run:
	clang -c  core/assert.c -o ./build/assert.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/ 
	clang -c  core/darray.c -o ./build/darray.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  core/memory.c -o ./build/memory.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  platform/platform.c -o ./build/platform.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_init.c -o ./build/vulkan_init.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_device.c -o ./build/vulkan_device.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_surface.c -o ./build/vulkan_surface.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_command.c -o ./build/vulkan_command.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_swapchain.c -o ./build/vulkan_swapchain.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_renderpass.c -o ./build/vulkan_renderpass.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  vulkan/vulkan_framebuffer.c -o ./build/vulkan_framebuffer.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/
	clang -c  main.c -o ./build/main.o  -I C:\VulkanSDK\1.4.321.1\Include -I ./ -I ./libs/

	clang  ./build/assert.o ./build/darray.o ./build/memory.o ./build/platform.o ./build/vulkan_init.o ./build/vulkan_device.o ./build/vulkan_surface.o ./build/vulkan_command.o ./build/vulkan_swapchain.o ./build/vulkan_renderpass.o ./build/vulkan_framebuffer.o ./build/main.o -o ./build/app.exe -L C:\VulkanSDK\1.4.321.1\Lib -L ./dlls/ -luser32 -lvulkan-1 -lsdl3
	./build/app.exe

	
