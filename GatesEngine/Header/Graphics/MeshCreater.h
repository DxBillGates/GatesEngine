#pragma once
#include "VertexData.h"
#include "MeshData.h"

#include <string>

namespace GE
{
	namespace MeshCreater
	{
		void CreatePlane(MeshData<Vertex_UV_Normal>& meshData, const Math::Vector2& size = { 1 }, const Math::Vector2& uvMax = { 1 });
		void Create2DPlane(MeshData<Vertex_UV>& meshData, const Math::Vector2& size = { 1 }, const Math::Vector2& uvMax = { 1 }, const Math::Vector2& center = { 0 });
		void CreateGrid(MeshData<Vertex_Color>& meshData, float spaceInterval = 100, const Math::Vector2& size = { 10000 });
		void CreateLine(MeshData<Vertex_Color>& meshData, const Math::Vector3& size = { 1 }, const Color& color = { 1 });
		void CreateLineCube(MeshData<Vertex_Color>& meshData, const Math::Vector3& size = { 1 }, const Color& color = { 1 });
		void CreateLineCircle(MeshData<Vertex_Color>& meshData,float vertexCount = 64, const Math::Vector3& size = { 1 }, const Color& color = { 1 });
		void CreateLineAxis(MeshData<Vertex_Color>& meshData, float size = 1);
		void LoadObjModelData(const std::string& filename, MeshData<Vertex_UV_Normal>& meshData);
	}
}
