#include "..\..\Header\Graphics\RenderTexture.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::RenderTexture::RenderTexture()
	: device(nullptr)
	, rtvHeap(nullptr)
	, color(Math::Vector4())
	, currentResourceState(D3D12_RESOURCE_STATES())
	, buffer(nullptr)
	, size(Math::Vector2())
	, srvNum(0)
{
}

GE::RenderTexture::~RenderTexture()
{
	COM_RELEASE(buffer);
	COM_RELEASE(rtvHeap);
}

void GE::RenderTexture::Create(ID3D12Device* device, IShaderResourceHeap* shaderResourceHeap, const Math::Vector2& setSize, const Math::Vector4& setColor)
{
	this->device = device;
	size = setSize;

	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resDesc.Alignment = 65536;
	resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.Width = (UINT)setSize.x;
	resDesc.Height = (UINT)setSize.y;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	D3D12_CLEAR_VALUE clearValue = {};
	clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	clearValue.Color[0] = (color.x > 1) ? color.x / 255.0f : color.x;
	clearValue.Color[1] = (color.y > 1) ? color.y / 255.0f : color.y;
	clearValue.Color[2] = (color.z > 1) ? color.z / 255.0f : color.z;
	clearValue.Color[3] = (color.w > 1) ? color.w / 255.0f : color.w;

	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clearValue, IID_PPV_ARGS(&buffer));

	//ヒープの生成
	HRESULT result;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = 1;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	//ビューの生成
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	device->CreateRenderTargetView(buffer, &rtvDesc, rtvHeapHandle);

	srvNum= shaderResourceHeap->GetNextSRVNumber();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = buffer->GetDesc().Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	shaderResourceHeap->CreateSRV(buffer,srvDesc);
}

D3D12_CPU_DESCRIPTOR_HANDLE GE::RenderTexture::GetHandle()
{
	return rtvHeap->GetCPUDescriptorHandleForHeapStart();
}

int GE::RenderTexture::GetSRVNumber()
{
	return srvNum;
}

void GE::RenderTexture::EndDraw(ID3D12GraphicsCommandList* cmdList)
{
	if (currentResourceState != D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	{
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Transition.pResource = buffer;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		barrier.Transition.StateBefore = currentResourceState;
		cmdList->ResourceBarrier(1, &barrier);

		currentResourceState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	}
}

const GE::Math::Vector2& GE::RenderTexture::GetSize()
{
	return size;
}

D3D12_RESOURCE_STATES GE::RenderTexture::GetCurrentResourceState()
{
	return currentResourceState;
}

const GE::Math::Vector4& GE::RenderTexture::GetColor()
{
	return color;
}

void GE::RenderTexture::SetCurrentResourceState(D3D12_RESOURCE_STATES state)
{
	currentResourceState = state;
}

void GE::RenderTexture::SetColor(const Math::Vector4& color)
{
	this->color = color;
}

void GE::RenderTexture::Prepare(ID3D12GraphicsCommandList* cmdList)
{
	if (currentResourceState != D3D12_RESOURCE_STATE_RENDER_TARGET)
	{
		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Transition.pResource = buffer;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateBefore = currentResourceState;
		cmdList->ResourceBarrier(1, &barrier);

		currentResourceState = D3D12_RESOURCE_STATE_RENDER_TARGET;
	}
}
