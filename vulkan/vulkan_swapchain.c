#include "vulkan_swapchain.h"

b8 vulkan_swapchain_create(vulkan_t* p_vulkan,uint16_t width, uint16_t height)
{
  //vulkan->swapchain;
  vulkan->swapchain.image_format=VK_FORMAT_B8G8R8A8_SRGB;
  vulkan->swapchain.images_count=2;


  VkSwapchainCreateInfoKHR swapchain_create_info;
  swapchain_create_info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_create_info.pNext=NULL;
  swapchain_create_info.flags=0;
  swapchain_create_info.surface=p_vulkan->surface.handle;
  swapchain_create_info.minImageCount=2;
  swapchain_create_info.imageFormat=p_vulkan->swapchain.image_format;
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
  swapchain_create_info.pQueueFamilyIndices=&p_vulkan->global_queue_family_index;

  swapchain_create_info.preTransform=VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  swapchain_create_info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_create_info.presentMode=VK_PRESENT_MODE_IMMEDIATE_KHR;
  swapchain_create_info.clipped=VK_TRUE;
  swapchain_create_info.oldSwapchain=VK_NULL_HANDLE;
  
  vk_check_ex(vkCreateSwapchainKHR(p_vulkan->logical_device,&swapchain_create_info,p_vulkan->p_allocators,&p_vulkan->swapchain.handle),
      "swapchain creation failed!",
      "swapchain creation failed!");

  VkFenceCreateInfo fence_create_info;
  fence_create_info.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_create_info.pNext=0;
  fence_create_info.flags=0;
  vk_check_ex(
      vkCreateFence(p_vulkan->logical_device,&fence_create_info,p_vulkan->p_allocators,&p_vulkan->swapchain.fence),
      "swapchain fence creation failed ",
      "swapchain fence created");
  return  1;
}


b8 vulkan_swapchain_get_images(vulkan_t* p_vulkan) 
{
  vk_check(vkGetSwapchainImagesKHR(vulkan->logical_device,vulkan->swapchain.handle,&vulkan->swapchain.images_count,0),"getting swapchain image count failed");
  
  printf("swapchain images count =%d !\n",vulkan->swapchain.images_count);

  //allocate memory for swapchain images and their views
  p_vulkan->swapchain.p_images=darray_reserve(VkImage,p_vulkan->swapchain.images_count);
  p_vulkan->swapchain.p_images_views=darray_reserve(VkImageView,p_vulkan->swapchain.images_count);

  // get swapchain images
  vk_check_ex(
      vkGetSwapchainImagesKHR(vulkan->logical_device,vulkan->swapchain.handle,&vulkan->swapchain.images_count,vulkan->swapchain.p_images),
      "failed to get swapchain images!",
      "swapchain images retrieved !");

  // create swapchain images views
  vulkan_swapchain_create_images_views(p_vulkan);
  return 1;
}

b8 vulkan_swapchain_create_images_views(vulkan_t* p_vulkan)
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
    image_view_info.format=p_vulkan->swapchain.image_format;
    VkComponentMapping components={VK_COMPONENT_SWIZZLE_R,VK_COMPONENT_SWIZZLE_G,VK_COMPONENT_SWIZZLE_B,VK_COMPONENT_SWIZZLE_A};
    image_view_info.components=components;
    VkImageSubresourceRange subresource={VK_IMAGE_ASPECT_COLOR_BIT,0,VK_REMAINING_MIP_LEVELS,0,VK_REMAINING_ARRAY_LAYERS};
    image_view_info.subresourceRange=subresource;

    //create the views
    vk_check(
        vkCreateImageView(vulkan->logical_device,&image_view_info,vulkan->p_allocators,&vulkan->swapchain.p_images_views[count]),
        "image view creation failed !"); 
    }

  printf("images views created ! \n");
  return 1;
}

b8 vulkan_swapchain_get_presentable_image(vulkan_t* p_vulkan,uint32_t* p_image_index)
{
    // query available swapchain image
    vk_check(vkAcquireNextImageKHR(p_vulkan->logical_device,p_vulkan->swapchain.handle,UINT64_MAX,NULL,p_vulkan->swapchain.fence,p_image_index),"failed to acquire an image");

    vk_check(vkGetFenceStatus(p_vulkan->logical_device,p_vulkan->swapchain.fence),"failed getting fence status");

    vk_check(vkResetFences(p_vulkan->logical_device,1,&p_vulkan->swapchain.fence),"failed to reset fence status");
    return 1;
}


b8 vulkan_swapchain_present_image(vulkan_t* p_vulkan,uint32_t* p_image_index)    
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

  vk_check_ex(vkQueuePresentKHR(p_vulkan->global_queue,&present_info),"presentation failed","presentation success");
  return 1;
}

void vulkan_swapchain_destroy(vulkan_t* p_vulkan)
{
  //destroy fences

  vkDestroyFence(p_vulkan->logical_device,p_vulkan->swapchain.fence,p_vulkan->p_allocators);
  //destroy imageViews
  for(u64 i=0;i<darray_get_used(p_vulkan->swapchain.images_count);i++)
  {
    vkDestroyImageView(p_vulkan->logical_device,p_vulkan->swapchain.p_images_views[i],p_vulkan->p_allocators);
  }
  darray_destroy(p_vulkan->swapchain.p_images_views);

  ////destroy images
  darray_destroy(p_vulkan->swapchain.p_images);

  //destroy swapchain
  vkDestroySwapchainKHR(p_vulkan->logical_device,p_vulkan->swapchain.handle,p_vulkan->p_allocators);
}


