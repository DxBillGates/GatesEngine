#include "..\..\Header\Graphics\DepthStencil.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::DepthStencil::DepthStencil()
	: size(Math::Vector2())
	, depthBuffer(nullptr)
	, dsvHeap(nullptr)
{
}

GE::DepthStencil::~DepthStencil()
{
	COM_RELEASE(depthBuffer);
	COM_RELEASE(dsvHeap);
}

void GE::DepthStencil::Create(const Math::Vector2& size, ID3D12Device* device)
{
	this->size = size;

	HRESULT result = 0;

	// デプスバッファ作成
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

	// デプスバッファのフォーマットと最大深度値を設定
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	// 設定をもとにデプスバッファを生成
	device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(&depthBuffer));

	if (dsvHeap == nullptr)
	{
		// dsvを格納する
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
		dsvHeapDesc.NumDescriptors = 1;
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;

		// dsvヒープの生成
		result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	}

	// dsvの生成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(depthBuffer, &dsvDesc, dsvHeap->GetCPUDescriptorHandleForHeapStart());
}

void GE::DepthStencil::Cleanup()
{
	COM_RELEASE(depthBuffer);
}

D3D12_CPU_DESCRIPTOR_HANDLE GE::DepthStencil::GetHandle()
{
	return dsvHeap->GetCPUDescriptorHandleForHeapStart();
}
