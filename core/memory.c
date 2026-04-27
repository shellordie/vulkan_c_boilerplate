#include "memory.h"

void* mem_allocate(uint64_t size)
{
  return malloc(size);
}

void mem_free(void* mem_address)
{
  free(mem_address);
}

void* mem_copy(void* dest,void* src,uint64_t count)
{
  return memcpy(dest,src,count);
}



