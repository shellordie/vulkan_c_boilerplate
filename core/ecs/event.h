#ifndef _ECS_EVENT_H_
#define _ECS_EVENT_H_

#include "ecs_types.h"

void init_systems(systems_t* p_systems);
void event_register(systems_t* p_systems,u64 event_type,pfn_system_t function,ctx_t context);
void event_fired(systems_t* p_systems,u64 event_type);
void destroy_systems(systems_t* p_systems);
void event_test();

#endif
