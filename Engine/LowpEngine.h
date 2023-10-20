/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_ 
#define _lpEngine_

#ifndef _lpEngine_assimp
#define _lpEngine_assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#include "Macros.h"
#include "PhysicsEngineCore.h"
#include "RenderingEngine.h"
#include "LpSoundSystem.h"

#ifndef _lpEngine_Physics
#error  Physics engine not initialized
#endif
struct AppInfo
{
	std::string name;
	std::string version;
	std::string developer;
	std::string publisher;
	int resWidth;
	int resHeight;
	int flags;
	SoundSystemInitInfo soundSystem;
};

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
