/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <EngineCommons/LowpCommons.h>
#include "Scene.h"
#include <unordered_map>
#include <unordered_set>

LP_Export class SceneManager
{
private:
	std::list<Scene*> LoadedScenes;

public:
	LP_Export void LoadSceneAsActive(Scene* scene);
	LP_Export void LoadSceneAsActive(int sceneIndex);
};