#ifndef _VULKAN_SURFACE_H_
#define _VULKAN_SURFACE_H_
#include  "vulkan_types.h"

b8 vulkan_surface_create(vulkan_t* p_vulkan,HINSTANCE hinstance_handle,HWND window_handle);

void vulkan_surface_destroy(vulkan_t* p_vulkan);


#endif



