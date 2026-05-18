#include "vulkan_device.h"

b8 get_physical_device(VkInstance vk_instance,VkPhysicalDevice* p_physical_device)
{
  u32 device_count=1;
  vk_check_ex(
      vkEnumeratePhysicalDevices(vk_instance,&device_count,p_physical_device),
      "error getting the GPU ",
        "physical_device found !");
  return 1;
}

b8 vulkan_device_logical_device_create(
    VkPhysicalDevice physical_device,
    VkAllocationCallbacks* p_allocators,
    u32 queue_count,
    u32* p_queue_family_indices,
    u32* p_queue_per_family_counts,
    VkDevice* p_logical_device
    )
{
  // queue create info
   
  VkDeviceQueueCreateInfo* p_queue_create_info=darray_reserve(VkDeviceQueueCreateInfo,queue_count);
  for(u32 i=0;i<queue_count;i++)
  {
    VkDeviceQueueCreateInfo queue_create_info;
    queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.pNext=NULL;
    queue_create_info.flags=0;
    queue_create_info.queueFamilyIndex=p_queue_family_indices[i];
    queue_create_info.queueCount=p_queue_per_family_counts[i];
    float queue_priority[1]={1.0f};
    queue_create_info.pQueuePriorities=queue_priority;
    darray_push(p_queue_create_info,queue_create_info);
  }

  //device create info
  const char* enabled_extension_names="VK_KHR_swapchain";
  VkDeviceCreateInfo device_create_info;
  device_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_create_info.pNext=NULL;
  device_create_info.flags=0;
  device_create_info.queueCreateInfoCount=queue_count;
  device_create_info.pQueueCreateInfos=&p_queue_create_info;
  device_create_info.enabledLayerCount=0;
  device_create_info.ppEnabledLayerNames=0;
  device_create_info.enabledExtensionCount=1;
  device_create_info.ppEnabledExtensionNames=&enabled_extension_names;
  device_create_info.pEnabledFeatures=NULL;

  vk_check_ex(
      vkCreateDevice(physical_device,&device_create_info,p_allocators,p_logical_device),
      "logical device creation failed !",
      "logical device creation success !");

  darray_destroy(p_queue_create_info);
  return 1;
}

b8 vulkan_device_get_queue(
    VkDevice logical_device,
    u32 queue_family_index,
    u32_queue_index_in_family,
    VkQueue* p_queue
    )
{
  vk_check_ex(
      vkGetDeviceQueue(logical_device,queue_family_index,queue_index_in_family,p_queue),
      "error getting queue ! ",
      "queue retrieved !");
  return 1;
}

void vulkan_device_logical_device_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators
    )
{
  vkDeviceDestroy(logical_device,p_allocators);
}



