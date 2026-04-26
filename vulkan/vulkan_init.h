#ifndef VULKAN_INIT_H
#define VULKAN_INIT_H
#include "vulkan_types.h"

int create_vulkan_instance(vulkan_t* vulkan,char* name);

VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
);
#endif
