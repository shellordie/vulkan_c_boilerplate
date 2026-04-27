#ifndef _VULKAN_RENDERPASS_H_
#define _VULKAN_RENDERPASS_H_

#include "vulkan_types.h"

int create_renderpass(vulkan_t* vulkan);
int begin_renderpass(vulkan_t vulkan,uint32_t image_index,uint32_t width,uint32_t height);
#endif


