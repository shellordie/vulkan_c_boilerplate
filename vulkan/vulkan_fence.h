#ifndef _VULKAN_FENCE_H_
#define _VULKAN_FENCE_H_

#include "vulkan_types.h"

b8 vulkan_fence_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFence* p_fence
    );

void vulkan_fence_destroy(
    VkDevice logical_device,
    vkAllocationsCallbacks* p_allocators,
    VkFence fence);

#endif
