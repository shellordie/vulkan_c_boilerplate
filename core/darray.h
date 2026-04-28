#ifndef _DARRAY_H
#define _DARRAY_H
#include "../defines.h"

enum header_t 
{
  HEADER_TYPE_STRIDE=0,
  HEADER_TYPE_CAPACITY=1,
  HEADER_TYPE_USED=2
};

#define header_size 3*sizeof(u64)

void* _darray_allocate(u64 stride, u64 capacity);
void _darray_destroy(void* p_mem_address);
u64 _darray_get_info(void* p_mem_address,enum header_t header);
void _darray_push(void* p_mem_address,u64 stride,void* p_data,u64 index);
void darray_test();

#define darray_create(type) _darray_allocate(sizeof(type),1)

#define darray_reserve(type,capacity) _darray_allocate(sizeof(type),capacity)

#define darray_destroy(p_mem_address) _darray_destroy((void*)p_mem_address)

#define darray_get_size(p_mem_address) _darray_get_info((void*)p_mem_address,HEADER_TYPE_CAPACITY)
#define darray_get_size_used(p_mem_address) _darray_get_info((void*)p_mem_address,HEADER_TYPE_USED)

#define darray_push(p_mem_address,p_data)\
{\
  u64 stride=sizeof(typeof(p_data));\
  u64 index=darray_get_size_used(p_mem_address)+1;\
  _darray_push(p_mem_address,stride,p_data,index);\
}\

#define darray_push_at(p_mem_address,p_data,index)\
{\
  u64 stride=sizeof(typeof(p_data));\
  _darray_push(p_mem_address,stride,p_data,index);\
}\


#endif
