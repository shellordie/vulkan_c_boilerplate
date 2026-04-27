#include "vulkan_command.h"

int create_command_pool(vulkan_t* p_vulkan)
{
  VkCommandPoolCreateInfo command_pool_create_info;
  command_pool_create_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  command_pool_create_info.pNext=NULL;
  command_pool_create_info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  command_pool_create_info.queueFamilyIndex=p_vulkan->global_queue_family_index;
  VkResult result= vkCreateCommandPool(p_vulkan->logical_device,&command_pool_create_info,p_vulkan->p_allocators,&p_vulkan->command_pool);
  if(result!=VK_SUCCESS)
  {
    printf("command pool creation failed ! \n");
    return -1;
  }

  printf("command pool created !\n");
  return 0;
}

int allocate_command_buffer(vulkan_t* p_vulkan)
{ 
  VkCommandBufferAllocateInfo allocation_info;
  allocation_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocation_info.pNext=NULL;
  allocation_info.commandPool=p_vulkan->command_pool;
  allocation_info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocation_info.commandBufferCount=1;
  VkResult result=vkAllocateCommandBuffers(p_vulkan->logical_device,&allocation_info,&p_vulkan->command_buffer);
  if(result!=VK_SUCCESS)
  {
    printf("command buffer allocation failed !\n");
    return -1;
  }
  printf("command buffer allocated !\n");
  return  0;
}

int begin_command_buffer(vulkan_t vulkan)
{
  VkCommandBufferBeginInfo command_buffer_begin_info;
  command_buffer_begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  command_buffer_begin_info.pNext=0;
  command_buffer_begin_info.flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  command_buffer_begin_info.pInheritanceInfo=0;
  if(vkBeginCommandBuffer(vulkan.command_buffer,&command_buffer_begin_info)!=VK_SUCCESS)
  {
    printf(" -failed to begin the command buffer");
    return -1;
  }
  printf(" -command buffer begin ! \n");
  return 0;
}

int submit_command(vulkan_t vulkan)
{
  VkSubmitInfo submit_info;
  submit_info.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.pNext=0;
  submit_info.waitSemaphoreCount=0;
  submit_info.pWaitSemaphores=0;
  submit_info.commandBufferCount=1;
  submit_info.pCommandBuffers=&vulkan.command_buffer;
  submit_info.signalSemaphoreCount=0;
  submit_info.pSignalSemaphores=0;
  if(vkQueueSubmit(vulkan.global_queue,1,&submit_info,NULL)!=VK_SUCCESS)
  {
    printf(" -queue submission failed ! \n");
    return -1;
  }

  printf(" -queue submitted !\n");
  return 0;
}

