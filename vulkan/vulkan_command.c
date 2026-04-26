#include "vulkan_command.h"

int create_command_pool(vulkan_t* vulkan)
{
  VkCommandPoolCreateInfo command_pool_create_info;
  command_pool_create_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  command_pool_create_info.pNext=NULL;
  command_pool_create_info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  command_pool_create_info.queueFamilyIndex=vulkan->global_queue_family_index;
  VkResult result= vkCreateCommandPool(vulkan->logical_device,&command_pool_create_info,vulkan->p_allocators,&vulkan->command_pool);
  if(result!=VK_SUCCESS)
  {
    printf("command pool creation failed ! \n");
    return -1;
  }

  printf("command pool created !\n");
  return 0;
}

int allocate_command_buffer(vulkan_t* vulkan)
{ 
  VkCommandBufferAllocateInfo allocation_info;
  allocation_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocation_info.pNext=NULL;
  allocation_info.commandPool=vulkan->command_pool;
  allocation_info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocation_info.commandBufferCount=1;
  VkResult result=vkAllocateCommandBuffers(vulkan->logical_device,&allocation_info,&vulkan->command_buffer);
  if(result!=VK_SUCCESS)
  {
    printf("command buffer allocation failed !\n");
    return -1;
  }
  printf("command buffer allocated !\n");
  return  0;
}


