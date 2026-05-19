#ifndef _VULKAN_COMMAND_H_
#define _VULKAN_COMMAND_H_
#include "vulkan_types.h"

b8 vulkan_command_create_pool(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    u32 queue_family_index,
    VkCommandPool* p_command_pool
    ); 

b8 vulkan_command_allocate_buffer(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkCommandPool command_pool,
    u32 command_buffer_count,
    VkCommandBuffer* p_command_buffers
    );

b8 vulkan_command_begin_buffer(VkCommandBuffer command_buffer);

b8 vulkan_command_end_buffer(VkCommandBuffer command_buffer);

b8 vulkan_command_submit(
    u32 command_buffer_count,
    VkCommandBuffer* p_command_buffers,
    VkQueue worker_queue
    );

void vulkan_command_destroy_pool(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkCommandPool command_pool
    );
#endif
