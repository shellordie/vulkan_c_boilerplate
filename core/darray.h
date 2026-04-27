#ifndef _DARRAY_H
#define _DARRAY_H
#include "../defines.h"

typedef struct header_t 
{
  uint32_t stride;
  uint32_t capacity;
  uint32_t used;
}header_t;

void* _darray_allocate(uint32_t stride, uint32_t capacity);
void _darray_destroy(void* p_mem_address);
void darray_test();

#define darray_create(type) _darray_allocate(sizeof(type),1)

#define darray_reserve(type,capacity) _darray_allocate(sizeof(type),capacity)

#define darray_destroy(mem_address) _darray_destroy((void*)mem_address)

#endif
