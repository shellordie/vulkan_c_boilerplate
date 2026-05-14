#include "vulkan_framebuffer.h"

b8 vulkan_framebuffer_create(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkRenderPass renderpass,
    VkImageView* p_image_view,
    u16 width,
    u16 height,
    VkFramebuffer* p_framebuffer
    )
{
  VkFramebufferCreateInfo framebuffer_create_info;
  framebuffer_create_info.sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebuffer_create_info.pNext=0;
  framebuffer_create_info.flags=0;
  framebuffer_create_info.renderPass=renderpass;
  framebuffer_create_info.attachmentCount=1;
  framebuffer_create_info.pAttachments=p_image_view;

  framebuffer_create_info.width=width;
  framebuffer_create_info.height=height;
  framebuffer_create_info.layers=1;

  vk_check_ex(
      vkCreateFramebuffer(logical_device,&framebuffer_create_info,p_allocators,p_framebuffer),
      "framebuffer creation failed!",
      "framebuffer creation failed!"
      );
  return 1;
}

void vulkan_framebuffer_destroy(
    VkDevice logical_device,
    VkAllocationCallbacks* p_allocators,
    VkFramebuffer* p_framebuffer)
{

  vkDestroyFramebuffer(logical_device,p_framebuffer,p_allocators);
}


