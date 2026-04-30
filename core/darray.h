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
#define ARRAY_RESIZE_FACTOR 2

void* _darray_allocate(u64 stride, u64 capacity);
void _darray_destroy(void* p_mem_address);
u64 _darray_get_info(void* p_mem_address,enum header_t header);
void* _darray_push(void* p_mem_address,void* p_data,u64 index);
void* darray_resize(void* p_mem_address);
void _darray_set_info(void* p_mem_address,enum header_t header,u64 data);
void darray_test();

#define darray_create(type) _darray_allocate((u64)sizeof(type),1)

#define darray_reserve(type,capacity) _darray_allocate(sizeof(type),capacity)

#define darray_destroy(p_mem_address) _darray_destroy((void*)p_mem_address)

//get info
#define darray_get_capacity(p_mem_address) _darray_get_info((void*)p_mem_address,HEADER_TYPE_CAPACITY)
#define darray_get_used(p_mem_address) _darray_get_info((void*)p_mem_address,HEADER_TYPE_USED)
#define darray_get_stride(p_mem_address) _darray_get_info((void*)p_mem_address,HEADER_TYPE_STRIDE)

//set info
#define darray_set_capacity(p_mem_address,data) _darray_set_info((void*)p_mem_address,HEADER_TYPE_CAPACITY,data)
#define darray_set_used(p_mem_address,data) _darray_set_info((void*)p_mem_address,HEADER_TYPE_USED,data)
#define darray_set_stride(p_mem_address,data) _darray_set_info((void*)p_mem_address,HEADER_TYPE_STRIDE,data)


#define darray_push(p_mem_address,data)\
{\
  u64 index=darray_get_used(p_mem_address);\
  typeof(data) p_data=data;\
  p_mem_address=_darray_push((void*)p_mem_address,(void*)&p_data,index);\
}\

#define darray_push_at(p_mem_address,p_data,index)\
{\
  p_mem_address=_darray_push((void*)p_mem_address,(void*)&p_data,index);\
}\


#endif
