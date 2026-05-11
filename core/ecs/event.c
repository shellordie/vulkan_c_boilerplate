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
  systems_t system;
  system.pfn=function;
  system.context=context;
  u64 used=darray_get_used(p_systems->p_array[event_type]);
  p_systems->p_array[event_type]=_darray_push(p_systems->p_array[event_type],(void*)&system,used);
}

void event_fired(systems_t* p_systems,u64 event_type)
{
  assert_failure(p_systems->p_array[event_type]!=NULL,"event type array is null");
  void* p_mem=p_systems->p_array[event_type];
  for(u64 i=0;i<darray_get_used(p_mem);i++)
  {
    system_t system=(system_t)p_mem[i];
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

void event_test()
{
  typedef enum event_type_t
  {
    EVENT_TYPE_PRINT=0,
    EVENT_TYPE_CALC=1
  }event_type_t;
  systems_t systems;
  init_systems(&systems);
  char* name="context";
  ctx_t context;
  context.ctx_void[0]=(void*)&name;
  b8 print_ok(context);
  event_register(&systems,EVENT_TYPE_PRINT,print_ok,context);

  event_fired(&systems,EVENT_TYPE_PRINT);
  assert_failed(1==0,"break here for test");
}


