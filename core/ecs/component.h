#ifndef _COMPONENT_TYPE_H_
#define _COMPONENT_TYPE_H_

#include "ecs_types.h"
#include "entity.h"

void init_components(components_t* p_components);
void _add_component(components_t* p_components,u64 type,void* p_data,u64 stride);
i64 get_component_id(components_t* p_components,u64 type,entities_t entities,char* entity_name);
void delete_component(components_t* p_components,u64 type,u64 id); 
void destroy_components(components_t* p_components);
void test_component(entities_t* p_entities_db);

#define add_component(p_components,type,data)\
{\
  typeof(data) p_data=data;\
  _add_component(p_components,type,(void*)&p_data,sizeof(p_data));\
}\

#endif
