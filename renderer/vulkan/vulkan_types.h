#ifndef _VULKAN_TYPES_H
#define _VULKAN_TYPES_H
#include <stdio.h>
#include <vulkan/vulkan.h>
#include <windows.h>
#include <vulkan/vulkan_win32.h>
#include "defines.h"


#define vk_check(vk_status,message_f) assert_failure(vk_status==VK_SUCCESS,message_f)
#define vk_check_ex(vk_status,message_f,message_s) assert(vk_status==VK_SUCCESS,message_f,message_s)

#endif
