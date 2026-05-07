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


u64 get_component_id(components_t* p_components,u64 type,entities_t entities,char* enity_name)
{
  assert_failure(type<MAX_COMPONENT_TYPE,"type superior or equal to MAX_COMPONENT_TYPE");
  assert_failure(p_components->p_array[type]!=NULL,"empty array");
  u64 entity_id=entity_get_id(entities,entity_name);
  u64 used=darray_get_used(p_components->p_array[type]);
  u64 stride=darray_get_used(p_components->p_array[type]);
  u64 mem_address=(u64)p_components->p_array[type];
  for(u64 i=0;i<used;i++)
  {
    mem_address+=stride;
    u64* p_mem=(u64*)mem_address;
    if(entity_id==p_mem[0])
    {
      break;
      return i;
    }
  }
  return -1;
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


