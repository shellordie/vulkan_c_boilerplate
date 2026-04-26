#include "vulkan_surface.h"

int create_surface(vulkan_t* vulkan,HINSTANCE instance_handle,HWND window_handle)
{
  VkWin32SurfaceCreateInfoKHR surface_create_info;
  surface_create_info.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surface_create_info.flags=0;
  surface_create_info.pNext=NULL;
  surface_create_info.flags=0;
  surface_create_info.hinstance=instance_handle;
  surface_create_info.hwnd=window_handle;
  //
  VkResult result=vkCreateWin32SurfaceKHR(vulkan->instance,&surface_create_info,vulkan->p_allocators,&vulkan->surface.handle);

  (result!=VK_SUCCESS)?printf("win32 surface creation failed ! \n"):-1;

  printf("win32 surface created !\n");

  return 0;
}
