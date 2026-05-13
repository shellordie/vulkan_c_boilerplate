#include "vulkan_renderpass.h"

b8 vulkan_renderpass_create(vulkan_t* p_vulkan)
{
  VkRenderPassCreateInfo renderpass_create_info;
  renderpass_create_info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_create_info.pNext=0;
  renderpass_create_info.flags=0;
  renderpass_create_info.attachmentCount=1;
  VkAttachmentDescription attach_description_array[1]=
  {
    {
      0,
      p_vulkan->swapchain.image_format,
      VK_SAMPLE_COUNT_1_BIT,
      VK_ATTACHMENT_LOAD_OP_CLEAR,
      VK_ATTACHMENT_STORE_OP_STORE,
      VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      VK_ATTACHMENT_STORE_OP_DONT_CARE,
      VK_IMAGE_LAYOUT_UNDEFINED,
      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    }
    
  };
  renderpass_create_info.pAttachments=attach_description_array;

  VkAttachmentReference color_attach_reference[1]=
  {
    {
      0,
      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    }
  };

  renderpass_create_info.subpassCount=1;
  VkSubpassDescription subpass_description[1]=
  {
    {
      0,
      VK_PIPELINE_BIND_POINT_GRAPHICS,
      0,
      0,
      1,
      color_attach_reference,
      0,
      0,
      0,
      0
    }
  };
  renderpass_create_info.pSubpasses=subpass_description;
  renderpass_create_info.dependencyCount=0;
  renderpass_create_info.pDependencies=0;

  vk_check_ex(
      vkCreateRenderPass(p_vulkan->logical_device,&renderpass_create_info,p_vulkan->p_allocators,&p_vulkan->renderpass),
      "renderpass creation failed!",
      "renderpass created !");
  return 1;
}

b8 vulkan_renderpass_begin(vulkan_t* p_vulkan,uint32_t image_index,uint32_t width,uint32_t height)
{
  VkRenderPassBeginInfo renderpass_begin_info;
  renderpass_begin_info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_begin_info.pNext=0;
  renderpass_begin_info.renderPass=p_vulkan->renderpass;
  renderpass_begin_info.framebuffer=p_vulkan->framebuffer.p_handles[image_index];
  VkRect2D render_area={{0,0},{width,height}};
  renderpass_begin_info.renderArea=render_area;
  renderpass_begin_info.clearValueCount=1;
  VkClearValue clear_value;
  clear_value.color.float32[0]=0.0f;
  clear_value.color.float32[1]=0.0f;
  clear_value.color.float32[2]=1.0f;
  clear_value.color.float32[3]=1.0f;
  renderpass_begin_info.pClearValues=&clear_value;

  VkSubpassBeginInfo subpass_begin_info;
  subpass_begin_info.sType=VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO;
  subpass_begin_info.pNext=0;
  subpass_begin_info.contents=VK_SUBPASS_CONTENTS_INLINE;

  vkCmdBeginRenderPass2(p_vulkan->command_buffer,&renderpass_begin_info,&subpass_begin_info);
  return 1;
}

b8 vulkan_renderpass_end(vulkan_t* p_vulkan)
{
  vkCmdEndRenderPass(p_vulkan->command_buffer);
  return 1;
}

void vulkan_renderpass_destroy(vulkan_t* p_vulkan)
{
  vkDestroyRenderpass(p_vulkan->logical_device,p_vulkan->renderapss,p_vulkan->p_allocators);
}

