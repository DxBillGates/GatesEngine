#pragma once
#include "ICBufferAllocater.h"
#include "ILayer.h"
#include "IGraphicsPipeline.h"
#include "GraphicsPipelineInfo.h"
#include "ITexture.h"
#include "IMesh.h"
#include "IShaderResourceHeap.h"

#include <vector>

namespace GE
{
	struct ShaderResourceCommand
	{
		int descIndex = 0;
		int viewNumber = 0;
	};

	struct RenderingCommand
	{
		IRenderTarget* renderTarget = nullptr;
		IDepthStencil* depthStencil = nullptr;
		IGraphicsPipeline* pipeline = nullptr;
		bool isWireframe = false;
		std::vector<ShaderResourceCommand> shaderResources;
		std::vector<ShaderResourceCommand> constantBufferViews;
		IMesh* drawMesh = nullptr;
		float depth = 0;
	};

	class RenderQueue
	{
	private:
		std::vector<RenderingCommand> renderingCommands;

		IRenderTarget* currentSetRenderTarget;
		IDepthStencil* currentSetDepthStencil;
		IGraphicsPipeline* currentSetPipeline;
		bool currentSetPipelineIsWireframe;
		std::vector<ShaderResourceCommand> currentSetShaderResources;
		std::vector<ShaderResourceCommand> currentSetConstantBufferViews;
		IMesh* currentSetDrawMesh;
		float depth;
	public:
		RenderQueue();
		void SetLayer(IRenderTarget* setRenderTarget,IDepthStencil* setDepthStencil);
		void SetPipeline(IGraphicsPipeline* setPipeline,bool isWireframe = false);
		void AddSetShaderResource(const ShaderResourceCommand& command);
		void AddSetConstantBufferInfo(const ShaderResourceCommand& command);
		void SetMesh(IMesh* drawMesh);
		void SetDepth(float value);

		void AddCommand();

		void ZSortCommand();
		void Execute(ID3D12GraphicsCommandList* cmdList, IShaderResourceHeap* shaderResourceHeap);
	};
}
