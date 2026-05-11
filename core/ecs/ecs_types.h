#ifndef _ECS_TYPES_H_
#define _ECS_TYPES_H_

#include "defines.h"


// entity type
//#define MAX_CHAR_LENGTH 250
#define MAX_ENTITY 20000
#define MAX_COMPONENT_TYPE 100
#define MAX_EVENT_TYPE 100

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
  void* p_array[MAX_COMPONENT_TYPE];
}components_t;

//events
typedef union ctx_t
{
  u64  ctx_u64[4];
  void* ctx_void[4];
}ctx_t;

typedef b8 (*pfn_system_t) (ctx_t context);

typedef struct system_t
{
  pfn_system_t pfn;
  ctx_t context;
}system_t;

typedef struct systems_t
{
  void* p_array[MAX_EVENT_TYPE];
}systems_t;


#endif
