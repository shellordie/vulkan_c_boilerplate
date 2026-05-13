#include "vulkan_framebuffer.h"

b8 vulkan_framebuffer_create(vulkan_t* p_vulkan,uint16_t width,uint16_t height)
{
  //allocate framebuffer handles
  p_vulkan->framebuffer.p_handles=darary_reserve(VkFramebuffer,p_vulkan->swapchain.images_count); 

  for(uint32_t i=0;i<p_vulkan->swapchain.images_count;i++)
  {
    printf("i=%d \n",i);
    VkFramebufferCreateInfo framebuffer_create_info;
    framebuffer_create_info.sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_create_info.pNext=0;
    framebuffer_create_info.flags=0;
    framebuffer_create_info.renderPass=vulkan->renderpass;
    framebuffer_create_info.attachmentCount=1;
    framebuffer_create_info.pAttachments=&vulkan->swapchain.p_images_views[i];

    framebuffer_create_info.width=width;
    framebuffer_create_info.height=height;
    framebuffer_create_info.layers=1;

    vk_check(vkCreateFramebuffer(p_vulkan->logical_device,&framebuffer_create_info,vulkan->p_allocators,&p_vulkan->framebuffer.p_handles[i]),"framebuffer creation failed!");
  }

  printf("framebuffers created !\n");
  return 0;
}

void vulkan_framebuffer_destroy(vulkan_t* p_vulkan)
{
  for(u64 i=0;i<darray_get_used(p_vulkan->framabuffer.p_handles);i++)
  {
    if(p_vulkan->framabuffer.p_handles[i]!=NULL)
    {
      vkDestroyFramebuffer(p_vulkan->logical_device,p_vulkan->framebuffer.p_handles[i],p_vulkan->p_allocators);
      p_vulkan->framabuffer.p_handles[i]=NULL;
    }
  }
}


