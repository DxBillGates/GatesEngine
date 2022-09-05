#include "..\..\Header\Graphics\GraphicsDeviceDx12.h"
#include "..\..\Header\Graphics\COMRelease.h"
#include "..\..\Header\Graphics\GraphicsPipelineInfo.h"

#include <string>
#include <assert.h>
#include <wrl.h>

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
	swapChainDesc.Width =  (UINT)viewPort.Width ;
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
	, shaderResourceHeap(ShaderResourceHeap())
	, cbufferAllocater(CBufferAllocater())
	, rootSignatureManager(Manager<IRootSignature>())
	, graphicsPipelineManager(Manager<IGraphicsPipeline>())
	, meshManager(Manager<IMesh>())
	, textureManager(Manager<ITexture>())
	, renderQueue(RenderQueue())
	, mainCamera(nullptr)
{
}

GE::GraphicsDeviceDx12::~GraphicsDeviceDx12()
{
	// 実行中のコマンドが終了してから解放!!
	cmdQueue->Signal(fence, ++fenceValue);
	if (fence->GetCompletedValue() != fenceValue)
	{
		HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (!event)
		{
			printf("ID3D12Fence:イベントエラー、正しくメモリ解放ができませんでした、アプリケーションを終了します。\n");
			return;
		}
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

void GE::GraphicsDeviceDx12::SetMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void GE::GraphicsDeviceDx12::ClearDefaultRenderTarget(const Color& color)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.GetHandle();

	float rgba[] = { color.r,color.g,color.b,color.a };
	cmdList->ClearRenderTargetView(rtvHandle, rgba, 0, nullptr);

	ClearDepthStencil(&depthStencil);
}

void GE::GraphicsDeviceDx12::ClearRenderTarget(IRenderTarget* renderTarget)
{
	if (!renderTarget)assert(true);
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetHandle();
	const Color& color = renderTarget->GetColor();

	// レンダーテクスチャの場合はSRVからRTVにリソースステートを変更する
	renderTarget->Prepare(cmdList);
	float rgba[] = { color.r,color.g,color.b,color.a };
	cmdList->ClearRenderTargetView(rtvHandle, rgba, 0, nullptr);
}

void GE::GraphicsDeviceDx12::ClearDepthStencil(IDepthStencil* depthStencil)
{
	if (!depthStencil)assert(true);
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil->GetHandle();
	cmdList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void GE::GraphicsDeviceDx12::ClearLayer(const std::string& name)
{
	IRenderTarget* layerRenderTarget = layerManager.Get(name)->GetRenderTexture();
	IDepthStencil* layerDepthStencil = layerManager.Get(name)->GetDepthTexture();

	if (layerRenderTarget)ClearRenderTarget(layerRenderTarget);
	if (layerDepthStencil)ClearDepthStencil(layerDepthStencil);
}

void GE::GraphicsDeviceDx12::SetDefaultRenderTarget()
{
	renderQueue.SetLayer(&renderTarget,&depthStencil );
}

void GE::GraphicsDeviceDx12::SetDefaultRenderTargetWithoutDSV()
{
	renderQueue.SetLayer(&renderTarget,nullptr);
}

void GE::GraphicsDeviceDx12::SetRenderTarget(IRenderTarget* renderTarget, IDepthStencil* depthStencil)
{
	renderQueue.SetLayer(renderTarget, depthStencil);
}

void GE::GraphicsDeviceDx12::SetRenderTargetWithoutDSV(IRenderTarget* renderTarget)
{
	renderQueue.SetLayer(renderTarget,nullptr);
}

void GE::GraphicsDeviceDx12::SetLayer(const std::string& name)
{
	IRenderTarget* layerRenderTarget = layerManager.Get(name)->GetRenderTexture();
	IDepthStencil* layerDepthStencil = layerManager.Get(name)->GetDepthTexture();

	if (!layerRenderTarget)return;

	renderQueue.SetLayer(layerRenderTarget,layerDepthStencil);

	if (!layerDepthStencil)
	{
		SetRenderTargetWithoutDSV(layerRenderTarget);
		return;
	}

	SetRenderTarget(layerRenderTarget, layerDepthStencil);
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
	swapChain->Present(0, 0);

	UINT64 backBufferIndex = swapChain->GetCurrentBackBufferIndex();
	renderTarget.SetIndex((int)backBufferIndex);

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

ID3D12Device* GE::GraphicsDeviceDx12::GetDevice()
{
	return device;
}

ID3D12GraphicsCommandList* GE::GraphicsDeviceDx12::GetCmdList()
{
	return cmdList;
}

GE::IShaderResourceHeap* GE::GraphicsDeviceDx12::GetShaderResourceHeap()
{
	return &shaderResourceHeap;
}

GE::ICBufferAllocater* GE::GraphicsDeviceDx12::GetCBufferAllocater()
{
	return &cbufferAllocater;
}

GE::Manager<GE::IRootSignature>* GE::GraphicsDeviceDx12::GetRootSignatureManager()
{
	return &rootSignatureManager;
}

GE::Manager<GE::IGraphicsPipeline>* GE::GraphicsDeviceDx12::GetGraphicsPipelineManager()
{
	return &graphicsPipelineManager;
}

GE::Manager<GE::IMesh>* GE::GraphicsDeviceDx12::GetMeshManager()
{
	return &meshManager;
}

GE::Manager<GE::ITexture>* GE::GraphicsDeviceDx12::GetTextureManager()
{
	return &textureManager;
}

GE::Manager<GE::ILayer>* GE::GraphicsDeviceDx12::GetLayerManager()
{
	return &layerManager;
}

GE::RenderQueue* GE::GraphicsDeviceDx12::GetRenderQueue()
{
	return &renderQueue;
}

GE::Camera* GE::GraphicsDeviceDx12::GetMainCamera()
{
	return mainCamera;
}

GE::Math::Vector2 GE::GraphicsDeviceDx12::GetViewportSize()
{
	return Math::Vector2(viewPort.Width,viewPort.Height);
}

void GE::GraphicsDeviceDx12::ExecuteRenderQueue()
{
	renderQueue.Execute(cmdList,&shaderResourceHeap);
}

void GE::GraphicsDeviceDx12::ExecuteCommands()
{
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
			return;
		}
		fence->SetEventOnCompletion(fenceValue, event);
		WaitForSingleObject(event, INFINITE);
		//CloseHandle(event);
	}
	cmdAlloc->Reset();
	cmdList->Reset(cmdAlloc, nullptr);
}

void GE::GraphicsDeviceDx12::SetShader(const std::string& shaderName, bool isWireframe)
{
	IGraphicsPipeline* usePipeline = graphicsPipelineManager.Get(shaderName);
	renderQueue.SetPipeline(usePipeline,isWireframe);
}

void GE::GraphicsDeviceDx12::SetTexture(const std::string& texName, int descIndex)
{
	renderQueue.AddSetShaderResource({ descIndex,textureManager.Get(texName)->GetSRVNumber() });
}

void GE::GraphicsDeviceDx12::SetRenderTexture(const std::string& texName, int descIndex)
{
	IRenderTexture* renderTexture = layerManager.Get(texName)->GetRenderTexture();
	renderQueue.AddSetShaderResource({ descIndex,renderTexture->GetSRVNumber() });
}

void GE::GraphicsDeviceDx12::SetDepthTexture(const std::string& layerName, int descIndex)
{
	IDepthTexture* depthTexture = layerManager.Get(layerName)->GetDepthTexture();
	renderQueue.AddSetShaderResource({ descIndex,depthTexture->GetSRVNumber() });
}

void GE::GraphicsDeviceDx12::DrawMesh(const std::string& meshName, int instanceCount)
{
	renderQueue.SetMesh(meshManager.Get(meshName));
	renderQueue.AddCommand();
}

void GE::GraphicsDeviceDx12::OnResizeWindow(const Math::Vector2& size)
{
	// 全ての発行済みコマンドの終了を待つ.
	Microsoft::WRL::ComPtr<ID3D12Fence1> mFence;
	const UINT64 expectValue = 1;
	HRESULT hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));

	cmdQueue->Signal(mFence.Get(), expectValue);
	if (mFence->GetCompletedValue() != expectValue)
	{
		HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		mFence->SetEventOnCompletion(expectValue, event);
		WaitForSingleObject(event, INFINITE);
	}

	// 既存のSwapchainからFormatなどを取得
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChain->GetDesc1(&swapChainDesc);

	// コマンドが終了しているためフレームバッファとデプスを一度削除
	depthStencil.Cleanup();
	renderTarget.Cleanup();

	HRESULT result;
	result = swapChain->ResizeBuffers(swapChainDesc.BufferCount,(UINT)size.x, (UINT)size.y, swapChainDesc.Format, swapChainDesc.Flags);

	std::vector<ID3D12Resource*>& frameBuffers = renderTarget.GetFrameBuffers();
	frameBuffers.resize(2);

	// swapChainからフレームバッファを取得
	for (int i = 0; i < (int)frameBuffers.size(); ++i)
	{
		result = swapChain->GetBuffer(i, IID_PPV_ARGS(&frameBuffers[i]));
	}

	// コマンドが終了しているためフレームバッファとデプスを再度作成
	depthStencil.Create(size, device);
	renderTarget.Create(device);
	renderTarget.SetIndex(swapChain->GetCurrentBackBufferIndex());
}
