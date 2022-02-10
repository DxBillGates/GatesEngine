#include "..\..\Header\Graphics\GraphicsDeviceDx12.h"
#include "..\..\Header\Graphics\COMRelease.h"
#include <string>
#include <assert.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

void GE::GraphicsDeviceDx12::CreateDxgiFactory()
{
	// DXGIFactoryの生成
	HRESULT result;
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
}

void GE::GraphicsDeviceDx12::CreateDevice()
{
	// 使用できるGPUを探してそのアダプタでID3DDeviceを生成
	HRESULT result;
	for (int i = 0; dxgiFactory->EnumAdapters(i, &useAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		enumAdapter.push_back(useAdapter);
	}
	DXGI_ADAPTER_DESC adapterDesc = {};
	for (int i = 0; i < (int)enumAdapter.size(); ++i)
	{
		enumAdapter[i]->GetDesc(&adapterDesc);
		std::wstring adapterName = adapterDesc.Description;
		if (adapterName.find(L"Microsoft") == std::wstring::npos && adapterName.find(L"Intel") == std::wstring::npos)
		{
			useAdapter = enumAdapter[i];
			break;
		}
	}
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
	for (int i = 0; i < _countof(featureLevel); ++i)
	{
		if (SUCCEEDED(result = D3D12CreateDevice(useAdapter, featureLevel[i], IID_PPV_ARGS(&device))))break;
	}
}

void GE::GraphicsDeviceDx12::CreateCmdList()
{
	// コマンド関係を生成
	HRESULT result;
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
	result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc, nullptr, IID_PPV_ARGS(&cmdList));
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	result = device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
}

void GE::GraphicsDeviceDx12::CreateSwapChain(HWND hwnd)
{
	//ApplicationからgameWindowのハンドルを取得しそのハンドルとそのほかの設定からSwapChainを生成
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = (UINT)viewPort.Width;
	swapChainDesc.Height = (UINT)viewPort.Height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	result = dxgiFactory->CreateSwapChainForHwnd(cmdQueue, hwnd, &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&swapChain);
}

void GE::GraphicsDeviceDx12::CreateRTV()
{
	HRESULT result;
	std::vector<ID3D12Resource*>& frameBuffers = renderTarget.GetFrameBuffers();
	frameBuffers.resize(2);

	// swapChainからフレームバッファを取得
	for (int i = 0; i < (int)frameBuffers.size(); ++i)
	{
		result = swapChain->GetBuffer(i, IID_PPV_ARGS(&frameBuffers[i]));
	}

	renderTarget.Create(device);
}

void GE::GraphicsDeviceDx12::CreateDSV()
{
	Math::Vector2 size = { viewPort.Width,viewPort.Height };
	depthStencil.Create(size, device);
}

void GE::GraphicsDeviceDx12::CreateFence()
{
	// CPUとGPUの同期をさせる役割を持つフェンスを生成
	HRESULT result;
	result = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

GE::GraphicsDeviceDx12::GraphicsDeviceDx12()
	: viewPort(D3D12_VIEWPORT())
	, rect(D3D12_RECT())
	, dxgiFactory(nullptr)
	, useAdapter(nullptr)
	, device(nullptr)
	, cmdAlloc(nullptr)
	, cmdList(nullptr)
	, cmdQueue(nullptr)
	, swapChain(nullptr)
	, renderTarget(RenderTarget())
	, depthStencil(DepthStencil())
	, fence(nullptr)
	, fenceValue(0)
{
}

GE::GraphicsDeviceDx12::~GraphicsDeviceDx12()
{
	// 実行中のコマンドが終了してから解放!!
	cmdQueue->Signal(fence, ++fenceValue);
	if (fence->GetCompletedValue() != fenceValue)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceValue, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	COM_RELEASE(dxgiFactory);
	COM_RELEASE(device);
	COM_RELEASE(cmdAlloc);
	COM_RELEASE(cmdList);
	COM_RELEASE(cmdQueue);
	COM_RELEASE(swapChain);
	COM_RELEASE(fence);
}

bool GE::GraphicsDeviceDx12::Create(const Math::Vector2& viewportSize, HWND hwnd)
{
	SetViewport(viewportSize, Math::Vector2());
	CreateDxgiFactory();
	CreateDevice();
	CreateCmdList();
	CreateSwapChain(hwnd);
	CreateRTV();
	CreateDSV();
	CreateFence();

	shaderResourceHeap.SetGraphicsDevice(device, cmdList);
	shaderResourceHeap.Create(Math::Vector3(2560, 256, 256));

	cbufferAllocater.SetGraphicsDevice(device, cmdList, &shaderResourceHeap);
	cbufferAllocater.Create();

	return true;
}

void GE::GraphicsDeviceDx12::ClearDefaultRenderTarget(const Math::Vector4& color)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.GetHandle();
	rtvHandle.ptr += (UINT64)swapChain->GetCurrentBackBufferIndex() * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	float rgba[] = { color.x,color.y,color.z,color.w };
	cmdList->ClearRenderTargetView(rtvHandle, rgba, 0, nullptr);
}

void GE::GraphicsDeviceDx12::ClearRenderTarget(IRenderTarget* renderTarget)
{
	if (!renderTarget)assert(true);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetHandle();
	const Math::Vector4& color = renderTarget->GetColor();

	renderTarget->Prepare();
	float rgba[] = { color.x,color.y,color.z,color.w };
	cmdList->ClearRenderTargetView(rtvHandle, rgba, 0, nullptr);
}

void GE::GraphicsDeviceDx12::ClearDepthStencil(IDepthStencil* depthStencil)
{
	if (!depthStencil)assert(true);
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil->GetHandle();
	cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void GE::GraphicsDeviceDx12::SetDefaultRenderTarget()
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.GetHandle();
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil.GetHandle();

	rtvHandle.ptr += (UINT64)swapChain->GetCurrentBackBufferIndex() * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_VIEWPORT viewport = viewPort;
	D3D12_RECT _rect = rect;

	viewport.Height = renderTarget.GetSize().y;
	viewport.Width = renderTarget.GetSize().x;

	_rect.bottom = (LONG)renderTarget.GetSize().y;
	_rect.right =  (LONG)renderTarget.GetSize().x;

	cmdList->RSSetViewports(1, &viewport);
	cmdList->RSSetScissorRects(1, &_rect);
	cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
}

void GE::GraphicsDeviceDx12::SetDefaultRenderTargetWithoutDSV()
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.GetHandle();
	rtvHandle.ptr += (UINT64)swapChain->GetCurrentBackBufferIndex() * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_VIEWPORT viewport = viewPort;
	D3D12_RECT _rect = rect;

	viewport.Height = renderTarget.GetSize().y;
	viewport.Width = renderTarget.GetSize().x;

	_rect.bottom = (LONG)renderTarget.GetSize().y;
	_rect.right = (LONG)renderTarget.GetSize().x;

	cmdList->RSSetViewports(1, &viewport);
	cmdList->RSSetScissorRects(1, &_rect);
	cmdList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
}

void GE::GraphicsDeviceDx12::SetRenderTarget(IRenderTarget* renderTarget,IDepthStencil* depthStencil)
{
	if (!renderTarget || !depthStencil)assert(true);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetHandle();
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil->GetHandle();

	D3D12_VIEWPORT viewport = viewPort;
	D3D12_RECT _rect = rect;

	viewport.Height = renderTarget->GetSize().y;
	viewport.Width = renderTarget->GetSize().x;

	_rect.bottom = (LONG)renderTarget->GetSize().y;
	_rect.right = (LONG)renderTarget->GetSize().x;

	renderTarget->Prepare();
	cmdList->RSSetViewports(1, &viewport);
	cmdList->RSSetScissorRects(1, &_rect);
	cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
}

void GE::GraphicsDeviceDx12::SetRenderTargetWithoutDSV(IRenderTarget* renderTarget)
{
	if (!renderTarget)assert(true);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetHandle();

	D3D12_VIEWPORT viewport = viewPort;
	D3D12_RECT _rect = rect;

	viewport.Height = renderTarget->GetSize().y;
	viewport.Width = renderTarget->GetSize().x;

	_rect.bottom = (LONG)renderTarget->GetSize().y;
	_rect.right = (LONG)renderTarget->GetSize().x;

	renderTarget->Prepare();
	cmdList->RSSetViewports(1, &viewport);
	cmdList->RSSetScissorRects(1, &_rect);
	cmdList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
}

void GE::GraphicsDeviceDx12::SetShaderResourceDescriptorHeap()
{
	shaderResourceHeap.Set();
}

void GE::GraphicsDeviceDx12::ResetCBufferAllocater()
{
	cbufferAllocater.ResetCurrentUsedNumber();
}

bool GE::GraphicsDeviceDx12::ScreenFlip()
{
	if (renderTarget.GetCurrentResourceState() != D3D12_RESOURCE_STATE_PRESENT)
	{
		renderTarget.SetCurrentResourceState(D3D12_RESOURCE_STATE_PRESENT);
		std::vector<ID3D12Resource*>& frameBuffers = renderTarget.GetFrameBuffers();
		SetResourceBarrier(frameBuffers[swapChain->GetCurrentBackBufferIndex()], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	}
	cmdList->Close();
	ID3D12CommandList* cmdLists[] = { cmdList };
	cmdQueue->ExecuteCommandLists(1, cmdLists);
	cmdQueue->Signal(fence, ++fenceValue);
	if (fence->GetCompletedValue() != fenceValue)
	{
		HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (!event)
		{
			printf("ID3D12Fence:イベントエラー、アプリケーションを終了します。");
			return false;
		}
		fence->SetEventOnCompletion(fenceValue, event);
		WaitForSingleObject(event, INFINITE);
		//CloseHandle(event);
	}
	cmdAlloc->Reset();
	cmdList->Reset(cmdAlloc, nullptr);
	swapChain->Present(0, 0);
	return true;
}

void GE::GraphicsDeviceDx12::SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Transition.pResource = resource;
	barrier.Transition.StateAfter = after;
	barrier.Transition.StateBefore = before;
	cmdList->ResourceBarrier(1, &barrier);
}

void GE::GraphicsDeviceDx12::SetViewport(const Math::Vector2& size, const Math::Vector2& pos)
{
	viewPort = { 0,0,(float)size.x,(float)size.y,0,1.0f };
	rect = { 0,0,(int)size.x,(int)size.y };
}
