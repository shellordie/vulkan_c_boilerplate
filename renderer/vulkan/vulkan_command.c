#include "vulkan_command.h"

b8 vulkan_command_create_pool(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    u32 queue_family_index,
    VkCommandPool* p_command_pool
    )
{
  VkCommandPoolCreateInfo command_pool_create_info;
  command_pool_create_info.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  command_pool_create_info.pNext=NULL;
  command_pool_create_info.flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  command_pool_create_info.queueFamilyIndex=queue_family_index;
  vk_check_ex(
      vkCreateCommandPool(logical_device,&command_pool_create_info,p_allocators,p_command_pool),
      "command pool creation failed !",
      "command pool created !");
  return 1;
}

b8 vulkan_command_allocate_buffer(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkCommandPool command_pool,
    u32 command_buffer_count,
    VkCommandBuffer* p_command_buffers
    )
{ 

  VkCommandBufferAllocateInfo allocation_info;
  allocation_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocation_info.pNext=NULL;
  allocation_info.commandPool=command_pool;
  allocation_info.level=VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocation_info.commandBufferCount=command_buffer_count;
  vk_check_ex(
      vkAllocateCommandBuffers(logical_device,&allocation_info,p_command_buffers),
      "command buffer allocation failed !",
      "command buffer allocated !");
  return  1;
}

b8 vulkan_command_begin_buffer(VkCommandBuffer command_buffer)
{
  VkCommandBufferBeginInfo command_buffer_begin_info;
  command_buffer_begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  command_buffer_begin_info.pNext=0;
  command_buffer_begin_info.flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  command_buffer_begin_info.pInheritanceInfo=0;
  vk_check(
      vkBeginCommandBuffer(command_buffer,&command_buffer_begin_info),
      "failed to begin the command buffer");
  return 1;
}

b8 vulkan_command_end_buffer(VkCommandBuffer command_buffer)
{
  vkEndCommandBuffer(command_buffer);
  return 1;
}

b8 vulkan_command_submit(
    u32 command_buffer_count,
    VkCommandBuffer* p_command_buffers,
    VkQueue worker_queue
    )
{
  VkSubmitInfo submit_info;
  submit_info.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.pNext=0;
  submit_info.waitSemaphoreCount=0;
  submit_info.pWaitSemaphores=0;
  submit_info.commandBufferCount=command_buffer_count;
  submit_info.pCommandBuffers=p_command_buffers;
  submit_info.signalSemaphoreCount=0;
  submit_info.pSignalSemaphores=0;
  vk_check(
      vkQueueSubmit(worker_queue,1,&submit_info,NULL),
      "queue submission failed !");
  return 1;
}

void vulkan_command_destroy_pool(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkCommandPool command_pool
    )
{
  vkDestroyCommandPool(logical_device,command_pool,p_allocators);
}

