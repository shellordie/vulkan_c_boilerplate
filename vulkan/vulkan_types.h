#ifndef VULKAN_TYPES_H
#define VULKAN_TYPES_H
#include <stdio.h>
#include <vulkan/vulkan.h>
#include <windows.h>
#include <vulkan/vulkan_win32.h>
#include "../defines.h"


#define vk_check(vk_status,message_f) assert_failure(vk_status==VK_SUCCESS,message)
#define vk_check_ex(vk_status,message_f,message_s) assert(vk_status!=VK_SUCCESS,message,message_s)

typedef struct swapchain_t
{
  VkFormat image_format;
  VkSwapchainKHR handle;
  uint32_t images_count;
  VkImage* p_images;
  VkImageView* p_images_views;
  VkFence fence;
}swapchain_t;

typedef struct surface_t
{
  VkSurfaceKHR handle;
}surface_t;

typedef struct framebuffer_t
{
  VkFramebuffer* p_handles;
}framebuffer_t;

typedef struct command_t
{
  VkCommandPool command_pool;
  VkCommandBuffer command_buffer;
}command_t;

typedef struct vulkan_t 
{
  VkInstance instance;
  VkAllocationCallbacks* p_allocators;
  VkDebugUtilsMessengerEXT debug_messenger;
  uint32_t physical_device_count;
  uint32_t gpu_id;
  char* gpu_name;
  VkPhysicalDevice physical_device;
  VkDevice logical_device;
  uint32_t global_queue_family_index;
  uint32_t global_queues_count;
  VkQueue global_queue;
  command_t command;
  swapchain_t swapchain;
  surface_t surface;
  VkRenderPass renderpass;
  framebuffer_t framebuffer;
}vulkan_t;

#endif
