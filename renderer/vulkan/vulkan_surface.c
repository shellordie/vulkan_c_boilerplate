#include "vulkan_surface.h"

b8 vulkan_surface_create(
    VkInstance vk_instance,
    VkAllocationCallbacks* p_allocators,
    HINSTANCE instance_handle,
    HWND window_handle,
    VkSurfaceKHR* p_surface
    )
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
      vkCreateWin32SurfaceKHR(vk_instance,&surface_create_info,p_allocators,p_surface),
      "win32 surface creation failed",
      "win32 surface created");

  return 1;
}

void vulkan_surface_destroy(
    VKInstance vk_instance,
    VkAllocationCallbacks* p_alloctors,
    VkSurfaceKHR  surface
    )
{
  VkDestroySurfaceKHR(vk_instance,surface,p_allocators);
}
