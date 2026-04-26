#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdio.h>
#include "libs/SDL3/SDL.h"
//#include <vulkan/vulkan.h>
//#include <vulkan/vulkan_win32.h>
#include <windows.h>

typedef struct window_t
{
  SDL_Window* window;
  uint16_t width;
  uint16_t height;
  uint32_t drawable_width;
  uint32_t drawable_height;
  HWND window_handle;
  HINSTANCE instance_handle;
  uint8_t closed;
  char* name;
}window_t;

int create_window(window_t* window);

#endif


