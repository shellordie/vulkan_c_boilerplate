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
    p_components->p_array[type]=_darray_allocate(stride,1);
  }
  u64 index=darray_get_used(p_components->p_array[type]);
  p_components->p_array[type]=_darray_push((void*)p_components->p_array[type],p_data,index);
}


i64 get_component_id(components_t* p_components,u64 type,u64 entity_id)
{
  assert_failure(type<MAX_COMPONENT_TYPE,"type superior or equal to MAX_COMPONENT_TYPE");
  assert_failure(p_components->p_array[type]!=NULL,"empty array");
  u64 used=darray_get_used(p_components->p_array[type]);
  u64 stride=darray_get_stride(p_components->p_array[type]);
  u64 mem_address=(u64)p_components->p_array[type];
  u64 result=-1;
  for(u64 i=0;i<used;i++)
  {
    u64* p_mem=(u64*)mem_address;
    if(entity_id==p_mem[0])
    {
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
    if(p_components->p_array[i]!=NULL)
    {
      darray_destroy(p_components->p_array[i]);
    }
  }
}


void test_component()
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


  entities_t entities_db;
  init_entities(&entities_db);

  components_t components_db;
  init_components(&components_db);

  // add floor
  u64 entity_id=create_entity(&entities_db,"floor");
  printf("entity floor id=%llu\n",entity_id);
  position_component_t position={entity_id,20,40,0};
  add_component(&components_db,COMPONENT_TYPE_POSITION,position);

  // add triangle
  entity_id=create_entity(&entities_db,"triangle");
  position.entity_id=entity_id;
  position.x=1;
  position.y=1;
  position.z=1;
  add_component(&components_db,COMPONENT_TYPE_POSITION,position);

  
  location_component_t location={entity_id,NORTH};
  add_component(&components_db,COMPONENT_TYPE_LOCATION,location);
  
  
  // information
  printf("info about COMPONENT_TYPE_POSITION ARRAY \n");
  void* p_mem=components_db.p_array[COMPONENT_TYPE_POSITION];
  darray_info(p_mem);

  printf("info about COMPONENT_TYPE_LOCATION ARRAY \n");
  darray_info(components_db.p_array[COMPONENT_TYPE_LOCATION]);
  
  i64 comp_id=get_component_id(&components_db,COMPONENT_TYPE_POSITION,entity_id);
  assert_failure(comp_id!=-1,"error with getting the comp id");
  printf("the position component of the entity 'triangle' is at the index %lli\n",comp_id);
  

  position_component_t* p_mem_acc=p_mem;
  position=p_mem_acc[comp_id];
  printf("entity id =%llu\n",position.entity_id);
  printf("entity x=%d y=%d z=%d\n",position.x,position.y,position.z);

  
  //deleting components
  printf("deleting component at previous id\n");
  delete_component(&components_db,COMPONENT_TYPE_POSITION,comp_id);
  darray_info(p_mem);
 
  destroy_components(&components_db);
  assert_failure(1==0,"break here for test");
}
