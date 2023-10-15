#pragma once
class RenderingFramework
{
public:
	void* device;
	void* factory;
	void* main_swapchain;
	void* command_queue;
	void* command_allocator;
	void* command_list;
	void* root_signature;
	void* pipeline_stat;
	~RenderingFramework();
};

