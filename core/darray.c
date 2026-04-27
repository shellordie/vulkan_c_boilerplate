#include "darray.h"

void* _darray_allocate(uint32_t stride, uint32_t capacity)
{
  uint64_t mem_size_to_allocate=(stride*capacity)+sizeof(header_t);

  void* p_mem_address=mem_allocate(mem_size_to_allocate);

  header_t header={stride,capacity,0};

  assert_failure(p_mem_address!=NULL,"mem_allocate failed");

  p_mem_address=mem_copy(p_mem_address,(void*)&header,sizeof(header_t));

  //mem address to return
  uint64_t* mem_address=(uint64_t*)p_mem_address;
  *mem_address+=sizeof(uint32_t);

  return (void*)mem_address;
}

void _darray_destroy(void* p_mem_address)
{
  // calculate real mem address
  uint64_t* real_mem_address=(uint64_t*)p_mem_address;
  *real_mem_address-=sizeof(header_t);
  mem_free((void*)real_mem_address);
}


void darray_test()
{
  int* p_int_array=darray_create(int);
  assert(p_int_array!=NULL,"darray_create failed","array_allocated");
  darray_destroy(p_int_array);

  p_int_array=darray_reserve(int,2);
  assert(p_int_array!=NULL,"darray_reserve failed","array_allocated");
  darray_destroy(p_int_array);
}






