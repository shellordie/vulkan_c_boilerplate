#ifndef _VULKAN_SWAPCHAIN_H_
#define _VULKAN_SWAPCHAIN_H_
#include "vulkan_types.h"

int create_swapchain(vulkan_t* vulkan,uint16_t width,uint16_t height);
int get_swapchain_images(vulkan_t* vulkan);
int create_swapchain_images_views(vulkan_t* vulkan);
int get_presentable_image(vulkan_t* p_vulkan,uint32_t* p_image_index);
int present_image(vulkan_t* p_vulkan,uint32_t* p_image_index);
#endif
