#include "renderer_backend.h" 

b8 renderer_backend_initialization(
    vulkan_t* p_vulkan,
    HINSTANCE hinstance_handle,
    HWND window_handle,
    char* p_app_name,
    u16 drawable_width,
    u16 drawable_height 
    )
{
  //vulkan instance
  vulkan_instance_create(
      p_vulkan->p_allocators,
      p_app_name,
      &p_vulkan->instance,
      &p_vulkan->debug_messenger);

  //create surface
  vulkan_surface_create(
      p_vulkan->instance,
      p_vulkan->p_allocators,
      hinstance_handle,
      window_handle,
      &p_vulkan->surface.handle
      );

  // get physical device
  vulkan_device_get_physical_device(
      p_vulkan->instance,
      &p_vulkan->device.physical_device
      );

  // creeate logical device
  u32 total_queue_count=1;
  p_vulkan->global_queue.count=1;
  p_vulkan->global_queue.family_index=0;
  p_vulkan->global_queue.p_handles=darray_reserve(VkQueue,p_vulkan->global_queue.count);

  vulkan_device_logical_device_create(
      p_vulkan->device.physical_device,
      p_vulkan->p_allocators,
      total_queue_count,
      &p_vulkan->global_queue.family_index,
      &p_vulkan->global_queue.count,
      &p_vulkan->device.logical_device
      );

  //get queue
  vulkan_device_get_queue(
      p_vulkan->device.logical_device,
      p_vulkan->global_queue.family_index,
      0,
      p_vulkan->global_queue.p_handles
      );

  // create command pool
  vulkan_command_create_pool(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->global_queue.family_index,
      &p_vulkan->command.command_pool
      );

  // allocate command buffer
  p_vulkan->command.command_buffer_count=1;
  p_vulkan->command.p_command_buffers=darray_reserve(VkCommandBuffer,p_vulkan->command.command_buffer_count);

  vulkan_command_allocate_buffer(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->command.command_pool,
      p_vulkan->command.command_buffer_count,
      p_vulkan->command.p_command_buffers
      ); 

  // create swapchain
  p_vulkan->swapchain.image_count=2;
  p_vulkan->swapchain.image_format=VK_FORMAT_B8G8R8A8_SRGB;

  vulkan_swapchain_create(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->surface.handle,
      p_vulkan->swapchain.image_format,
      p_vulkan->swapchain.image_count,
      1,
      &p_vulkan->global_queue.family_index,
      drawable_width,
      drawable_height,
      &p_vulkan->swapchain.handle
      );

  // vulkan swapchain get images
  
  p_vulkan->swapchain.p_images=darray_reserve(VkImage,p_vulkan->swapchain.image_count);
  vulkan_swapchain_get_images(
      p_vulkan->device.logical_device,
      p_vulkan->swapchain.handle,
      &p_vulkan->swapchain.image_count,
      p_vulkan->swapchain.p_images
      );

  // vulkan swapchain create images views

  p_vulkan->swapchain.p_image_views=darray_reserve(VkImageView,p_vulkan->swapchain.image_count);
  for(u32 i=0;i<p_vulkan->swapchain.image_count;i++)
  {
    vulkan_swapchain_create_image_view(
        p_vulkan->device.logical_device,
        p_vulkan->p_allocators,
        p_vulkan->swapchain.image_format,
        p_vulkan->swapchain.p_images[i],
        &p_vulkan->swapchain.p_image_views[i]
        );
  }
  // create swapchain fence
  vulkan_fence_create(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      &p_vulkan->swapchain.fence
      );

  // create render pass
  vulkan_renderpass_create(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->swapchain.image_format,
      &p_vulkan->renderpass.handle
      ); 

  // create frame buffers 

  p_vulkan->framebuffer.p_handles=darray_reserve(VkFramebuffer,p_vulkan->swapchain.image_count);

  for(u32 i=0;i<p_vulkan->swapchain.image_count;i++){
    vulkan_framebuffer_create(
        p_vulkan->device.logical_device,
        p_vulkan->p_allocators,
        p_vulkan->renderpass.handle,
        &p_vulkan->swapchain.p_image_views[i],
        drawable_width,
        drawable_height,
        &p_vulkan->framebuffer.p_handles[i]
        );
  }
  return 1;

}


void renderer_backend_shutdown(vulkan_t* p_vulkan)
{
  printf("destroying everything ... \n");
  vkDeviceWaitIdle(p_vulkan->device.logical_device);
  //destroy framebuffer
  for(u32 i=0;i<p_vulkan->swapchain.image_count;i++){
    vulkan_framebuffer_destroy(
        p_vulkan->device.logical_device,
        p_vulkan->p_allocators,
        p_vulkan->framebuffer.p_handles[i]
        );
  }
  darray_destroy(p_vulkan->framebuffer.p_handles);
  printf("framebuffers destroyed \n");

  //destroy renderpass
  vulkan_renderpass_destroy(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->renderpass.handle
      );
  printf("renderpass destroyed \n");

  // destroy swapchain fence
  vulkan_fence_destroy(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->swapchain.fence
      );
  printf("swapchain fence destroyed \n");

  // destroy swapchain 
  vulkan_swapchain_destroy( 
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->swapchain.handle,
      p_vulkan->swapchain.image_count,
      p_vulkan->swapchain.p_image_views
      );
  darray_destroy(p_vulkan->swapchain.p_image_views);
  darray_destroy(p_vulkan->swapchain.p_images);
  printf("swapchain destroyed \n");

  // destroy command pool
  vulkan_command_destroy_pool(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators,
      p_vulkan->command.command_pool
      );
  darray_destroy(p_vulkan->command.p_command_buffers);

  printf("commands destroyed \n");

  // destroy logical device
  vulkan_device_logical_device_destroy(
      p_vulkan->device.logical_device,
      p_vulkan->p_allocators
      );
  printf("logical device destroyed \n");

  // destroy surface destroy
  vulkan_surface_destroy(
      p_vulkan->instance,
      p_vulkan->p_allocators,
      p_vulkan->surface.handle
      );
  printf("surface destroyed \n");

  //destroy instance
  vulkan_instance_destroy(p_vulkan->instance,p_vulkan->debug_messenger,p_vulkan->p_allocators);
  printf("instance destroyed \n");
}


