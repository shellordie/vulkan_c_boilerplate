#ifndef _VULKAN_SURFACE_H_
#define _VULKAN_SURFACE_H_
#include  "vulkan_types.h"

b8 vulkan_surface_create(
    VkInstance vk_instance,
    VkAllocationCallbacks* p_allocators,
    HINSTANCE hinstance_handle,
    HWND window_handle,
    VkSurfaceKHR* p_surface
    );

void vulkan_surface_destroy(
    VKInstance vk_instance,
    VkAllocationsCallbacks* p_allocators,
    VkSurfaceKHR surface
    );


#endif



