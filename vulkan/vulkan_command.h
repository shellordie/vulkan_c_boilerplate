#ifndef _VULKAN_COMMAND_H_
#define _VULKAN_COMMAND_H_
#include "vulkan_types.h"

int create_command_pool(vulkan_t* p_vulkan); 
int allocate_command_buffer(vulkan_t* p_vulkan);
int begin_command_buffer(vulkan_t vulkan);
void destroy_command_pool();
void destroy_command_buffer();
int submit_command(vulkan_t vulkan);
#endif
