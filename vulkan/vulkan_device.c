#include "vulkan_device.h"

int get_physical_device(vulkan_t* vulkan)
{
  vulkan->physical_device_count=1;
  vulkan->gpu_id=0;
  vulkan->gpu_name="NVIDIA GeForce GTX 960";
  vulkan->global_queue_family_index=0;
  vulkan->global_queues_count=1;
 
  VkResult result =vkEnumeratePhysicalDevices(vulkan->instance,&vulkan->physical_device_count,&vulkan->physical_device);
  if(result!=VK_SUCCESS)
  {
    printf("error getting the GPU ! physical_device_count= %d\n",vulkan->physical_device_count);
    return -1;
  }
  printf("physical_device found !\n");
  return 0;
}

int create_logical_device(vulkan_t* vulkan)
{
  // queue create info
  
  VkDeviceQueueCreateInfo  queue_create_info;
  queue_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_info.pNext=NULL;
  queue_create_info.flags=0;
  queue_create_info.queueFamilyIndex=vulkan->global_queue_family_index;
  queue_create_info.queueCount=vulkan->global_queues_count;
  float queue_priority[1]={1.0f};
  queue_create_info.pQueuePriorities=queue_priority;

  //device create info
  const char* enabled_extension_names="VK_KHR_swapchain";
  VkDeviceCreateInfo device_create_info;
  device_create_info.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_create_info.pNext=NULL;
  device_create_info.flags=0;
  device_create_info.queueCreateInfoCount=1;
  device_create_info.pQueueCreateInfos=&queue_create_info;
  device_create_info.enabledLayerCount=0;
  device_create_info.ppEnabledLayerNames=0;
  device_create_info.enabledExtensionCount=1;
  device_create_info.ppEnabledExtensionNames=&enabled_extension_names;
  device_create_info.pEnabledFeatures=NULL;

  VkResult result=vkCreateDevice(vulkan->physical_device,&device_create_info,vulkan->p_allocators,&vulkan->logical_device);
  if(result!=VK_SUCCESS)
  {
    printf("logical device creation failed !\n");
    return -1;
  }
  printf("logical device creation success !\n");
  return 0;
}

int get_global_queue_from_logical_device(vulkan_t* vulkan)
{
  vkGetDeviceQueue(vulkan->logical_device,vulkan->global_queue_family_index,0,&vulkan->global_queue);
  if(vulkan->global_queue==NULL)
  {
    printf("error getting the global queue ! \n");
    return -1;
  }
  printf("global queue retrieved !\n");
  return 0;
}


