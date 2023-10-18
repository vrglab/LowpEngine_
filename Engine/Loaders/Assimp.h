/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once
class AssimpLoader
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

