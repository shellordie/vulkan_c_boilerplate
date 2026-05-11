#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_types.h"
void init_entities(entities_t* p_entities);
u64 create_entity(entities_t* p_entities,char* name);
void delete_entity(entities_t* p_entities,char* name);
u64 get_entity_id(entities_t entities,char* name);
void destroy_entity(entities_t* p_entities);

void test_entity();

#endif
