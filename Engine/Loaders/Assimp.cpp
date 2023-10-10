#include "lppch.h"
#include "Assimp.h"

Mesh* AssimpLoader::LoadMesh(const char* file)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		importer.FreeScene();
		return nullptr;
	}

    // Create a Mesh object to store the loaded data
    Mesh mesh = Mesh();

    // Process all the meshes in the scene and add them as submeshes to the main Mesh
    processNode(scene->mRootNode, scene, mesh);

    return &mesh;
}

void AssimpLoader::processNode(const aiNode* node, const aiScene* scene, Mesh& mesh)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];

        // Convert Assimp mesh data to your Mesh class data structure
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textureCoords;
        std::vector<unsigned int> indices;

        for (unsigned int j = 0; j < aiMesh->mNumVertices; ++j) {
            aiVector3D vertex = aiMesh->mVertices[j];
            vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));

            aiVector3D normal = aiMesh->mNormals[j];
            normals.push_back(glm::vec3(normal.x, normal.y, normal.z));

            if (aiMesh->HasTextureCoords(0)) {
                aiVector3D texCoord = aiMesh->mTextureCoords[0][j];
                textureCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
            }
        }

        for (unsigned int j = 0; j < aiMesh->mNumFaces; ++j) {
            aiFace face = aiMesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }

        // Create a submesh and add it to the main Mesh
        Mesh subMesh(vertices, normals, textureCoords, indices);
        mesh.AddSubMesh(subMesh);
    }

    // Recursively process child nodes
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, mesh);
    }
}

LP_Extern{
    LP_Export Mesh* Assimp_LoadMesh(const char* file) 
    {
        return AssimpLoader::LoadMesh(file);
    }
}