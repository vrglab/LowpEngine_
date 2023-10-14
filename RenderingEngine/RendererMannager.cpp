#include "lprdpch.h"

int LP_Export GetRendererType()
{
#ifdef _WIN32
	return RendererType::DirectX12;
#elif __APPLE__
	return RendererType::Metal;
#endif
#ifdef __gl_h_
	return RendererType::OpenGL;
#else
	return RendererType::Vulkan;
#endif
}
