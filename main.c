#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "libs/SDL3/SDL.h"


#include "core/memory.h"
#include "core/darray.h"
#include "core/str.h"
#include "core/ecs/entity.h"
#include "core/ecs/component.h"
#include "core/ecs/event.h"


#include "platform/platform.h"

#include "renderer/renderer_backend.h"



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
  printf("window created \n");

  renderer_backend_initialization(
      &vulkan,
      window.instance_handle,
      window.window_handle,
      window.name,
      window.drawable_width,
      window.drawable_height
      );
  
  //darray_test();
  //str_test();
  //test_entity();
  //test_component();
  //event_test();


  SDL_ShowWindow(window.window);

  while(window.closed!=1)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if(event.type==SDL_EVENT_QUIT)
      {
        renderer_backend_shutdown(&vulkan);
        window.closed=1;
      }
    }
    

    // frame start
    //
    // query available swapchain image
    u32 image_index;
    vulkan_swapchain_get_presentable_image(
        vulkan.device.logical_device,
        vulkan.swapchain.handle,
        vulkan.swapchain.fence,
        &image_index
        );

    // render loop

    vulkan_command_begin_buffer(vulkan.command.p_command_buffers[0]);  
        
    // renderpass commands 
    
    vulkan_renderpass_begin(
        vulkan.command.p_command_buffers[0],
        vulkan.renderpass.handle,
        vulkan.p_framebuffers[image_index].handle,
        window.drawable_width,
        window.drawable_height
        );

    // record subpass command in here

    vulkan_renderpass_end(
        vulkan.command.p_command_buffers[0]
        );

    vulkan_command_end_buffer(vulkan.command.p_command_buffers[0]);

    // submit command 
    vulkan_command_submit(
        vulkan.command.command_buffer_count,
        vulkan.command.p_command_buffers,
        vulkan.global_queue.p_handles[0]
        );

    // wait until execution is done
    if(vkQueueWaitIdle(vulkan.global_queue.p_handles[0])!=VK_SUCCESS)
    {
      printf(" -queue execution failed ! \n");
      return -1;
    }

    // reset the command buffer
    vkResetCommandBuffer(vulkan.command.p_command_buffers[0],VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

    // present to the swapchain
    vulkan_swapchain_present_image(
        vulkan.global_queue.p_handles[0],
        &vulkan.swapchain.handle,
        &image_index
        );

    // end frame
  }
  return 0;
}
