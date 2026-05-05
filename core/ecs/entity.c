#include "entity.h"

b8 entity_create(char* name,entities_t* p_entities)
{
  if(p_entities->p_array==NULL)
  {
    printf("initializing srand\n");
    srand(1000000);
    p_entities->p_array=(entity_t*)darray_reserve(entity_t,MAX_ENTITY);
  }

  entity_t new_entity;
  new_entity.id=(u64)rand();
  new_entity.name=name;
  darray_push(p_entities->p_array,new_entity);
  return 1;
}

u64 entity_get_id(char* name,entities_t* p_entities)
{
  for(u64 i=0;i<darray_get_used(p_entities->p_array);i++)
  {
    entity_t entity=p_entities->p_array[i];
    if(str_cmp(name,entity.name)==1)
    {
      return i;
      break;
    }
  }
  return 0;
}

void entity_pop(char* name,entities_t* p_entities);

void entity_destroy(entities_t* p_entities)
{
  assert_failure(p_entities->p_array!=NULL,"entity array not initialized");
  darray_destroy(p_entities->p_array);
}

void entity_test()
{
  entities_t entity_world={NULL};
  entity_create("floor",&entity_world);
  entity_create("triangle",&entity_world);

  for(u64 i=0;i<darray_get_used(entity_world.p_array);i++)
  {
    entity_t entity=entity_world.p_array[i];
    printf("name = %s\n",entity.name);
    printf("id= %llu\n",entity.id);
  }
  printf("array id =%llu\n",entity_get_id("floor",&entity_world));

  printf("array capacity = %llu\n",darray_get_capacity(entity_world.p_array));
  printf("array stride  =%llu\n",darray_get_stride(entity_world.p_array));
  printf("array used=%llu\n",darray_get_used(entity_world.p_array));
 
  entity_destroy(&entity_world);

  assert_failure(1!=1,"break here for test");
 
}





