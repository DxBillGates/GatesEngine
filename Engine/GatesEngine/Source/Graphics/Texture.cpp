#include "..\..\Header\Graphics\Texture.h"
#include "..\..\Header\Graphics\COMRelease.h"
#include "..\..\External\DirectXTex\DirectXTex.h"

GE::Texture::Texture()
	: buffer(nullptr)
	, size(Math::Vector2())
	, srvNum(0)
{
}

GE::Texture::~Texture()
{
	COM_RELEASE(buffer);
}

void GE::Texture::Load(const std::string& filename, ID3D12Device* device, IShaderResourceHeap* shaderResourceHeap)
{
	std::string filepath = "Resources/Texture/" + filename;
	wchar_t wFilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wFilepath, _countof(wFilepath));

	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
	const DirectX::Image* image;

	DirectX::LoadFromWICFile(wFilepath, DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);
	image = scratchImage.GetImage(0, 0, 0);
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
	resDesc.Format = metadata.format;
	resDesc.Width = (UINT64)metadata.width;
	resDesc.Height = (UINT)metadata.height;
	resDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	resDesc.MipLevels = (UINT16)metadata.mipLevels;
	resDesc.SampleDesc.Count = 1;

	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buffer));
	buffer->WriteToSubresource(0, nullptr, image->pixels, (UINT)image->rowPitch, (UINT)image->slicePitch);
	srvNum = shaderResourceHeap->GetNextSRVNumber();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = buffer->GetDesc().Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	shaderResourceHeap->CreateSRV(buffer,srvDesc);
}

int GE::Texture::GetSRVNumber()
{
	return srvNum;
}