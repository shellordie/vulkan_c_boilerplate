#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H
#include "vulkan_types.h"

b8 vulkan_instance_create(
    VkAllocationCallbacks* p_allocators,
    char* p_app_name,
    VkInstance* p_vk_instance,
    VkDebugUtilsMessengerEXT* p_debug_messenger
    );

void vulkan_instance_destroy(
    VkInstance vk_instance,
    VkAllocationCallbacks* p_allocators
    );

VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
);



#endif
