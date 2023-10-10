#pragma once
class AssimpLoader
{
	public:
		static Mesh* LoadMesh(const char* file);
	private:
		static void processNode(const aiNode* node, const aiScene* scene, Mesh& mesh, bool root);
};

