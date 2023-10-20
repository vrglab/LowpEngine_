#include "lprdpch.h"
#include "lpRenderingEngine.h"

RenderingFramework::~RenderingFramework()
{
	delete(device);
	delete(factory);
	delete(main_swapchain);
	delete(command_queue);
	delete(command_allocator);
	delete(command_list);
	delete(root_signature);
	delete(pipeline_stat);
}
