#ifndef VULKAN_INIT_H
#define VULKAN_INIT_H
#include "vulkan_types.h"

b8 vulkan_init_create_instance(vulkan_t* p_vulkan,char* name);
void vulkan_init_destroy(vulkan_t* p_vulkan);

VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
);



#endif
