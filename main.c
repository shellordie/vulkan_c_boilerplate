#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "libs/SDL3/SDL.h"


#include "core/memory.h"
#include "core/darray.h"
#include "core/str.h"
#include "core/ecs/entity.h"
#include "core/ecs/component.h"


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


  //darray_test();
  //str_test();
  entities_t entities_db;
  test_entity(&entities_db);
  test_component(&entities_db);


  SDL_ShowWindow(window.window);

  while(window.closed!=1)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if(event.type==SDL_EVENT_QUIT)
      {
        window.closed=1;
      }
    }

    // frame start
    //
    // query available swapchain image
    uint32_t image_index;
    get_presentable_image(&vulkan,&image_index);

    // render loop

    begin_command_buffer(vulkan);  
        
    // renderpass commands 
    
    begin_renderpass(vulkan,image_index,window.drawable_width,window.drawable_height);

    // record subpass command in here

    vkCmdEndRenderPass(vulkan.command_buffer);

    vkEndCommandBuffer(vulkan.command_buffer);

    // submit command 
    submit_command(vulkan);

    // wait until execution is done
    if(vkQueueWaitIdle(vulkan.global_queue)!=VK_SUCCESS)
    {
      printf(" -queue execution failed ! \n");
      return -1;
    }

    // reset the command buffer
    vkResetCommandBuffer(vulkan.command_buffer,VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

    // present to the swapchain
    present_image(&vulkan,&image_index);

    // end frame

  }
  
  return 0;
}
