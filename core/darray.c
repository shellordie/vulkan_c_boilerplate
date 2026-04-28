#include "darray.h"

void* _darray_allocate(u64 stride, u64 capacity)
{
  u64 mem_size_to_allocate=(stride*capacity)+header_size;

  u64* p_mem_address=(u64*)mem_allocate(mem_size_to_allocate);

  assert_failure(p_mem_address!=NULL,"mem_allocate failed");

  p_mem_address[HEADER_TYPE_STRIDE]=stride;
  p_mem_address[HEADER_TYPE_CAPACITY]=capacity;
  p_mem_address[HEADER_TYPE_USED]=0;

  //p_mem_address=mem_copy(p_mem_address,(void*)&header,sizeof(header_t));

  //mem address to return
  //uint64_t* mem_address=(uint64_t*)p_mem_address;
  *p_mem_address+=header_size;

  return (void*)p_mem_address;
}

void _darray_destroy(void* p_mem_address)
{
  // calculate real mem address
  u64* real_mem_address=(u64*)p_mem_address;
  *real_mem_address-=header_size;
  mem_free((void*)real_mem_address);
}

u64 _darray_get_info(void* p_mem_address,enum header_t header_type)
{
  // calculate real mem address
  u64* p_real_mem_address=(u64*)p_mem_address;
  *p_real_mem_address-=header_size;
  u64 info;
  switch(header_type)
  {
    case HEADER_TYPE_STRIDE:
      info=p_real_mem_address[HEADER_TYPE_STRIDE];
      break;
    case HEADER_TYPE_CAPACITY:
      info=p_real_mem_address[HEADER_TYPE_CAPACITY];
      break;
    case HEADER_TYPE_USED:
      info=p_real_mem_address[HEADER_TYPE_USED];
      break;
    default:
  }
  return info;
}

void darray_test()
{
  int* p_int_array=darray_create(int);
  assert(p_int_array!=NULL,"darray_create failed","array_allocated");
  printf("array capacity =%d \n",darray_get_size(p_int_array));
  p_int_array[0]=3;
  darray_destroy(p_int_array);

  p_int_array=darray_reserve(int,2);
  assert(p_int_array!=NULL,"darray_reserve failed","array_allocated");
  printf("array capacity =%d \n",darray_get_size(p_int_array));
  darray_destroy(p_int_array);
}






