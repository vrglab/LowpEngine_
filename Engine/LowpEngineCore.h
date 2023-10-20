/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */

#ifndef lpEngine
#define lpEngine

#include <LowpCommons.h>
#include <lpPhysicsEngine.h>
#include <LpSoundSystem.h>
#include <lpRenderingEngine.h>

#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <assimp/Importer.hpp>
#include <assimp/Scene.h>
#include <assimp/Mesh.h>
#include <assimp/postprocess.h>

LP_Export struct Mesh
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    std::vector<unsigned int> indices;
    std::vector<Mesh> submeshes;

    Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec2>& textureCoords, const std::vector<unsigned int>& indices)
        : vertices(vertices), normals(normals), textureCoords(textureCoords), indices(indices) {}
    Mesh();
    void AddSubMesh(const Mesh&);
};

LP_Export class AssimpLoader
{
public:
    /// <summary>
    /// Loads a Mesh from the given file
    /// </summary>
    /// <param name="file">The path to the file</param>
    /// <returns>The loaded mesh</returns>
    static Mesh* LoadMesh(const char* file);
private:
    static void processNode(const aiNode* node, const aiScene* scene, Mesh& mesh, bool root);
};

struct LP_Export Resolution
{
    int width, height;
};

LP_Export struct GameInfo
{
    std::string name;
    std::string developer;
    std::string version;
    int flags;
    SoundSystemInitInfo soundSystemInfo;
    Resolution* resolution;
};

class LP_Export Windowing
{
private:
    SDL_Renderer* sdl_renderer;
    GameInfo* info;
    bool shouldClose = false;

public:
    Windowing(GameInfo*);
    ~Windowing();
    void ProcessEvents();
    void Open();
    void Close();
    bool ShouldClose();
    RenderingFramework* framework;
    SDL_Window* sdl_window;
};


LP_Export struct Game
{
    Windowing* createdWindow;
    GameInfo* info;
    SoundSystem* soundSystem;
    RenderingFramework* renderingFramework;
};


LP_Export int InitGame(GameInfo* initInfo, Game* game);

LP_Export int StartGame(Game* game);

LP_Export int CleanupGame(Game* game);

LP_Extern{
    LP_Export Mesh * Assimp_LoadMesh(const char* file);
}

#endif