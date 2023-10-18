/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*  Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                                     */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
class AssimpLoader
{
	public:
		static Mesh* LoadMesh(const char* file);
	private:
		static void processNode(const aiNode* node, const aiScene* scene, Mesh& mesh, bool root);
};

