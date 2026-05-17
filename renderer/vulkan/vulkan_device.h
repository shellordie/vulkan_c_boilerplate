#ifndef _VULKAN_DEVICE_H_
#define _VULKAN_DEVICE_H_
#include "vulkan_types.h"

b8 vulkan_device_get_physical_device(
    VkInstance vk_instance,
    VkPhysicalDevice* p_physical_device
    );

b8 vulkan_device_logical_device_create(
    VkPhysicalDevice physical_device,
    VkAllocationCallbacks* p_allocators,
    u32 queue_count,
    u32* p_queue_family_indices,
    u32* p_queue_per_family_counts,
    VkDevice* p_logical_device
    );

b8 vulkan_device_get_queue(
    VkDevice logical_device,
    u32 queue_family_index,
    u32 queue_index_in_family,
    VkQueue* p_queue
    );


#endif
