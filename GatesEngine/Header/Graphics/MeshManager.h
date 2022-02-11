#pragma once
#include "IMesh.h"

#include <string>
#include <map>

namespace GE
{
	class MeshManager
	{
	private:
		std::map<std::string, IMesh*> meshes;
	public:
		MeshManager();
		~MeshManager();
		void Add(IMesh* newMesh, const std::string& name);
		IMesh* Get(const std::string& name);
	};
}