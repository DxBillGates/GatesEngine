#pragma once
#include "Color.h"
#include "IRenderTarget.h"
#include "IDepthStencil.h"
#include "IShaderResourceHeap.h"
#include "ICBufferAllocater.h"
#include "IRootSignature.h"
#include "IGraphicsPipeline.h"
#include "IMesh.h"
#include "ITexture.h"
#include "ILayer.h"
#include "RenderQueue.h"
#include "Camera.h"

#include "..\Util\Manager.h"

#include <string>
#include <d3d12.h>

namespace GE
{
	class IGraphicsDeviceDx12
	{
	public:
		virtual ~IGraphicsDeviceDx12() {}

		virtual void ClearDefaultRenderTarget(const Color& color = { 0,0,0,1 }) = 0;
		virtual void ClearRenderTarget(IRenderTarget* renderTarget) = 0;
		virtual void ClearDepthStencil(IDepthStencil* depthStencil) = 0;
		virtual void ClearLayer(const std::string& name) = 0;
		virtual void SetDefaultRenderTarget() = 0;
		virtual void SetDefaultRenderTargetWithoutDSV() = 0;
		virtual void SetRenderTarget(IRenderTarget* renderTarget, IDepthStencil* depthStencil) = 0;
		virtual void SetRenderTargetWithoutDSV(IRenderTarget* renderTarget) = 0;
		virtual void SetLayer(const std::string& name) = 0;
		virtual void SetShaderResourceDescriptorHeap() = 0;
		virtual void ResetCBufferAllocater() = 0;
		virtual bool ScreenFlip() = 0;
		virtual void SetResourceBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after) = 0;
		virtual void SetViewport(const Math::Vector2& size, const Math::Vector2& pos = {}) = 0;

		virtual ID3D12Device* GetDevice() = 0;
		virtual ID3D12GraphicsCommandList* GetCmdList() = 0;
		virtual IShaderResourceHeap* GetShaderResourceHeap() = 0;
		virtual ICBufferAllocater* GetCBufferAllocater() = 0;
		virtual Manager<IRootSignature>* GetRootSignatureManager() = 0;
		virtual Manager<IGraphicsPipeline>* GetGraphicsPipelineManager() = 0;
		virtual Manager<IMesh>* GetMeshManager() = 0;
		virtual Manager<ITexture>* GetTextureManager() = 0;
		virtual Manager<ILayer>* GetLayerManager() = 0;
		virtual RenderQueue* GetRenderQueue() = 0;
		virtual Camera* GetMainCamera() = 0;
		virtual Math::Vector2 GetViewportSize() = 0;

		virtual void ExecuteRenderQueue() = 0;
		virtual void ExecuteCommands() = 0;
		virtual void SetShader(const std::string& shaderName, bool isWireframe = false) = 0;
		virtual void SetTexture(const std::string& texName, int descIndex) = 0;
		virtual void SetRenderTexture(const std::string& texName, int descIndex) = 0;
		virtual void SetDepthTexture(const std::string& layerName, int descIndex) = 0;
		virtual void DrawMesh(const std::string& meshName, int instanceCount = 1) = 0;

		virtual void OnResizeWindow(const Math::Vector2& size) {};
	};
}
