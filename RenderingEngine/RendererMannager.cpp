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

std::string LP_Export GetRendereTypeName(int renderer)
{
	switch (renderer)
	{
	case 0:
		return "OpenGL";
	case 1:
		return "DirectX12";
	case 2:
		return "Vulkan";
	case 3:
		return "Metal";
	}
}
