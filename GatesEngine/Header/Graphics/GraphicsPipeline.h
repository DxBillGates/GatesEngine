#pragma once
#include "IGraphicsPipeline.h"
#include "IShader.h"
#include "IRootSignature.h"

#include <vector>

namespace GE
{
	enum class GraphicsPipelineBlendMode
	{
		BLENDMODE_ADD,
		BLENDMODE_SUB,
		BLENDMODE_INV,
		BLENDMODE_ALPHA
	};

	enum class GraphicsPipelinePrimitiveTopolotyType
	{
		UNDIFINED,
		POINT,
		LINE,
		TRIANGLE,
		PATCH,
	};

	enum class GraphicsPipelineComparison
	{
		COMPARISON_FUNC_NEVER = 1,
		COMPARISON_FUNC_LESS,
		COMPARISON_FUNC_EQUAL,
		COMPARISON_FUNC_LESS_EQUAL,
		COMPARISON_FUNC_GREATER,
		COMPARISON_FUNC_NOT_EQUAL,
		COMPARISON_FUNC_GREATER_EQUAL,
		COMPARISON_FUNC_ALWAYS,
	};

	struct GraphicsPipelineInfo
	{
		GraphicsPipelineBlendMode blendMode = GraphicsPipelineBlendMode::BLENDMODE_ALPHA;
		GraphicsPipelinePrimitiveTopolotyType topologyType = GraphicsPipelinePrimitiveTopolotyType::TRIANGLE;
		bool isUseDepthStencil = true;
		int renderTargetCount = 1;
		bool isUseAlphaToCoverage = false;
		GraphicsPipelineComparison depthComparison = GraphicsPipelineComparison::COMPARISON_FUNC_LESS;
	};

	enum class GraphicsPipelineInputLayout
	{
		POSITION,
		UV,
		NORMAL,
		COLOR,
	};

	struct ShaderStages
	{
		IShader* vShader;
		IShader* gShader;
		IShader* dShader;
		IShader* hShader;
		IShader* pShader;
	};

	class GraphicsPipeline : public IGraphicsPipeline
	{
	private:
		ID3D12PipelineState* wireframePipeline;
		ID3D12PipelineState* solidPipeline;
		IRootSignature* rootSignature;
		ShaderStages shaderStages;
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
	};
}