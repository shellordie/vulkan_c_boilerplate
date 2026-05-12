#include "event.h"

void init_systems(systems_t* p_systems)
{
  for(u64 i=0;i<MAX_EVENT_TYPE;i++)
  {
    p_systems->p_array[i]=NULL;
  }
}

void event_register(systems_t* p_systems,u64 event_type,pfn_system_t function,ctx_t context)
{
  if(p_systems->p_array[event_type]==NULL)
  {
    p_systems->p_array[event_type]=_darray_allocate(sizeof(system_t),1);
  }
  system_t system;
  system.pfn=function;
  system.context=context;
  u64 used=darray_get_used(p_systems->p_array[event_type]);
  p_systems->p_array[event_type]=_darray_push(p_systems->p_array[event_type],(void*)&system,used);
}

void event_fired(systems_t* p_systems,u64 event_type)
{
  assert_failure(p_systems->p_array[event_type]!=NULL,"event type array is null");
  system_t* p_mem=(system_t*)p_systems->p_array[event_type];
  for(u64 i=0;i<darray_get_used(p_mem);i++)
  {
    system_t system=p_mem[i];
    b8 result=system.pfn(system.context);
    assert_failure(result==1,"error executing event systems");
  }
}

void destroy_systems(systems_t* p_systems)
{
  for(u64 i=0;i<MAX_EVENT_TYPE;i++)
  {
    if(p_systems->p_array[i]!=NULL)
    {
      darray_destroy(p_systems->p_array[i]);
    }
  }
}

b8 print_ok(ctx_t context)
{
  printf("this function is fired\n");
  char* name=(char*)context.ctx_void[0];
  printf("name= %s\n",name);
  return 1;
}

b8 calc(ctx_t context)
{
  printf("this function is fired\n");
  i32* p_data1=(i32*)context.ctx_void[0];
  i32* p_data2=(i32*)context.ctx_void[1];
  i32* p_result=(i32*)context.ctx_void[2];
  *p_result=*p_data1+*p_data2;
  return 1;
}

void event_test()
{
  //event types
  typedef enum event_type_t
  {
    EVENT_TYPE_PRINT=0,
    EVENT_TYPE_CALC=1
  }event_type_t;

  //initialisation
  systems_t systems;
  init_systems(&systems);

  //contexts
  char* name="my name is charles";
  ctx_t context;
  context.ctx_void[0]=(void*)name;
  event_register(&systems,EVENT_TYPE_PRINT,print_ok,context);

  name="another day another name";
  context.ctx_void[0]=(void*)name;
  event_register(&systems,EVENT_TYPE_PRINT,print_ok,context);


  i32 data1=3;
  i32 data2=10;
  i32 result=0;
  context.ctx_void[0]=(void*)&data1;
  context.ctx_void[1]=(void*)&data2;
  context.ctx_void[2]=(void*)&result;
  event_register(&systems,EVENT_TYPE_CALC,calc,context);

  //event fired
  event_fired(&systems,EVENT_TYPE_PRINT);
  event_fired(&systems,EVENT_TYPE_CALC);

  printf("new result=%d\n",result);
  assert_failure(1==0,"break here for test");
}


