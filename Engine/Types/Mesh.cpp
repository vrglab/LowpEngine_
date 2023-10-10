#include "lppch.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

void Mesh::AddSubMesh(const Mesh& subMesh)
{
	submeshes.push_back(subMesh);
}
