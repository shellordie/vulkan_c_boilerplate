#include "vulkan_command.h"

b8 vulkan_command_create_pool(vulkan_t* p_vulkan)
{
  VkCommandPoolCreateInfo command_pool_create_info;
  command_pool_create_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  command_pool_create_info.pNext=NULL;
  command_pool_create_info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  command_pool_create_info.queueFamilyIndex=p_vulkan->global_queue_family_index;
  vk_check_ex(
      vkCreateCommandPool(p_vulkan->logical_device,&command_pool_create_info,p_vulkan->p_allocators,&p_vulkan->command.command_pool),
      "command pool creation failed !",
      "command pool created !");
  return 1;
}

b8 vulkan_command_allocate_buffer(vulkan_t* p_vulkan)
{ 
  VkCommandBufferAllocateInfo allocation_info;
  allocation_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocation_info.pNext=NULL;
  allocation_info.commandPool=p_vulkan->command_pool;
  allocation_info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocation_info.commandBufferCount=1;
  vk_check_ex(
      vkAllocateCommandBuffers(p_vulkan->logical_device,&allocation_info,&p_vulkan->command.command_buffer),
      "command buffer allocation failed !",
      "command buffer allocated !");
  return  1;
}

b8 vulkan_command_begin_buffer(vulkan_t vulkan)
{
  VkCommandBufferBeginInfo command_buffer_begin_info;
  command_buffer_begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  command_buffer_begin_info.pNext=0;
  command_buffer_begin_info.flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  command_buffer_begin_info.pInheritanceInfo=0;
  vk_check(vkBeginCommandBuffer(vulkan.command.command_buffer,&command_buffer_begin_info),"failed to begin the command buffer");
  return 1;
}

b8 vulkan_command_end_buffer(vulkan_t vulkan)
{
  vkEndCommandBuffer(vulkan.command.command_buffer);
  return 1;
}

b8 vulkan_command_submit(vulkan_t vulkan)
{
  VkSubmitInfo submit_info;
  submit_info.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.pNext=0;
  submit_info.waitSemaphoreCount=0;
  submit_info.pWaitSemaphores=0;
  submit_info.commandBufferCount=1;
  submit_info.pCommandBuffers=&vulkan.command.command_buffer;
  submit_info.signalSemaphoreCount=0;
  submit_info.pSignalSemaphores=0;
  vk_check_ex(
      vkQueueSubmit(vulkan.global_queue,1,&submit_info,NULL),
      "queue submission failed !",
      "queue submited!");
  return 1;
}

void vulkan_command_destroy(vulkan_t* p_vulkan)
{
  vkDestroyCommandPool(p_vulkan->logical_device,p_vulkan->command.command_pool,p_vulkan->p_allocators);
}

