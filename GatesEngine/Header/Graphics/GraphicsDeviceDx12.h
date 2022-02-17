#pragma once
#include "..\Util\Math\Vector2.h"
#include "Color.h"

#include "RenderTarget.h"
#include "DepthStencil.h"
#include "ShaderResourceHeap.h"
#include "CBufferAllocater.h"

#include "IRootSignature.h"
#include "IGraphicsPipeline.h"
#include "IMesh.h"
#include "ITexture.h"
#include "ILayer.h"

#include "..\Util\Manager.h"

#include "RenderQueue.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

namespace GE
{
	class GraphicsDeviceDx12
	{
	private:
		D3D12_VIEWPORT viewPort;
		D3D12_RECT rect;
		IDXGIFactory6* dxgiFactory;
		std::vector<IDXGIAdapter*> enumAdapter;
		IDXGIAdapter* useAdapter;
		ID3D12Device* device;
		ID3D12CommandAllocator* cmdAlloc;
		ID3D12GraphicsCommandList* cmdList;
		ID3D12CommandQueue* cmdQueue;
		IDXGISwapChain4* swapChain;
		RenderTarget renderTarget;
		DepthStencil depthStencil;
		ID3D12Fence* fence;
		UINT64 fenceValue;

		ShaderResourceHeap shaderResourceHeap;
		CBufferAllocater cbufferAllocater;
		Manager<IRootSignature> rootSignatureManager;
		Manager<IGraphicsPipeline> graphicsPipelineManager;
		Manager<IMesh> meshManager;
		Manager<ITexture> textureManager;
		Manager<ILayer> layerManager;

		RenderQueue renderQueue;
	private:
		void CreateDxgiFactory();
		void CreateDevice();
		void CreateCmdList();
		void CreateSwapChain(HWND hwnd);
		void CreateRTV();
		void CreateDSV();
		void CreateFence();
	public:
		GraphicsDeviceDx12();
		~GraphicsDeviceDx12();
		bool Create(const Math::Vector2& viewportSize, HWND hwnd);

		void ClearDefaultRenderTarget(const Color& color = {0,0,0,1});
		void ClearRenderTarget(IRenderTarget* renderTarget);
		void ClearDepthStencil(IDepthStencil* depthStencil);
		void ClearLayer(const std::string& name);
		void SetDefaultRenderTarget();
		void SetDefaultRenderTargetWithoutDSV();
		void SetRenderTarget(IRenderTarget* renderTarget,IDepthStencil* depthStencil);
		void SetRenderTargetWithoutDSV(IRenderTarget* renderTarget);
		void SetLayer(const std::string& name);
		void SetShaderResourceDescriptorHeap();
		void ResetCBufferAllocater();
		bool ScreenFlip();
		void SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after);
		void SetViewport(const Math::Vector2& size, const Math::Vector2& pos = {});

		ID3D12Device* GetDevice();
		ID3D12GraphicsCommandList* GetCmdList();
		ShaderResourceHeap* GetShaderResourceHeap();
		CBufferAllocater* GetCBufferAllocater();
		Manager<IRootSignature>* GetRootSignatureManager();
		Manager<IGraphicsPipeline>* GetGraphicsPipelineManager();
		Manager<IMesh>* GetMeshManager();
		Manager<ITexture>* GetTextureManager();
		Manager<ILayer>* GetLayerManager();
		RenderQueue* GetRenderQueue();
		void ExecuteRenderQueue();

		void SetShader(const std::string& shaderName,bool isWireframe = false);
		void SetTexture(const std::string& texName, int descIndex);
		void SetRenderTexture(const std::string& texName, int descIndex);
		void SetDepthTexture(const std::string& layerName, int descIndex);
		void DrawMesh(const std::string& meshName,int instanceCount = 1);
	};
}
