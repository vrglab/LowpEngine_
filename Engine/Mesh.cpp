#include "lppch.h"
#include "LowpEngineCore.h"

Mesh::Mesh()
{
}

void Mesh::AddSubMesh(const Mesh& subMesh)
{
	submeshes.push_back(subMesh);
}
