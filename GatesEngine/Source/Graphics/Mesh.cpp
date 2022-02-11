#include "..\..\Header\Graphics\Mesh.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::Mesh::Mesh()
	: vBuffer(nullptr)
	, iBuffer(nullptr)
	, vbView(D3D12_VERTEX_BUFFER_VIEW())
	, ibView(D3D12_INDEX_BUFFER_VIEW())
	, indicesCount(0)
	, device(nullptr)
	, cmdList(nullptr)
{
}

GE::Mesh::~Mesh()
{
	COM_RELEASE(vBuffer);
	COM_RELEASE(iBuffer);
}

void GE::Mesh::Draw(unsigned int instanceCount)
{
	cmdList->IASetIndexBuffer(&ibView);
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	cmdList->DrawIndexedInstanced(indicesCount, instanceCount, 0, 0, 0);
}
