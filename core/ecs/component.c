#include "component.h"

void init_components(components_t* p_components)
{
  for(u64 i=0;i<MAX_COMPONENT_TYPE;i++)
  {
    p_components->p_array[i]=NULL;
  }
}

void _add_component(components_t* p_components,u64 type,void* p_data,u64 stride)
{
  assert_failure(type<MAX_COMPONENT_TYPE,"type superior or equal to MAX_COMPONENT_TYPE");
  if(p_components->p_array[type]==NULL)
  {
    p_components->p_array[type]=darray_create(stride);
  }
  darray_push(p_components->p_array[type],p_data);
}


i64 get_component_id(components_t* p_components,u64 type,entities_t entities,char* entity_name)
{
  assert_failure(type<MAX_COMPONENT_TYPE,"type superior or equal to MAX_COMPONENT_TYPE");
  assert_failure(p_components->p_array[type]!=NULL,"empty array");
  u64 entity_id=get_entity_id(entities,entity_name);
  printf("type =%llu\n",type);
  u64 used=darray_get_used(p_components->p_array[type]);
  u64 stride=darray_get_stride(p_components->p_array[type]);
  printf("stride=%llu\n",stride);
  u64 mem_address=(u64)p_components->p_array[type];
  u64 result=-1;
  for(u64 i=0;i<used;i++)
  {
    u64* p_mem=(u64*)mem_address;
    printf("entity_id=%llu\n",entity_id);
    printf("mem id=%llu\n",p_mem[0]);
    if(entity_id==p_mem[0])
    {
      printf("i=%llu\n",i);
      result=i;
      break;
    }
    mem_address+=stride;
  }
  return result;
}

void delete_component(components_t* p_components,u64 type,u64 id) 
{
    darray_pop_at(p_components->p_array[type],id);
}

void destroy_components(components_t* p_components)
{
  for(u64 i=0;i<MAX_COMPONENT_TYPE;i++)
  {
    darray_destroy(p_components->p_array[i]);
  }
}


void test_component(entities_t* p_entities_db)
{
  typedef enum components_type_t
  {
    COMPONENT_TYPE_POSITION=0,
    COMPONENT_TYPE_LOCATION=1
  }components_type_t;

  typedef struct position_component_t
  {
    u64 entity_id;
    u32 x;
    u32 y;
    u32 z;
  }position_component_t;

  enum location_type
  {
    NORTH,
    SOUTH
  };

  typedef struct location_component_t
  {
    u64 entity_id;
    enum location_type location;
  }location_component_t;


  components_t components_db;
  init_components(&components_db);

  // add position component
  u64 id=get_entity_id(*p_entities_db,"floor");
  position_component_t position={id,20,40,0};
  _add_component(&components_db,COMPONENT_TYPE_POSITION,(void*)&position,sizeof(position_component_t));

  /*
  id=get_entity_id(*p_entities_db,"triangle");
  position.entity_id=id;
  position.x=1;
  position.y=1;
  position.z=1;
  add_component(&components_db,COMPONENT_TYPE_POSITION,position);
  */

  // information
  printf("info about COMPONENT_TYPE_POSITION ARRAY \n");
  void* p_mem=components_db.p_array[COMPONENT_TYPE_POSITION];
  printf("array capacity = %llu\n",darray_get_capacity(p_mem));
  printf("array stride  =%llu\n",darray_get_stride(p_mem));
  printf("array used=%llu\n",darray_get_used(p_mem));
 
  u64 comp_id=get_component_id(&components_db,COMPONENT_TYPE_POSITION,*p_entities_db,"floor");
  printf("the position component of the entity 'floor' is at the index %lli\n",comp_id);

  position_component_t* p_mem_acc=p_mem;
  position=p_mem_acc[comp_id];
  printf("entity id =%llu\n",position.entity_id);
  printf("entity x=%u y=%u z=%u\n",position.x,position.y,position.z);

  //deleting components
  printf("deleting component at previous id\n");
  delete_component(&components_db,COMPONENT_TYPE_POSITION,comp_id);
  printf("array capacity = %llu\n",darray_get_capacity(p_mem));
  printf("array stride  =%llu\n",darray_get_stride(p_mem));
  printf("array used=%llu\n",darray_get_used(p_mem));
 
  assert_failure(1==0,"break here for test");
}
