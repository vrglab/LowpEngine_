#pragma once
class RenderingFramework
{
public:
	void* device = nullptr;
	void* factory = nullptr;
	void* main_swapchain = nullptr;
	void* command_queue = nullptr;
	void* command_allocator = nullptr;
	void* command_list = nullptr;
	void* root_signature = nullptr;
	void* pipeline_stat = nullptr;
	~RenderingFramework();
};

