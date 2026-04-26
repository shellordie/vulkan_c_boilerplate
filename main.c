#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "libs/SDL3/SDL.h"


#include "platform/platform.h"
#include "vulkan/vulkan_types.h"
#include "vulkan/vulkan_init.h"
#include "vulkan/vulkan_surface.h"
#include "vulkan/vulkan_device.h"
#include "vulkan/vulkan_command.h"
#include "vulkan/vulkan_swapchain.h"
#include "vulkan/vulkan_renderpass.h"
#include "vulkan/vulkan_framebuffer.h"



int main()
{
  window_t window;
  vulkan_t vulkan;
  
  window.window=0;
  window.width=800;
  window.height=600;
  window.drawable_width=0;
  window.drawable_height=0;
  window.window_handle=0;
  window.instance_handle=0;
  window.closed=0;
  window.name="vulkan_game";
  

  create_window(&window);
  create_vulkan_instance(&vulkan,window.name);
  create_surface(&vulkan,window.instance_handle,window.window_handle);
  get_physical_device(&vulkan);
  create_logical_device(&vulkan);
  get_global_queue_from_logical_device(&vulkan);
  create_command_pool(&vulkan);
  allocate_command_buffer(&vulkan); 
  create_swapchain(&vulkan,window.drawable_width,window.drawable_height);
  get_swapchain_images(&vulkan);
  create_renderpass(&vulkan); 
  create_framebuffer(&vulkan,window.drawable_width,window.drawable_height);

  SDL_ShowWindow(window.window);

  uint32_t max_frame=100;
  while(window.closed!=1)
  {
    SDL_Event event;
    /*
    if(max_frame==0)
    {
      printf("max frame reached !\n");
      break;
    }*/
    while (SDL_PollEvent(&event))
    {
      if(event.type==SDL_EVENT_QUIT)
      {
        window.closed=1;
      }
    }
    printf(" -frame start !\n ");

    // query available swapchain image
    uint32_t image_index;
    get_presentable_image(&vulkan,&image_index);

    // render loop
    VkCommandBufferBeginInfo command_buffer_begin_info;
    command_buffer_begin_info.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    command_buffer_begin_info.pNext=0;
    command_buffer_begin_info.flags=VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    command_buffer_begin_info.pInheritanceInfo=0;
    if(vkBeginCommandBuffer(vulkan.command_buffer,&command_buffer_begin_info)!=VK_SUCCESS)
    {
      printf(" -failed to begin the command buffer");
      return -1;
    }
    printf(" -command buffer begin ! \n");

    // renderpass commands 
    
    VkRenderPassBeginInfo renderpass_begin_info;
    renderpass_begin_info.sType=VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderpass_begin_info.pNext=0;
    renderpass_begin_info.renderPass=vulkan.renderpass;
    renderpass_begin_info.framebuffer=vulkan.framebuffer.p_handles[image_index];
    VkRect2D render_area={{0,0},{window.drawable_width,window.drawable_height}};
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
    vkCmdBeginRenderPass2(vulkan.command_buffer,&renderpass_begin_info,&subpass_begin_info);

    // record subpass command in here

    vkCmdEndRenderPass(vulkan.command_buffer);

    vkEndCommandBuffer(vulkan.command_buffer);

    printf(" -command buffer end  \n");

    // submit queue

    VkSubmitInfo submit_info;
    submit_info.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.pNext=0;
    submit_info.waitSemaphoreCount=0;
    submit_info.pWaitSemaphores=0;
    submit_info.commandBufferCount=1;
    submit_info.pCommandBuffers=&vulkan.command_buffer;
    submit_info.signalSemaphoreCount=0;
    submit_info.pSignalSemaphores=0;
    if(vkQueueSubmit(vulkan.global_queue,1,&submit_info,NULL)!=VK_SUCCESS)
    {
      printf(" -queue submission failed ! \n");
      return -1;
    }

    printf(" -command submitted ! \n");

    // wait until execution is done
    if(vkQueueWaitIdle(vulkan.global_queue)!=VK_SUCCESS)
    {
      printf(" -queue execution failed ! \n");
      return -1;
    }
    printf(" -command execution done ! \n");

    // reset the command buffer
    vkResetCommandBuffer(vulkan.command_buffer,VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);


    // present to the swapchain
    present_image(&vulkan,&image_index);
    // end frame


    printf(" -frame end \n");
    max_frame-=1;

  }
  
  return 0;
}
