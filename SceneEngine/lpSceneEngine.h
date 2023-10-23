/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#ifndef _lpEngine_Scene_Engine
#define _lpEngine_Scene_Engine
#include <LowpCommons.h>
#include <yaml-cpp/yaml.h>
#include "../Scripting/lpScriptingEngine.h"



LP_Export struct Scene
{
public:
	std::map<MonoBehaviour*, MonoObject*> created_objects = {};
	std::list<MonoBehaviour*> mono_behaviours_in_the_scene = {};
};

static Scene* activeScene;

#endif