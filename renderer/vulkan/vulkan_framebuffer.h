#ifndef _VULKAN_FRAMEBUFFER_H_
#define _VULKAN_FRAMEBUFFER_H_
#include "vulkan_types.h"

b8 vulkan_framebuffer_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkRenderPass renderpass,
    VkImageView* p_image_view,
    u16 width,
    u16 height,
    VkFramebuffer* p_framebuffer
    );

void vulkan_framebuffer_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFramebuffer* p_framebuffer);

#endif
