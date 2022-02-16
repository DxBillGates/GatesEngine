#include "..\..\Header\Graphics\DepthTexture.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::DepthTexture::DepthTexture()
	: dsvHeap(nullptr)
	, buffer(nullptr)
	, size(Math::Vector2())
	, srvNum(0)
{
}

GE::DepthTexture::~DepthTexture()
{
	COM_RELEASE(buffer);
	COM_RELEASE(dsvHeap);
}

void GE::DepthTexture::Create(ID3D12Device* device, IShaderResourceHeap* shaderResourceHeap, const Math::Vector2& setSize)
{
	size = setSize;
	//�f�v�X�o�b�t�@�̐ݒ�
	HRESULT result;
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Width = (UINT64)size.x;
	resDesc.Height = (UINT64)size.y;
	resDesc.DepthOrArraySize = 1;
	resDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	//�f�v�X�o�b�t�@�̃t�H�[�}�b�g�ƍő�[�x�l��ݒ�
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
	//�ݒ�����ƂɃf�v�X�o�b�t�@�𐶐�
	result = device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(&buffer));
	//DSV���i�[���邽�߂̃q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	//DSV�q�[�v�̐���
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	//DSV�̐���
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(buffer, &dsvDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());

	srvNum = shaderResourceHeap->GetNextSRVNumber();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	shaderResourceHeap->CreateSRV(buffer, srvDesc);
}

D3D12_CPU_DESCRIPTOR_HANDLE GE::DepthTexture::GetHandle()
{
	return dsvHeap->GetCPUDescriptorHandleForHeapStart();
}

int GE::DepthTexture::GetSRVNumber()
{
	return srvNum;
}
