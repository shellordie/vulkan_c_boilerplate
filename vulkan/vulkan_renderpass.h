#ifndef _VULKAN_RENDERPASS_H_
#define _VULKAN_RENDERPASS_H_

#include "vulkan_types.h"

b8 vulkan_renderpass_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFormat image_format,
    VkRenderPass* p_renderpass);

b8 vulkan_renderpass_begin(
    VkCommandBuffer command_buffer,
    VkRenderPass renderpass,
    VkFramebuffer framebuffer,
    u16 width,
    u16 height);

b8 vulkan_renderpass_end(VkCommandBuffer command_buffer);

void vulkan_renderpass_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkRenderPass renderpass);
#endif


