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
  p_mem_address=NULL;
}

void* _darray_push(void* p_mem_address,void* p_data,u64 index)
{
  //check if we have space for the push
  u64 mem_used=darray_get_used(p_mem_address);
  u64 capacity=darray_get_capacity(p_mem_address);
  u64 stride=darray_get_stride(p_mem_address);

  if(mem_used==capacity)
  {
    //resize darray
    printf("resizing ....\n");
    p_mem_address=darray_resize(p_mem_address);
    assert_failure(p_mem_address!=NULL,"p_mem_address error resizing darray");
  }
  u64* p_mem=(u64*)p_mem_address;
  p_mem+=(stride*index);
  mem_copy((void*)p_mem,p_data,stride);
  //update used
  darray_set_used(p_mem_address,mem_used+1);
  return p_mem_address;
}

void* darray_resize(void* p_mem_address)
{
  u64 mem_used=darray_get_used(p_mem_address);
  u64 capacity=darray_get_capacity(p_mem_address);
  u64 stride=darray_get_stride(p_mem_address);

  void* p_new_mem_address=_darray_allocate(stride,capacity*ARRAY_RESIZE_FACTOR);
  assert_failure(stride==darray_get_stride(p_new_mem_address),"stride don't match");
  assert_failure((ARRAY_RESIZE_FACTOR*capacity)==darray_get_capacity(p_new_mem_address),"capacity don't match");
  mem_copy(p_new_mem_address,p_mem_address,stride*mem_used);
  darray_set_used(p_new_mem_address,mem_used);
  darray_destroy(p_mem_address);
  return p_new_mem_address;
}


u64 _darray_get_info(void* p_mem_address,enum header_t header)
{
  // calculate real mem address
  u64* mem_address=(u64*)p_mem_address;
  mem_address-=header_size;
  u64 info;
  switch(header)
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

void _darray_set_info(void* p_mem_address,enum header_t header,u64 data)
{
  u64* mem_address=(u64*)p_mem_address;
  mem_address-=header_size;
  switch(header)
  {
    case HEADER_TYPE_STRIDE:
      mem_address[HEADER_TYPE_STRIDE]=data;
      break; 
    case HEADER_TYPE_CAPACITY:
      mem_address[HEADER_TYPE_CAPACITY]=data;
      break;
    case HEADER_TYPE_USED:
      mem_address[HEADER_TYPE_USED]=data;
      break;
    default:break;
  }
}

void darray_test()
{

  int* p_int_array=darray_create(int);
  //int* p_int_array=darray_reserve(int,3);
  assert(p_int_array!=NULL,"darray_create failed","array_allocated");

  assert_failure(darray_get_capacity(p_int_array)==1,"array capacity must be 1");
  assert_failure(darray_get_stride(p_int_array)==4,"array stride must be 4");
  assert_failure(darray_get_used(p_int_array)==0,"darray stride must be 0");

  printf("PUSHING 3...\n");
  darray_push(p_int_array,3);
  printf("array index 0 =%d \n",p_int_array[0]);

  assert_failure(darray_get_capacity(p_int_array)==1,"array capacity must be 1");
  assert_failure(darray_get_stride(p_int_array)==4,"array stride must be 4");
  assert_failure(darray_get_used(p_int_array)==1,"darray stride must be 1");

  printf("PUSHING 5...\n");
  darray_push(p_int_array,5);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %d =%d \n",i,p_int_array[i]);
  }

  assert_failure(darray_get_capacity(p_int_array)==2,"array capacity must be 2");
  assert_failure(darray_get_stride(p_int_array)==4,"array stride must be 4");
  assert_failure(darray_get_used(p_int_array)==2,"darray stride must be 2");


  darray_destroy(p_int_array);

}






