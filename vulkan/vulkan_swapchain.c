#include "vulkan_swapchain.h"

b8 vulkan_swapchain_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkSurfaceKHR surface,
    VkFormat image_format,
    u32 image_count,
    u32* p_queue_family_index,
    u16 width, 
    u16 height,
    VkSwapchainKHR* p_swapchain
    )
{

  VkSwapchainCreateInfoKHR swapchain_create_info;
  swapchain_create_info.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_create_info.pNext=NULL;
  swapchain_create_info.flags=0;
  swapchain_create_info.surface=surface;
  swapchain_create_info.minImageCount=image_count;
  swapchain_create_info.imageFormat=image_format;
  swapchain_create_info.imageColorSpace=VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

  VkExtent2D present_image;
  present_image.width=width;
  present_image.height=height;

  swapchain_create_info.imageExtent=present_image;
  swapchain_create_info.imageArrayLayers=1;
  swapchain_create_info.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
  swapchain_create_info.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swapchain_create_info.queueFamilyIndexCount=1;

  swapchain_create_info.pQueueFamilyIndices=p_queue_family_index;

  swapchain_create_info.preTransform=VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  swapchain_create_info.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_create_info.presentMode=VK_PRESENT_MODE_IMMEDIATE_KHR;
  swapchain_create_info.clipped=VK_TRUE;
  swapchain_create_info.oldSwapchain=VK_NULL_HANDLE;
  
  vk_check_ex(vkCreateSwapchainKHR(logical_device,&swapchain_create_info,p_allocators,p_swapchain),
      "swapchain creation failed!",
      "swapchain created!");
  return  1;
}


b8 vulkan_swapchain_get_images(
    VkDevice logical_device,
    VkSwapchainKHR swapchain,
    u32* p_image_count,
    VkImage* p_images,
    ) 
{
  vk_check(vkGetSwapchainImagesKHR(logical_device,swapchain,p_image_count,0),
      "getting swapchain image count failed!");

  printf("swapchain images count =%d !\n",*p_image_count);

  //allocate memory for swapchain images 
  p_images=darray_reserve(VkImage,*images_count);
  //p_vulkan->swapchain.p_images_views=darray_reserve(VkImageView,p_vulkan->swapchain.images_count);
  // get swapchain images
  vk_check_ex(
      vkGetSwapchainImagesKHR(logical_device,swapchain,p_image_count,p_images),
      "failed to get swapchain images!",
      "swapchain images retrieved !");

  // create swapchain images views
  //vulkan_swapchain_create_images_views(p_vulkan);
  return 1;
}

b8 vulkan_swapchain_create_image_view(
    VkDevice logical_device,
    VkAllocationsCallbacks* p_allocators,
    VkImage image,
    VkFormat image_format,
    VkImageView* p_image_view
    )
{
  // image view info
  VkImageViewCreateInfo image_view_info;
  image_view_info.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  image_view_info.pNext=0;
  image_view_info.flags=0;
  image_view_info.image=image;
  image_view_info.viewType=VK_IMAGE_VIEW_TYPE_2D;
  image_view_info.format=image_format;
  VkComponentMapping components={VK_COMPONENT_SWIZZLE_R,VK_COMPONENT_SWIZZLE_G,VK_COMPONENT_SWIZZLE_B,VK_COMPONENT_SWIZZLE_A};
  image_view_info.components=components;
  VkImageSubresourceRange subresource={VK_IMAGE_ASPECT_COLOR_BIT,0,VK_REMAINING_MIP_LEVELS,0,VK_REMAINING_ARRAY_LAYERS};
  image_view_info.subresourceRange=subresource;
  //create the views
  vk_check_ex(
      vkCreateImageView(logical_device,&image_view_info,p_allocators,p_image_view),
      "image view creation failed !",
      "image view created !"
      ); 
  return 1;
}

b8 vulkan_swapchain_get_presentable_image(
    VkDevice logical_device,
    VkSwapchainKHR swapchain,
    VkFence fence,
    u32* p_image_index)
{
  // query available swapchain image
  vk_check(vkAcquireNextImageKHR(logical_device,swapchain,UINT64_MAX,NULL,fence,p_image_index),
      "failed to acquire an image");

  vk_check(vkGetFenceStatus(logical_device,fence),"failed getting fence status");

  vk_check(vkResetFences(logical_device,1,&fence),"failed to reset fence status");
  return 1;
}


b8 vulkan_swapchain_present_image(
    VkQueue present_queue,
    VkSwapchainKHR* p_swapchain,
    u32* p_image_index
    )    
{
  VkResult swapchain_result;
  //present info
  VkPresentInfoKHR present_info;
  present_info.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.pNext=0;
  present_info.waitSemaphoreCount=0;
  present_info.pWaitSemaphores=0;
  present_info.swapchainCount=1;
  present_info.pSwapchains=p_swapchain;
  present_info.pImageIndices=p_image_index;
  present_info.pResults=&swapchain_result;

  vkQueuePresentKHR(global_queue,&present_info);

  vk_check_ex(swapchain_result,"presentation failed","presentation success");
  return 1;
}

void vulkan_swapchain_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkSwapchainKHR swapchain,
    u32 image_count,
    VkImage* p_images,
    VkImageView* p_image_views
    )
{
  assert_failure(p_images!=NULL,"p_images is NULL");
  assert_failure(p_image_views!=NULL,"p_image_views is NULL");
 //destroy imageViews
  for(u32 i=0;i<image_count;i++)
  {
    vkDestroyImageView(logical_device,p_images_views[i],p_allocators);
  }
  darray_destroy(p_images_views);
  ////destroy images
  darray_destroy(swapchain.p_images);
  //destroy swapchain
  vkDestroySwapchainKHR(logical_device,swapchain,p_allocators);
}


