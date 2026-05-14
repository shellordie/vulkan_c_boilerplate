#include "vulkan_surface.h"

b8 vulkan_surface_create(vulkan_t* p_vulkan,HINSTANCE instance_handle,HWND window_handle)
{
  VkWin32SurfaceCreateInfoKHR surface_create_info;
  surface_create_info.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surface_create_info.flags=0;
  surface_create_info.pNext=NULL;
  surface_create_info.flags=0;
  surface_create_info.hinstance=instance_handle;
  surface_create_info.hwnd=window_handle;
  //
  vk_check_ex(
      vkCreateWin32SurfaceKHR(p_vulkan->instance,&surface_create_info,p_vulkan->p_allocators,&p_vulkan->surface.handle),
      "win32 surface creation failed",
      "win32 surface created");

  return 1;
}

void vulkan_surface_destroy(vulkan_t* p_vulkan)
{
  VkDestroySurfaceKHR(p_vulkan->instance,p_vulkan->surface.handle,p_vulkan->p_allocators);
}
