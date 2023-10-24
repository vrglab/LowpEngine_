/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */

#ifndef lpEngine
#define lpEngine

#include <EngineCommons/LowpCommons.h>
#include <PhysicsEngine/lpPhysicsEngine.h>
#include <SoundSystem/LpSoundSystem.h>
#include <RenderingEngine/lpRenderingEngine.h>
#include <Scripting/lpScriptingEngine.h>

#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <assimp/Importer.hpp>
#include <assimp/Scene.h>
#include <assimp/Mesh.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include "AssimpLoader.h"

#include "GameInfo.h"

LP_Export class Game
{
public:
    Windowing* createdWindow;
    GameInfo* info;
    SoundSystem* soundSystem;
    RenderingFramework* renderingFramework;
    ScriptingEngine* scriptingEngine;
};


LP_Export int InitGame(GameInfo* initInfo, Game* game);

LP_Export int StartGame(Game* game);

LP_Export int CleanupGame(Game* game);

LP_Extern{
    LP_Export Mesh * Assimp_LoadMesh(const char* file);
}

#endif