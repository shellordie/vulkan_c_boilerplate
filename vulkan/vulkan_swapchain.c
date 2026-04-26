#include "vulkan_swapchain.h"

int create_swapchain(vulkan_t* vulkan,uint16_t width, uint16_t height)
{
  //vulkan->swapchain;
  vulkan->swapchain.image_format=VK_FORMAT_B8G8R8A8_SRGB;
  vulkan->swapchain.images_count=2;


  VkSwapchainCreateInfoKHR swapchain_create_info;
  swapchain_create_info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_create_info.pNext=NULL;
  swapchain_create_info.flags=0;
  swapchain_create_info.surface=vulkan->surface.handle;
  swapchain_create_info.minImageCount=2;
  swapchain_create_info.imageFormat=vulkan->swapchain.image_format;
  swapchain_create_info.imageColorSpace=VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

  VkExtent2D present_image;
  present_image.width=width;
  present_image.height=height;

  swapchain_create_info.imageExtent=present_image;
  swapchain_create_info.imageArrayLayers=1;
  swapchain_create_info.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
  swapchain_create_info.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swapchain_create_info.queueFamilyIndexCount=1;

  //uint32_t queue_indices=QUEUE_FAMILY_INDEX;
  swapchain_create_info.pQueueFamilyIndices=&vulkan->global_queue_family_index;

  swapchain_create_info.preTransform=VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  swapchain_create_info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_create_info.presentMode=VK_PRESENT_MODE_IMMEDIATE_KHR;
  swapchain_create_info.clipped=VK_TRUE;
  swapchain_create_info.oldSwapchain=VK_NULL_HANDLE;
  
  VkResult result=vkCreateSwapchainKHR(vulkan->logical_device,&swapchain_create_info,vulkan->p_allocators,&vulkan->swapchain.handle);

  if(result!=VK_SUCCESS)
  {
    printf("swapchain creation failed! \n");
    return -1;
  }

  if(result!=VK_SUCCESS)
  {
    printf("swapchain creation failed! \n");
    return -1;
  }

  VkFenceCreateInfo fence_create_info;
  fence_create_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_create_info.pNext=0;
  fence_create_info.flags=0;
  if(vkCreateFence(vulkan->logical_device,&fence_create_info,vulkan->p_allocators,&vulkan->swapchain.fence))
  {
    printf("swapchain fence creation failed \n");
    return -1;
  }
  printf("swapchain fence created \n");

  printf("swapchain created ! \n");
  return  0;
}


int get_swapchain_images(vulkan_t* vulkan) 
{
  VkResult result=vkGetSwapchainImagesKHR(vulkan->logical_device,vulkan->swapchain.handle,&vulkan->swapchain.images_count,0);
  if(result!= VK_SUCCESS)
  {
    return -1;
  }
  
  printf("swapchain images count =%d !\n",vulkan->swapchain.images_count);

  //allocate memory for swapchain images and their views
  vulkan->swapchain.p_images=malloc(vulkan->swapchain.images_count*sizeof(VkImage));
  vulkan->swapchain.p_images_views=malloc(vulkan->swapchain.images_count*sizeof(VkImageView));

  // get swapchain images
  result=vkGetSwapchainImagesKHR(vulkan->logical_device,vulkan->swapchain.handle,&vulkan->swapchain.images_count,vulkan->swapchain.p_images);
  if(result!= VK_SUCCESS)
  {
    printf("failed to get swapchain images !\n");
    return -1;
  }
  printf("swapchain images retrieved !\n");

  // create swapchain images views
  create_swapchain_images_views(vulkan);

  return 0;
}

int create_swapchain_images_views(vulkan_t* vulkan)
{
  uint8_t count;
  for(count=0;count<2;count++)
  {
    // image view info
    VkImageViewCreateInfo image_view_info;
    image_view_info.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    image_view_info.pNext=0;
    image_view_info.flags=0;
    image_view_info.image=vulkan->swapchain.p_images[count];
    image_view_info.viewType=VK_IMAGE_VIEW_TYPE_2D;
    image_view_info.format=vulkan->swapchain.image_format;
    VkComponentMapping components={VK_COMPONENT_SWIZZLE_R,VK_COMPONENT_SWIZZLE_G,VK_COMPONENT_SWIZZLE_B,VK_COMPONENT_SWIZZLE_A};
    image_view_info.components=components;
    VkImageSubresourceRange subresource={VK_IMAGE_ASPECT_COLOR_BIT,0,VK_REMAINING_MIP_LEVELS,0,VK_REMAINING_ARRAY_LAYERS};
    image_view_info.subresourceRange=subresource;

    //create the views
    VkResult result=vkCreateImageView(vulkan->logical_device,&image_view_info,vulkan->p_allocators,&vulkan->swapchain.p_images_views[count]);

    if(result!=VK_SUCCESS)
    {
      printf("image view creation failed ! \n"); 
      break;
    }

  }

  printf("images views created ! \n");
  return 0;
}

int get_presentable_image(vulkan_t* p_vulkan,uint32_t* p_image_index)
{
    // query available swapchain image
    if(vkAcquireNextImageKHR(p_vulkan->logical_device,p_vulkan->swapchain.handle,UINT64_MAX,NULL,p_vulkan->swapchain.fence,p_image_index)!=VK_SUCCESS)
    {
      printf(" -acquire presentable image failed \n");
      return -1;
    }

    if(vkGetFenceStatus(p_vulkan->logical_device,p_vulkan->swapchain.fence)==VK_SUCCESS)
    {
      printf(" -found presentable image \n");
    }

    if(vkResetFences(p_vulkan->logical_device,1,&p_vulkan->swapchain.fence)!=VK_SUCCESS)
    {
      printf(" -failed to reset fences !\n");
      return -1;
    }
    return 0;
}


int present_image(vulkan_t* p_vulkan,uint32_t* p_image_index)    
{
  VkResult swapchain_result;

  //present info
  VkPresentInfoKHR present_info;
  present_info.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.pNext=0;
  present_info.waitSemaphoreCount=0;
  present_info.pWaitSemaphores=0;
  present_info.swapchainCount=1;
  present_info.pSwapchains=&p_vulkan->swapchain.handle;
  present_info.pImageIndices=p_image_index;
  present_info.pResults=&swapchain_result;

  if(vkQueuePresentKHR(p_vulkan->global_queue,&present_info)!=VK_SUCCESS)
  {
    printf("presentation failed ! \n");
    return -1;
  }
  if(swapchain_result!=VK_SUCCESS)
  {
    printf("swapchain presentation failed ! \n");
    return -1;
  }
  else
  {
    printf("swapchain presentation success !\n");
  }

  printf("presentation done \n");
  return 0;
}


