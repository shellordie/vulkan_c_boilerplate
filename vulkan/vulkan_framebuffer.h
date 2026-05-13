#ifndef _VULKAN_FRAMEBUFFER_H_
#define _VULKAN_FRAMEBUFFER_H_
#include "vulkan_types.h"

b8 vulkan_framebuffer_create(vulkan_t* p_vulkan,uint16_t width,uint16_t height);
void vulkan_framebuffer_destroy(vulkan_t* p_vulkan);

#endif
