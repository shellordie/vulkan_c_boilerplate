#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "../defines.h"

void* mem_allocate(uint64_t size);
void mem_free(void* mem_address);
void* mem_copy(void* dest,void* src,uint64_t count);


#endif
