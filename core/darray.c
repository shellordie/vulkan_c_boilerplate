#include "darray.h"

void* _darray_allocate(u64 stride, u64 capacity)
{
  u64 mem_size_to_allocate=(stride*capacity)+header_size;

  u64* p_mem_address=(u64*)mem_allocate(mem_size_to_allocate);

  assert_failure(p_mem_address!=NULL,"mem_allocate failed");

  p_mem_address[HEADER_TYPE_STRIDE]=stride;
  p_mem_address[HEADER_TYPE_CAPACITY]=capacity;
  p_mem_address[HEADER_TYPE_USED]=0;

  p_mem_address+=header_size;
  return (void*)p_mem_address;
}

void _darray_destroy(void* p_mem_address)
{
  // calculate real mem address
  u64* real_mem_address=(u64*)p_mem_address;
  real_mem_address-=header_size;
  mem_free((void*)real_mem_address);
}

void _darray_push(void* p_mem_address,void* p_data,u64 index)
{
  //check if we have space for the push
  u64 mem_used=darray_get_size_used(p_mem_address);
  printf("used=%llu \n",mem_used);
  u64 capacity=darray_get_size(p_mem_address);
  printf("capacity=%llu \n",capacity);
  u64 stride=darray_get_stride(p_mem_address);
  printf("stride =%llu \n",stride);

  if(mem_used==capacity)
  {
    assert_failure(mem_used<capacity,"darray full cannot push more data!");
    //resize darray
  }
  u64* p_mem=(u64*)p_mem_address;
  p_mem+=(stride*index);
  mem_copy((void*)p_mem,p_data,stride);

  p_mem=(u64*)p_mem_address;
  p_mem-=header_size;
  p_mem[HEADER_TYPE_USED]=mem_used+1;
}

u64 _darray_get_info(void* p_mem_address,enum header_t header_type)
{
  // calculate real mem address
  u64* mem_address=(u64*)p_mem_address;
  mem_address-=header_size;
  u64 info;
  switch(header_type)
  {
    case HEADER_TYPE_STRIDE:
      info=mem_address[HEADER_TYPE_STRIDE];
      break; 
    case HEADER_TYPE_CAPACITY:
      info=mem_address[HEADER_TYPE_CAPACITY];
      break;
    case HEADER_TYPE_USED:
      info=mem_address[HEADER_TYPE_USED];
      break;
    default:break;
  }
  return info;
}

void darray_test()
{
  int* p_int_array=darray_create(int);
  assert(p_int_array!=NULL,"darray_create failed","array_allocated");
  //printf("array capacity =%d \n",darray_get_size(p_int_array));
  //printf("array stride=%d \n",darray_get_stride(p_int_array));
  darray_push(p_int_array,3);
  printf("array index 0 =%d \n",p_int_array[0]);
  darray_push(p_int_array,5);
  darray_destroy(p_int_array);

  p_int_array=darray_reserve(int,2);
  assert(p_int_array!=NULL,"darray_reserve failed","array_allocated");
  printf("array capacity =%d \n",darray_get_size(p_int_array));
  darray_destroy(p_int_array);
}






