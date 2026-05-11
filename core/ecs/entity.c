#include "entity.h"

void init_entities(entities_t* p_entities)
{
  p_entities->p_array=NULL;
}

u64 create_entity(entities_t* p_entities,char* name)
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
  return new_entity.id;
}

u64 get_entity_id(entities_t entities,char* name)
{
  for(u64 i=0;i<darray_get_used(entities.p_array);i++)
  {
    entity_t entity=entities.p_array[i];
    if(str_cmp(name,entity.name)==1)
    {
      return entity.id;
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

void test_entity()
{
  entities_t entities_db;
  init_entities(&entities_db);

  init_entities(&entities_db);
  create_entity(&entities_db,"floor");
  create_entity(&entities_db,"triangle");

  for(u64 i=0;i<darray_get_used(entities_db.p_array);i++)
  {
    entity_t entity=entities_db.p_array[i];
    printf("name = %s\n",entity.name);
    printf("id= %llu\n",entity.id);
  }
  printf("array id =%llu\n",get_entity_id(entities_db,"floor"));

  printf("array capacity = %llu\n",darray_get_capacity(entities_db.p_array));
  printf("array stride  =%llu\n",darray_get_stride(entities_db.p_array));
  printf("array used=%llu\n",darray_get_used(entities_db.p_array));
 
  destroy_entities(&entities_db);
  assert_failure(1!=1,"break here for test");
 
}





