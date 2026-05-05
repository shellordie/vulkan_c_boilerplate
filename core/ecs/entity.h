#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ecs_types.h"

b8 entity_create(char* name,entities_t* p_enities);
void entity_pop(char* name,entities_t* p_entities);
u64 entity_get_id(char* name,entities_t* p_entities);
void entity_destroy(entities_t* p_entities);

void entity_test();

#endif
