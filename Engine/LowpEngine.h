#pragma once


#ifndef _lpEngine_ 
#define _lpEngine_
#include "Macros.h"

#ifdef _WIN32
#include <Windows.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3d11.h>
#include <d3d12.h>
#endif

#ifdef min
#undef min
#endif

#include <gl/GL.h>
#include <vulkan/vulkan.h>

//Windowing
#include "Windowing/Window.h"
#include "Windowing/Application.h"

#endif // !_lpEngine_ 
