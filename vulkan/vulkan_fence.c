#include "vulkan_fence.h"

  VkFenceCreateInfo fence_create_info;
  fence_create_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_create_info.pNext=0;
  fence_create_info.flags=0;
  vk_check_ex(
      vkCreateFence(p_vulkan->logical_device,&fence_create_info,p_vulkan->p_allocators,&p_vulkan->swapchain.fence),
      "swapchain fence creation failed ",
      "swapchain fence created");
 


 vkDestroyFence(p_vulkan->logical_device,p_vulkan->swapchain.fence,p_vulkan->p_allocators);
  
