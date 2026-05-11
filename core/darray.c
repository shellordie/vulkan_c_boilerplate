#include "darray.h"

void* _darray_allocate(u64 stride, u64 capacity)
{
  u64 mem_size_to_allocate=(stride*capacity)+header_size;

  u64* p_mem_address=(u64*)mem_allocate(mem_size_to_allocate);

  assert_failure(p_mem_address!=NULL,"mem_allocate failed");

  p_mem_address[HEADER_TYPE_STRIDE]=stride;
  p_mem_address[HEADER_TYPE_CAPACITY]=capacity;
  p_mem_address[HEADER_TYPE_USED]=0;

  void* ptr_mem_to_return=(void*)((u64)p_mem_address+header_size);
  return (void*)ptr_mem_to_return;
}

void _darray_destroy(void* p_mem_address)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  // calculate real mem address
  u64 real_mem_address=((u64)p_mem_address-header_size);
  mem_free((void*)real_mem_address);
  p_mem_address=NULL;
}

void* _darray_push(void* p_mem_address,void* p_data,u64 index)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  u64 mem_used=darray_get_used(p_mem_address);
  u64 capacity=darray_get_capacity(p_mem_address);
  u64 stride=darray_get_stride(p_mem_address);

  //check if we have space for the push
  if(mem_used==capacity)
  {
    //resize darray
    //printf("resizing ....\n");
    p_mem_address=darray_resize(p_mem_address);
    assert_failure(p_mem_address!=NULL,"p_mem_address error resizing darray");
  }
  u64 mem_address=(u64)p_mem_address;
  //printf("mem ad u64 =%llu\n",(u64)p_mem_address);
  mem_address+=(stride*index);
  mem_copy((void*)mem_address,p_data,stride);
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
  mem_copy(p_new_mem_address,p_mem_address,stride*capacity);
  darray_set_used(p_new_mem_address,mem_used);
  darray_destroy(p_mem_address);
  return p_new_mem_address;
}

void* _darray_pop(void* p_mem_address, u64 index)
{
  assert_failure(darray_get_used(p_mem_address)!=0,"can not pop array containing 0 element");
  u64 mem_used=darray_get_used(p_mem_address);
  u64 capacity=darray_get_capacity(p_mem_address);
  u64 stride=darray_get_stride(p_mem_address);

  if(mem_used==index+1)
  {
    darray_set_used(p_mem_address,mem_used-1);
  }
  else
  {
    u64 dst_address=(u64)p_mem_address;
    dst_address+=(stride*index);

    u64 src_address=dst_address+stride; 
    u64 size_to_copy=stride*((mem_used-1)-index);
    mem_copy((void*)dst_address,(void*)src_address,size_to_copy);
    darray_set_used(p_mem_address,mem_used-1);
  }

  return p_mem_address;
}

void darray_reset(void* p_mem_address)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  darray_set_used(p_mem_address,0);
}

u64 _darray_get_info(void* p_mem_address,enum header_t header)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  // calculate real mem address
  u64 mem_address=(u64)p_mem_address;
  mem_address-=header_size;
  u64* ptr_mem_address=(u64*)mem_address;
  u64 info;
  switch(header)
  {
    case HEADER_TYPE_STRIDE:
      info=ptr_mem_address[HEADER_TYPE_STRIDE];
      break; 
    case HEADER_TYPE_CAPACITY:
      info=ptr_mem_address[HEADER_TYPE_CAPACITY];
      break;
    case HEADER_TYPE_USED:
      info=ptr_mem_address[HEADER_TYPE_USED];
      break;
    default:break;
  }
  return info;
}

void _darray_set_info(void* p_mem_address,enum header_t header,u64 data)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  u64 mem_address=(u64)p_mem_address;
  mem_address-=header_size;
  u64* ptr_mem_address=(u64*)mem_address;
  switch(header)
  {
    case HEADER_TYPE_STRIDE:
      ptr_mem_address[HEADER_TYPE_STRIDE]=data;
      break; 
    case HEADER_TYPE_CAPACITY:
      ptr_mem_address[HEADER_TYPE_CAPACITY]=data;
      break;
    case HEADER_TYPE_USED:
      ptr_mem_address[HEADER_TYPE_USED]=data;
      break;
    default:break;
  }
}

void darray_info(void* p_mem_address)
{
  assert_failure(p_mem_address!=NULL,"p_mem_address is null");
  printf("array capacity = %llu \n",darray_get_capacity(p_mem_address));
  printf("array stride  =%llu \n",darray_get_stride(p_mem_address));
  printf("array used =%llu \n",darray_get_used(p_mem_address));
}


void darray_test()
{

  int* p_int_array=darray_create(int);
  //int* p_int_array=darray_reserve(int,3);
  assert(p_int_array!=NULL,"darray_create failed","array_allocated");

  printf("array capacity = %llu \n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu \n",darray_get_stride(p_int_array));
  printf("array used=%llu \n",darray_get_used(p_int_array));
  int data =3;
  printf("PUSHING ...\n");
  darray_push(p_int_array,data);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu \n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));

  data=5;
  printf("PUSHING ...\n");
  darray_push(p_int_array,data);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu\n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));

  //
  printf("RESETING .... \n");
  darray_reset(p_int_array);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu\n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));


  //
  data=10;
  printf("PUSHING ...\n");
  darray_push(p_int_array,data);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu\n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));

  //

  u64 index=0;
  printf("poping...\n");
  darray_pop_at(p_int_array,index);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu\n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));
  

  data=100;
  printf("PUSHING ...\n");
  darray_push(p_int_array,data);
  for(u64 i=0;i<darray_get_used(p_int_array);i++)
  {
    printf("array index %llu =%d \n",i,p_int_array[i]);
  }

  printf("array capacity = %llu\n",darray_get_capacity(p_int_array));
  printf("array stride  =%llu\n",darray_get_stride(p_int_array));
  printf("array used=%llu\n",darray_get_used(p_int_array));
  


  darray_destroy(p_int_array);
  assert_failure(1==0,"break here for test");

}






