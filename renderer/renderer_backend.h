#ifndef _RENDERER_BACKEND_H_
#define _RENDERER_BACKEND_H_
#include "renderer_types.h"

b8 renderer_backend_init(
    vulkan_t* p_vulkan,
    HINSTANCE hinstance_handle,
    HWND window_handle,
    char* p_app_name,
    u16 drawable_width,
    u16 drawable_height
    );
void renderer_backend_shutdown(vulkan_t* p_vulkan);
#endif
