#include "..\..\Header\Graphics\MeshManager.h"

GE::MeshManager::MeshManager()
{
}

GE::MeshManager::~MeshManager()
{
	for (auto& mesh : meshes)
	{
		delete mesh.second;
	}
}

void GE::MeshManager::Add(IMesh* newMesh, const std::string& name)
{
	meshes.insert(std::make_pair(name, newMesh));
}

GE::IMesh* GE::MeshManager::Get(const std::string& name)
{
	return meshes.at(name);
}
