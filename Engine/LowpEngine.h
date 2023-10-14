#pragma once


#ifndef _lpEngine_ 
#define _lpEngine_
#include "Macros.h"
#include "PhysicsEngineCore.h"
#include "lprdpch.h"

#ifndef _lpEngine_Physics
#error  Physics engine not initialized
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
