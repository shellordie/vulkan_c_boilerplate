#include "vulkan_instance.h"

b8 vulkan_init_create_instance(
    VkAllocationCallbacks* p_allocators,
    char* p_app_name,
    VkInstance* p_vk_instance,
    VkDebugUtilsMessengerEXT* p_debug_messenger
    )
{
  p_allocators=0;

  // app_info
  VkApplicationInfo app_info={};
  app_info.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext=NULL;
  app_info.pApplicationName=p_app_name;
  app_info.applicationVersion=VK_MAKE_VERSION(0,0,1);
  app_info.pEngineName=p_app_name;
  app_info.engineVersion=VK_MAKE_VERSION(0,0,1);
  app_info.apiVersion=VK_MAKE_VERSION(1,2,200);

  const char* layer_names[1]={"VK_LAYER_KHRONOS_validation"};
  const char* extension_names[3]={"VK_EXT_debug_utils","VK_KHR_surface","VK_KHR_win32_surface"};

  //debug_messenger_info
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_info;
  debug_messenger_info.sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_messenger_info.pNext=NULL;
  debug_messenger_info.flags=0;
  debug_messenger_info.messageSeverity=VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debug_messenger_info.messageType=VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT|VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_messenger_info.pfnUserCallback=debug_messenger_callback;
  debug_messenger_info.pUserData=NULL;


  VkInstanceCreateInfo instance_info={}; 
  instance_info.sType=VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_info.pNext=&debug_messenger_info;
  instance_info.flags=0;
  instance_info.pApplicationInfo=&app_info;
  instance_info.enabledLayerCount=1;
  instance_info.ppEnabledLayerNames=layer_names;
  instance_info.enabledExtensionCount=3;
  instance_info.ppEnabledExtensionNames=extension_names;
  vk_check_ex(
      vkCreateInstance(&instance_info,p_allocators,p_vk_instance),
      "create instance failed !",
      "vulkan instance created !"
      );

  PFN_vkCreateDebugUtilsMessengerEXT pfn_create_debug_utils_messenger =(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*p_vk_instance,"vkCreateDebugUtilsMessengerEXT");
  vk_check_ex(
      pfn_create_debug_utils_messenger(*p_vk_instance,&debug_messenger_info,p_allocators,p_debug_messenger),
      "debug messenger creation failed!",
      "debug messenger created!");
  return 1;
}

VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
)
{
  switch(message_severity)
  {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      printf("VULKAN WARNING : %s: %s \n",callback_data->pMessageIdName,callback_data->pMessage);
      break;

    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      printf("VULKAN ERROR : %s: %s \n",callback_data->pMessageIdName,callback_data->pMessage);
      break;
    default:
      printf("VULKAN DEBUG : %s: %s \n",callback_data->pMessageIdName,callback_data->pMessage);
  }
  return VK_TRUE;
}


void vulkan_instance_destroy(
    VkInstance vk_instance,
    VkAllocationCallbacks* p_allocators
    )
{
  vkDestroyInstance(vk_instance,p_allocators);
}



