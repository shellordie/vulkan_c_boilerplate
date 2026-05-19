#ifndef _VULKAN_RENDERER_TYPES_H_
#define _VULKAN_RENDERER_TYPES_H_

#include "defines.h"
#include "vulkan/vulkan_types.h"


typedef struct vk_device_t
{
  char* p_gpu_name;
  u32 gpu_id;
  u32 physical_device_count;
  VkPhysicalDevice physical_device;
  VkDevice logical_device;
}vk_device_t;

typedef struct vk_queue_t
{
  u32 family_index;
  u32 count;
  VkQueue* p_handles;
}vk_queue_t;

typedef struct vk_swapchain_t
{
  VkSwapchainKHR handle;
  VkFormat image_format;
  u32 image_count;
  VkImage* p_images;
  VkImageView* p_image_views;
  VkFence fence;
}vk_swapchain_t;

typedef struct vk_surface_t
{
  VkSurfaceKHR handle;
}vk_surface_t;

typedef struct vk_framebuffer_t
{
  VkFramebuffer* p_handles;
}vk_framebuffer_t;

typedef struct vk_command_t
{
  VkCommandPool command_pool;
  u32 command_buffer_count;
  VkCommandBuffer* p_command_buffers;
}vk_command_t;

typedef struct vk_renderpass_t
{
  VkRenderPass handle;
}vk_renderpass_t;

typedef struct vulkan_t 
{
  VkInstance instance;
  VkAllocationCallbacks* p_allocators;
  VkDebugUtilsMessengerEXT debug_messenger;
  vk_device_t device;
  vk_queue_t global_queue;
  vk_swapchain_t swapchain;
  vk_surface_t surface;
  vk_framebuffer_t framebuffer;
  vk_command_t command;
  vk_renderpass_t renderpass;
}vulkan_t;

#endif
