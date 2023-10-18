#pragma once


enum LP_Export RendererType
{
	OpenGL = 0,
	DirectX12 = 1,
	Vulkan = 2,
	Metal = 3 
};

int LP_Export GetRendererType();

std::string LP_Export GetRendereTypeName(int renderer);

LP_Export RenderingFramework* InitializeRendering(RenderingEngineCreateInfo* createInfo);