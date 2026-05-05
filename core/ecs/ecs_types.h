#ifndef _ECS_TYPES_H_
#define _ECS_TYPES_H_

#include "defines.h"


// entity type
#define MAX_CHAR_LENGTH 250
#define MAX_ENTITY 20000
#define MAX_COMPONENT_TYPE 100

typedef struct entity_t 
{
  u64 id;
  char* name;
}entity_t;

typedef struct entities_t
{
  entity_t* p_array;
}entities_t;

//components

typedef struct components_t 
{
  //component_type_t available_component[MAX_COMPONENTS];
  void* p_array[MAX_COMPONENT_TYPE];
}components_t;


#endif
