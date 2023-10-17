#pragma once
struct RenderingEngineCreateInfo
{
public:
	int rendererType;
	SDL_Window* window;
	VkApplicationInfo vulkan_app_info = {};
};

