#ifndef _VULKAN_SWAPCHAIN_H_
#define _VULKAN_SWAPCHAIN_H_
#include "vulkan_types.h"

b8 vulkan_swapchain_create(vulkan_t* p_vulkan,uint16_t width,uint16_t height);
b8 vulkan_swapchain_get_images(vulkan_t* p_vulkan);
b8 vulkan_swapchain_create_images_views(vulkan_t* vulkan);
b8 vulkan_swapchain_get_presentable_image(vulkan_t* p_vulkan,uint32_t* p_image_index);
b8 vulkan_swapchain_present_image(vulkan_t* p_vulkan,uint32_t* p_image_index);
void vulkan_swapchain_destroy(vulkan_t* p_vulkan);
#endif
