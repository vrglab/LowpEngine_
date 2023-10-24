/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <LowpCommons.h>
#include "../Scripting/MonoBehaviour.h"
#include <unordered_map>
#include <unordered_set>

LP_Export struct Scene
{
public:
	std::map<MonoBehaviour*, MonoObject*> created_objects = {};
	std::list<MonoBehaviour*> mono_behaviours_in_the_scene = {};
	LP_Export void OnLoad();
	LP_Export void OnUnload();
};