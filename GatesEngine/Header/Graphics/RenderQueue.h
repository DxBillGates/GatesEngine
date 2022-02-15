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
		int descIndex;
		int viewNumber;
	};

	struct RenderingCommand
	{
		IRenderTarget* renderTarget;
		IDepthStencil* depthStencil;
		IGraphicsPipeline* pipeline;
		std::vector<ShaderResourceCommand> shaderResources;
		std::vector<ShaderResourceCommand> constantBufferViews;
		IMesh* drawMesh;
		float depth;
	};

	class RenderQueue
	{
	private:
		std::vector<RenderingCommand> renderingCommands;

		IRenderTarget* currentSetRenderTarget;
		IDepthStencil* currentSetDepthStencil;
		IGraphicsPipeline* currentSetPipeline;
		std::vector<ShaderResourceCommand> currentSetShaderResources;
		std::vector<ShaderResourceCommand> currentSetConstantBufferViews;
		IMesh* currentSetDrawMesh;
		float depth;
	public:
		void SetLayer(IRenderTarget* setRenderTarget,IDepthStencil* setDepthStencil);
		void SetPipeline(IGraphicsPipeline* setPipeline);
		void AddSetShaderResource(const ShaderResourceCommand& command);
		void AddSetConstantBufferInfo(const ShaderResourceCommand& command);
		void SetMesh(IMesh* drawMesh);
		void SetDepth(float value);

		void AddCommand();

		void ZSortCommand();
		void Execute(ID3D12GraphicsCommandList* cmdList, IShaderResourceHeap* shaderResourceHeap);
	};
}
