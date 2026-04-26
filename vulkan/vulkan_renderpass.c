#include "vulkan_renderpass.h"

int create_renderpass(vulkan_t* vulkan)
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
      vulkan->swapchain.image_format,
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

  VkResult result=vkCreateRenderPass(vulkan->logical_device,&renderpass_create_info,vulkan->p_allocators,&vulkan->renderpass);
  if(result!= VK_SUCCESS)
  {
    printf("renderpass creation failed! \n");
    return -1;
  }
  printf("renderpass created !\n");
  return 0;
}


