#include "entity.h"

void init_entities(entities_t* p_entities)
{
  p_entities=NULL;
}

b8 create_entity(entities_t* p_entities,char* name)
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

u64 get_entity_id(entities_t entities,char* name)
{
  for(u64 i=0;i<darray_get_used(entities.p_array);i++)
  {
    entity_t entity=entities.p_array[i];
    if(str_cmp(name,entity.name)==1)
    {
      return i;
      break;
    }
  }
  return 0;
}

void delete_entity(entities_t* p_entities,char* name);

void destroy_entities(entities_t* p_entities)
{
  assert_failure(p_entities->p_array!=NULL,"entity array not initialized");
  darray_destroy(p_entities->p_array);
}

void entity_test()
{
  entities_t entity_world;
  init_entities(&entity_world);
  create_entity(&entity_world,"floor");
  create_entity(&entity_world,"triangle");

  for(u64 i=0;i<darray_get_used(entity_world.p_array);i++)
  {
    entity_t entity=entity_world.p_array[i];
    printf("name = %s\n",entity.name);
    printf("id= %llu\n",entity.id);
  }
  printf("array id =%llu\n",get_entity_id(entity_world,"floor"));

  printf("array capacity = %llu\n",darray_get_capacity(entity_world.p_array));
  printf("array stride  =%llu\n",darray_get_stride(entity_world.p_array));
  printf("array used=%llu\n",darray_get_used(entity_world.p_array));
 
  destroy_entity(&entity_world);

  assert_failure(1!=1,"break here for test");
 
}





