#ifndef _VULKAN_SWAPCHAIN_H_
#define _VULKAN_SWAPCHAIN_H_
#include "vulkan_types.h"

b8 vulkan_swapchain_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_alocators,
    VkSurfaceKHR surface,
    VkFormat image_format,
    u32 image_count,
    u32 presentation_queue_count,
    u32* p_queue_family_indices,
    u16 width,
    u16 height,
    VkSwapchainKHR* p_swapchain
    );

b8 vulkan_swapchain_get_images(
    VkDevice logical_device,
    VkSwapchainKHR swapchain,
    u32* p_image_count,
    VkImage* p_images
    );

b8 vulkan_swapchain_create_image_view(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFormat image_format,
    VkImage image,
    VkImageView* p_image_view
    );

b8 vulkan_swapchain_get_presentable_image(
    VkDevice logical_device,
    VkSwapchainKHR swapchain,
    VkFence fence,
    u32* p_image_index);

b8 vulkan_swapchain_present_image(
    VkQueue present_queue,
    VkSwapchainKHR* p_swapchain,
    u32* p_image_index
    );

void vulkan_swapchain_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkSwapchainKHR swapchain,
    u32 image_count,
    VkImageView* p_image_views
    );
#endif
