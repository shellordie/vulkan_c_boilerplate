#ifndef _VULKAN_DEVICE_H_
#define _VULKAN_DEVICE_H_
#include "vulkan_types.h"

int get_physical_device(vulkan_t* vulkan);
int create_logical_device(vulkan_t* vulkan);
int get_global_queue_from_logical_device(vulkan_t* vulkan);


#endif
