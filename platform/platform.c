#include "platform.h"

int create_window(window_t* window)
  {
    if(SDL_Init(SDL_INIT_VIDEO)==0)
    {
      printf("sdl initialization failed \n");
      return -1;
    }

    window->window=SDL_CreateWindow(window->name,window->width,window->height,0);
    if(window->window ==NULL)
    {
      printf("sdl window creation failed \n");
      return -1;
    }

    // 
    SDL_PropertiesID properties_group; 
    properties_group=SDL_GetWindowProperties(window->window);
    if(properties_group==0)
    {
      printf("failed to retrieve properties group \n");
      return -1;
    }

    void* hwnd_ptr=SDL_GetPointerProperty(properties_group,SDL_PROP_WINDOW_WIN32_HWND_POINTER,0);
    if(hwnd_ptr==NULL)
    {
      printf("failed to retrieve HWND pointer \n");
      return -1;
    }

    void* instance_ptr=SDL_GetPointerProperty(properties_group,SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER,0);

    if(instance_ptr==NULL)
    {
      printf("failed to retrieve HINSTANCE pointer \n");
      return -1;
    }

    window->window_handle=(HWND)(hwnd_ptr);
    window->instance_handle=(HINSTANCE)(instance_ptr);

    // get drawable rect
    
    int w,h;
    if(SDL_GetWindowSizeInPixels(window->window,&w,&h)==0)
    {
      printf("failed to retrieve drawable size \n");
    }
    printf("drawable w =%d,h=%d \n",w,h);
    window->drawable_width=(uint32_t)w;
    window->drawable_height=(uint32_t)h;

    printf("sdl window created ! \n");
    return 0;
}

