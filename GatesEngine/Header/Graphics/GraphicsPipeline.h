#pragma once
#include "IGraphicsPipeline.h"
#include "IShader.h"
#include "IRootSignature.h"
#include "GraphicsPipelineInfo.h"

#include <vector>

namespace GE
{
	class GraphicsPipeline : public IGraphicsPipeline
	{
	private:
		ID3D12PipelineState* wireframePipeline;
		ID3D12PipelineState* solidPipeline;
		IRootSignature* rootSignature;
		ShaderStages shaderStages;
		GraphicsPipelineInfo graphicsPipelineInfo;
	private:
		void SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, GraphicsPipelineBlendMode mode);
	public:
		GraphicsPipeline(const ShaderStages& shaderStages);
		~GraphicsPipeline();
		void Create(ID3D12Device* device,const std::vector<GraphicsPipelineInputLayout>& inputLayouts, IRootSignature* rootSignature, const GraphicsPipelineInfo& info);

		// interface

		ID3D12PipelineState* GetWireframePipeline() override;
		ID3D12PipelineState* GetSolidPipeline() override;
		ID3D12RootSignature* GetRootSignature() override;
		int GetTopologyType() override;
	};
}