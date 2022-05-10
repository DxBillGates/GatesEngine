#include "..\..\Header\Graphics\MeshCreater.h"
#include "..\..\Header\Util\Math\Math.h"

#include <fstream>
#include <sstream>
#pragma comment(lib,"winmm.lib")

void GE::MeshCreater::CreatePlane(MeshData<Vertex_UV_Normal>& meshData, const Math::Vector2& size, const Math::Vector2& uvMax)
{
	std::vector<Vertex_UV_Normal>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	using namespace Math;
	vertices->push_back({ Vector3(-size.x / 2.0f,0, size.y / 2.0f),Vector2(0,0),Vector3(0,1,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,0, size.y / 2.0f),Vector2(uvMax.x,0),Vector3(0,1,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,0,-size.y / 2.0f),Vector2(uvMax.x,uvMax.y),Vector3(0,1,0) });
	vertices->push_back({ Vector3(-size.x / 2.0f,0,-size.y / 2.0f),Vector2(0,uvMax.y),Vector3(0,1,0) });

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
}

void GE::MeshCreater::Create2DPlane(MeshData<Vertex_UV>& meshData, const Math::Vector2& size, const Math::Vector2& uvMax, const Math::Vector2& center)
{
	std::vector<Vertex_UV>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	Math::Vector3 pivot = { -center.x,-center.y,0 };
	pivot = Math::Vector3::Max(pivot, Math::Vector3(1) / 2);
	pivot = Math::Vector3::Min(pivot, -Math::Vector3(1) / 2);
	pivot.x *= size.x;
	pivot.y *= size.y;

	using namespace Math;
	vertices->push_back({ Vector3(-size.x / 2.0f,-size.y / 2.0f,0) + pivot,Vector2(0,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,-size.y / 2.0f,0) + pivot,Vector2(uvMax.x,0) });
	vertices->push_back({ Vector3(size.x / 2.0f,size.y / 2.0f,0) + pivot,Vector2(uvMax.x,uvMax.y) });
	vertices->push_back({ Vector3(-size.x / 2.0f,size.y / 2.0f,0) + pivot,Vector2(0,uvMax.y) });

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);
	indices->push_back(0);
}

void GE::MeshCreater::CreateGrid(MeshData<Vertex_Color>& meshData, float spaceInterval, const Math::Vector2& size)
{
	int width = (int)(size.x / spaceInterval);
	int depth = (int)(size.y / spaceInterval);

	std::vector<Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	Math::Vector2 offset = Math::Vector2(-size.x / 2, -size.y / 2);
	Math::Vector2 maxOffset = size / 2;

	for (int w = 0; w <= width; ++w)
	{
		float x = w * spaceInterval;
		Color color = { 0.5f,0.5f,0.5f,1 };
		if (offset.x + x == 0)color = { 0,0,1,1 };
		vertices->push_back({ Math::Vector3(offset.x + x,0,offset.y),color });
		vertices->push_back({ Math::Vector3(offset.x + x,0,maxOffset.y),color });
	}

	for (int d = 0; d <= depth; ++d)
	{
		float z = d * spaceInterval;
		Color color = { 0.5f,0.5f,0.5f,1 };
		if (offset.y + z == 0)color = { 1,0,0,1 };
		vertices->push_back({ Math::Vector3(offset.x,0   ,offset.y + z),color });
		vertices->push_back({ Math::Vector3(maxOffset.x,0,offset.y + z),color });
	}

	for (int i = 0; i < (int)vertices->size(); i += 2)
	{
		indices->push_back(i);
		indices->push_back(i + 1);
	}
}

void GE::MeshCreater::CreateLine(MeshData<Vertex_Color>& meshData, const Math::Vector3& size, const Color& color)
{
	std::vector<Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	vertices->push_back({ Math::Vector3(0,0,0),color });
	vertices->push_back({ Math::Vector3(0,0,1),color });

	indices->push_back(0);
	indices->push_back(1);
}

void GE::MeshCreater::CreateLineCube(MeshData<Vertex_Color>& meshData, const Math::Vector3& size, const Color& color)
{
	std::vector<Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	//前
	vertices->push_back({ Math::Vector3(-size.x / 2.0f, size.y / 2.0f,-size.z / 2.0f),color });
	vertices->push_back({ Math::Vector3(size.x / 2.0f, size.y / 2.0f,-size.z / 2.0f), color });
	vertices->push_back({ Math::Vector3(size.x / 2.0f,-size.y / 2.0f,-size.z / 2.0f), color });
	vertices->push_back({ Math::Vector3(-size.x / 2.0f,-size.y / 2.0f,-size.z / 2.0f),color });
	//奥
	vertices->push_back({ Math::Vector3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f), color });
	vertices->push_back({ Math::Vector3(-size.x / 2.0f, size.y / 2.0f, size.z / 2.0f),color });
	vertices->push_back({ Math::Vector3(-size.x / 2.0f,-size.y / 2.0f, size.z / 2.0f),color });
	vertices->push_back({ Math::Vector3(size.x / 2.0f,-size.y / 2.0f, size.z / 2.0f), color });

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(3);

	indices->push_back(1);
	indices->push_back(4);
	indices->push_back(4);
	indices->push_back(7);
	indices->push_back(7);
	indices->push_back(2);

	indices->push_back(4);
	indices->push_back(5);
	indices->push_back(5);
	indices->push_back(6);
	indices->push_back(6);
	indices->push_back(7);

	indices->push_back(5);
	indices->push_back(0);
	indices->push_back(0);
	indices->push_back(3);
	indices->push_back(3);
	indices->push_back(6);
}

void GE::MeshCreater::CreateLineCircle(MeshData<Vertex_Color>& meshData, float vertexCount, const Math::Vector3& size, const Color& color)
{
	std::vector<Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	for (int i = 0; i < vertexCount; ++i)
	{
		Math::Vector3 pos;
		pos.x = size.x * sinf((2 * Math::PI / vertexCount) * i) / 2;
		pos.y = 0;
		pos.z = size.x * cosf((2 * Math::PI / vertexCount) * i) / 2;
		vertices->push_back({ pos,color });

		indices->push_back(i);
		int index = (i >= vertexCount - 1) ? 0 : i + 1;
		indices->push_back(index);
	}
}

void GE::MeshCreater::CreateLineAxis(MeshData<Vertex_Color>& meshData, float size)
{
	std::vector<Vertex_Color>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	vertices->push_back({ Math::Vector3(),Color::Red() });
	vertices->push_back({ Math::Vector3(size,0,0),Color::Red() });
	vertices->push_back({ Math::Vector3(),Color::Green() });
	vertices->push_back({ Math::Vector3(0,size,0),Color::Green() });
	vertices->push_back({ Math::Vector3(),Color::Blue() });
	vertices->push_back({ Math::Vector3(0,0,size),Color::Blue() });

	for (int i = 0; i < 3; ++i)
	{
		int offset = i * 2;
		indices->push_back(offset);
		indices->push_back(offset + 1);
	}
}

void GE::MeshCreater::LoadObjModelData(const std::string& filename, MeshData<Vertex_UV_Normal>& meshData)
{
	std::vector<Vertex_UV_Normal>* vertices = meshData.GetVertices();
	std::vector<unsigned int>* indices = meshData.GetIndices();

	std::string  filepath = filename + ".obj";
	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector2> uvies;
	std::vector<Math::Vector3> normals;
	int startIndex = 0;

	std::ifstream file;
	file.open(filepath);
	if (file.fail())return;
	std::string line;
	while (std::getline(file, line))    //ファイルから1行づつ読み込む
	{
		std::istringstream line_stream(line);    //getlineで読み込めるようにstringからstreamに変換する
		std::string key;
		std::getline(line_stream, key, ' ');    //line_streamから空白文字が出力されるまでkeyに入力する
		if (key == "v")    //頂点座標の読み込み
		{
			Math::Vector3 pos;
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			//positions.push_back(pos);    //単なるfloatなどならpush_backでもOK
			positions.emplace_back(pos);    //クラスや構造体の場合emplace_backのほうが早い
		}
		if (key == "vt")    //テクスチャ座標の読み込み
		{
			Math::Vector2 uv;
			line_stream >> uv.x;
			line_stream >> uv.y;
			uvies.emplace_back(uv);
		}
		if (key == "vn")    //法線情報の読み込み
		{
			Math::Vector3 normal;
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			normals.emplace_back(normal);
		}
		if (key == "f")    //v,vt,vnの組み合わせを生成
		{
			std::string index_word;
			std::string index;
			int number;
			std::vector<int> localIndices;
			int vCount = 0;
			while (std::getline(line_stream, index_word, ' '))
			{
				std::istringstream indexWord_stream(index_word);
				while (std::getline(indexWord_stream, index, '/'))
				{
					std::istringstream index_stream(index);
					index_stream >> number;
					localIndices.push_back(number - 1);
				}
				++vCount;
			}

			//頂点情報を組み合わせる
			for (int i = 0; i < (int)localIndices.size(); i += 3)
			{
				int v, vt, vn;
				v = localIndices[i];
				vt = localIndices[(uint64_t)i + 1];
				vn = localIndices[(uint64_t)i + 2];
				vertices->emplace_back(positions[v], uvies[vt], normals[vn]);
			}
			//面情報からインデックスを作る
			//4頂点と3頂点で分岐
			//4頂点なら6個追加
			if (vCount == 4)
			{
				indices->push_back(startIndex);
				indices->push_back(startIndex + 1);
				indices->push_back(startIndex + 2);
				indices->push_back(startIndex + 2);
				indices->push_back(startIndex + 3);
				indices->push_back(startIndex);
				startIndex += vCount;
			}
			//3頂点なら3個追加
			if (vCount == 3)
			{
				indices->push_back(startIndex);
				indices->push_back(startIndex + 1);
				indices->push_back(startIndex + 2);
				startIndex += vCount;
			}
		}
	}
	file.close();
}
