#include "..\..\Header\Graphics\RenderTarget.h"
#include "..\..\Header\Graphics\COMRelease.h"
#include <assert.h>

GE::RenderTarget::RenderTarget()
	: rtvHeap(nullptr)
	, currentResourceState(D3D12_RESOURCE_STATES())
{
}

GE::RenderTarget::~RenderTarget()
{
	for (auto& buffer : rtvBuffer)
	{
		COM_RELEASE(buffer);
	}
	COM_RELEASE(rtvHeap);
}

void GE::RenderTarget::Create(ID3D12Device* device)
{
	if ((int)rtvBuffer.size() <= 0)assert(true);

	// ヒープの生成
	HRESULT result;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = (int)rtvBuffer.size();
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	// ビューの生成
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	int i = 0;
	for (auto& r : rtvBuffer)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHeapHandle.ptr += (UINT64)i * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		device->CreateRenderTargetView(r, &rtvDesc, rtvHeapHandle);
		++i;
	}

	// sizeにバッファのサイズを格納
	D3D12_RESOURCE_DESC resDesc = rtvBuffer[0]->GetDesc();
	size = { (float)resDesc.Width,(float)resDesc.Height };
}

std::vector<ID3D12Resource*>& GE::RenderTarget::GetFrameBuffers()
{
	return rtvBuffer;
}

D3D12_CPU_DESCRIPTOR_HANDLE GE::RenderTarget::GetHandle()
{
	return rtvHeap->GetCPUDescriptorHandleForHeapStart();
}

const GE::Math::Vector2& GE::RenderTarget::GetSize()
{
	return size;
}

D3D12_RESOURCE_STATES GE::RenderTarget::GetCurrentResourceState()
{
	return currentResourceState;
}

const GE::Math::Vector4& GE::RenderTarget::GetColor()
{
	return color;
}

void GE::RenderTarget::SetCurrentResourceState(D3D12_RESOURCE_STATES state)
{
	currentResourceState = state;
}

void GE::RenderTarget::SetColor(const Math::Vector4& color)
{
	this->color = color;
}

void GE::RenderTarget::Prepare(ID3D12GraphicsCommandList* cmdList)
{
}
