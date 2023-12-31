/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
#include <EngineCommons/LowpCommons.h>
#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <vector>

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