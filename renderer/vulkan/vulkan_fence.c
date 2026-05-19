#include "vulkan_fence.h"


b8 vulkan_fence_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFence* p_fence
    )
{
  VkFenceCreateInfo fence_create_info;
  fence_create_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_create_info.pNext=0;
  fence_create_info.flags=0;
  vk_check_ex(
      vkCreateFence(logical_device,&fence_create_info,p_allocators,p_fence),
      "swapchain fence creation failed !",
      "swapchain fence created !");
  return 1;
}

void vulkan_fence_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFence fence)
{
  vkDestroyFence(logical_device,fence,p_allocators);
}

  
