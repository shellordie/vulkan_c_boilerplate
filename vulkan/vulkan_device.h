#ifndef _VULKAN_DEVICE_H_
#define _VULKAN_DEVICE_H_
#include "vulkan_types.h"

int vulkan_device_get_physical_device(vulkan_t* vulkan);
int vulkan_device_create_logical_device(vulkan_t* vulkan);
int vulkan_device_get_global_queue(vulkan_t* vulkan);


#endif
