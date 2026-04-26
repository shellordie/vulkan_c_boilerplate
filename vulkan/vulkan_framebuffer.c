#include "vulkan_framebuffer.h"

int create_framebuffer(vulkan_t* vulkan,uint16_t width,uint16_t height)
{
  int result;
  //allocate framebuffer handles
  vulkan->framebuffer.p_handles=malloc(vulkan->swapchain.images_count*sizeof(VkFramebuffer)); 

  for(uint32_t i=0;i<vulkan->swapchain.images_count;i++)
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

    VkResult result=vkCreateFramebuffer(vulkan->logical_device,&framebuffer_create_info,vulkan->p_allocators,&vulkan->framebuffer.p_handles[i]);

    if(result!= VK_SUCCESS)
    {
      result=-1;
      printf("framebuffer creation failed! \n");
      break;
    }
    result=0;
  }

  
  if(result!=0)
  {
    return -1;
  } 
  printf("framebuffers created !\n");
  
  return 0;
}


