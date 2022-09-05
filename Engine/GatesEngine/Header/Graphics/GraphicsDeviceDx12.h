#pragma once
#include "..\Util\Math\Vector2.h"
#include "Color.h"

#include "RenderTarget.h"
#include "DepthStencil.h"
#include "ShaderResourceHeap.h"
#include "CBufferAllocater.h"

#include "IGraphicsDeviceDx12.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

namespace GE
{
	class GraphicsDeviceDx12 : public IGraphicsDeviceDx12
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
		Camera* mainCamera;
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
		void SetMainCamera(Camera* camera);

		// interface

		void ClearDefaultRenderTarget(const Color& color = {0,0,0,1}) override;
		void ClearRenderTarget(IRenderTarget* renderTarget) override;
		void ClearDepthStencil(IDepthStencil* depthStencil) override;
		void ClearLayer(const std::string& name) override;
		void SetDefaultRenderTarget() override;
		void SetDefaultRenderTargetWithoutDSV() override;
		void SetRenderTarget(IRenderTarget* renderTarget,IDepthStencil* depthStencil) override;
		void SetRenderTargetWithoutDSV(IRenderTarget* renderTarget) override;
		void SetLayer(const std::string& name) override;
		void SetShaderResourceDescriptorHeap() override;
		void ResetCBufferAllocater() override;
		bool ScreenFlip() override;
		void SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after) override;
		void SetViewport(const Math::Vector2& size, const Math::Vector2& pos = {}) override;

		ID3D12Device* GetDevice() override;
		ID3D12GraphicsCommandList* GetCmdList() override;
		IShaderResourceHeap* GetShaderResourceHeap() override;
		ICBufferAllocater* GetCBufferAllocater();
		Manager<IRootSignature>* GetRootSignatureManager() override;
		Manager<IGraphicsPipeline>* GetGraphicsPipelineManager() override;
		Manager<IMesh>* GetMeshManager() override;
		Manager<ITexture>* GetTextureManager() override;
		Manager<ILayer>* GetLayerManager() override;
		RenderQueue* GetRenderQueue() override;
		Camera* GetMainCamera() override;
		Math::Vector2 GetViewportSize() override;

		void ExecuteRenderQueue() override;
		void ExecuteCommands() override;
		void SetShader(const std::string& shaderName,bool isWireframe = false) override;
		void SetTexture(const std::string& texName, int descIndex) override;
		void SetRenderTexture(const std::string& texName, int descIndex) override;
		void SetDepthTexture(const std::string& layerName, int descIndex) override;
		void DrawMesh(const std::string& meshName,int instanceCount = 1) override;

		void OnResizeWindow(const Math::Vector2& size) override;
	};
}
