#ifndef _VULKAN_COMMAND_H_
#define _VULKAN_COMMAND_H_
#include "vulkan_types.h"

b8 vulkan_command_create_pool(vulkan_t* p_vulkan); 
b8 vulkan_command_allocate_buffer(vulkan_t* p_vulkan);
b8 vulkan_command_begin_buffer(vulkan_t vulkan);
b8 vulkan_command_end_buffer(vulkan_t vulkan);
b8 vulkan_command_submit(vulkan_t vulkan);
void vulkan_command_destroy(vulkan_t* p_vulkan);
#endif
