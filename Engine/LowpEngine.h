#pragma once


#ifndef _lpEngine_ 
#define _lpEngine_
#include "Macros.h"
#include "Core.h"

#ifndef _lpEngine_Physics
#error  Physics engine not initialized
#endif

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

#ifdef __APPLE__ 
#include <metal/Foundation/Foundation.hpp>
#include <metal/Metal/Metal.hpp>
#include <metal/MetalFX/MetalFX.hpp>
#include <metal/QuartzCore/QuartzCore.hpp>
#endif

//Windowing
#include "Windowing/Window.h"

//Meshing
#include "Types/Mesh.h"
#include "Loaders/Assimp.h"

//Rendering
#include "Rendering/Renderer.h"

//Application Handling
#include "Application Handling/Application.h"

#endif // !_lpEngine_ 
