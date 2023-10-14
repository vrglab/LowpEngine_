#pragma once


#ifndef _lpEngine_Renderer_
#define _lpEngine_Renderer_

enum LP_Export RendererType
{
	OpenGL = 0,
	DirectX11 = 1,
	DirectX12 = 2,
	Vulkan = 3,
	Metal = 4 
};

int LP_Export GetRendererType()
{
#ifdef _WIN32
	return RendererType::DirectX12;
#elif __APPLE__
	return RendererType::Metal;
#endif
	return RendererType::OpenGL;
}

#endif