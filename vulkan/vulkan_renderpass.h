#ifndef _VULKAN_RENDERPASS_H_
#define _VULKAN_RENDERPASS_H_

#include "vulkan_types.h"

b8 vulkan_renderpass_create(vulkan_t* p_vulkan);
b8 vulkan_renderpass_begin(vulkan_t* p_vulkan,uint32_t image_index,uint32_t width,uint32_t height);
b8 vulkan_renderpass_end(vulkan_t* p_vulkan);
void vulkan_renderpass_destroy(vulkan_t* p_vulkan);
#endif


