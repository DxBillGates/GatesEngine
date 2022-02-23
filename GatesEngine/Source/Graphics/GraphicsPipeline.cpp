#include "..\..\Header\Graphics\GraphicsPipeline.h"
#include "..\..\Header\Graphics\COMRelease.h"

#include <string>

void GE::GraphicsPipeline::SetBlendMode(D3D12_RENDER_TARGET_BLEND_DESC& blendDesc, GraphicsPipelineBlendMode mode)
{
	blendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	blendDesc.BlendEnable = true;
	blendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
	switch (mode)
	{
	case GraphicsPipelineBlendMode::BLENDMODE_ADD:
		// 加算合成
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_ONE;
		blendDesc.DestBlend = D3D12_BLEND_ONE;
		break;
	case GraphicsPipelineBlendMode::BLENDMODE_SUB:
		// 減算合成
		blendDesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
		blendDesc.SrcBlend = D3D12_BLEND_ONE;
		blendDesc.DestBlend = D3D12_BLEND_ONE;
		break;
	case GraphicsPipelineBlendMode::BLENDMODE_INV:
		// 色反転
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;
		blendDesc.DestBlend = D3D12_BLEND_ZERO;
		break;
	case GraphicsPipelineBlendMode::BLENDMODE_ALPHA:
		// 半透明
		blendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		break;
	}
}

GE::GraphicsPipeline::GraphicsPipeline(const ShaderStages& shaderStages)
	: wireframePipeline(nullptr)
	, solidPipeline(nullptr)
	, rootSignature(nullptr)
	, shaderStages(shaderStages)
	, graphicsPipelineInfo(GraphicsPipelineInfo())
{
}

GE::GraphicsPipeline::~GraphicsPipeline()
{
	COM_RELEASE(wireframePipeline);
	COM_RELEASE(solidPipeline);
}

void GE::GraphicsPipeline::Create(ID3D12Device* device, const std::vector<GraphicsPipelineInputLayout>& inputLayouts, IRootSignature* rootSignature, const GraphicsPipelineInfo& info)
{
	int inputLayoutCount = (int)inputLayouts.size();
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputDescs(inputLayoutCount);

	// インプットレイアウト設定
	{
		int i = 0;
		for (const auto& inputLayout : inputLayouts)
		{
			const char* semantics = nullptr;
			DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
			if (inputLayout == GraphicsPipelineInputLayout::POSITION)
			{
				semantics = "POSITION";
				format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (inputLayout == GraphicsPipelineInputLayout::UV)
			{
				semantics = "UV";
				format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (inputLayout == GraphicsPipelineInputLayout::NORMAL)
			{
				semantics = "NORMAL";
				format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (inputLayout == GraphicsPipelineInputLayout::COLOR)
			{
				semantics = "COLOR";
				format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			inputDescs[i] = { semantics, 0,format, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
			++i;
		}
	}

	// ブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC blendDesc = {};
	SetBlendMode(blendDesc, info.blendMode);

	//PSOの各種設定
	HRESULT result;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.VS.BytecodeLength =  shaderStages.vShader->GetShaderBinaryData()->GetBufferSize();
	psoDesc.VS.pShaderBytecode = shaderStages.vShader->GetShaderBinaryData()->GetBufferPointer();
	psoDesc.PS.BytecodeLength =  shaderStages.pShader->GetShaderBinaryData()->GetBufferSize();
	psoDesc.PS.pShaderBytecode = shaderStages.pShader->GetShaderBinaryData()->GetBufferPointer();
	if (shaderStages.gShader)
	{
		psoDesc.GS.BytecodeLength = shaderStages.gShader->GetShaderBinaryData()->GetBufferSize();
		psoDesc.GS.pShaderBytecode = shaderStages.gShader->GetShaderBinaryData()->GetBufferPointer();
	}
	if (shaderStages.hShader)
	{
		psoDesc.HS.BytecodeLength = shaderStages.hShader->GetShaderBinaryData()->GetBufferSize();
		psoDesc.HS.pShaderBytecode = shaderStages.hShader->GetShaderBinaryData()->GetBufferPointer();
	}
	if (shaderStages.dShader)
	{
		psoDesc.DS.BytecodeLength = shaderStages.dShader->GetShaderBinaryData()->GetBufferSize();
		psoDesc.DS.pShaderBytecode = shaderStages.dShader->GetShaderBinaryData()->GetBufferPointer();
	}

	psoDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;

	psoDesc.RasterizerState.DepthClipEnable = info.isUseDepthClip;
	psoDesc.DepthStencilState.DepthEnable = info.isUseDepthClip;
	psoDesc.DepthStencilState.DepthWriteMask = (D3D12_DEPTH_WRITE_MASK)info.isWriteDepthStencil;
	psoDesc.DepthStencilState.DepthFunc = (D3D12_COMPARISON_FUNC)info.depthComparison;
	psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	psoDesc.BlendState.AlphaToCoverageEnable = info.isUseAlphaToCoverage;

	psoDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	psoDesc.BlendState.RenderTarget[0] = blendDesc;
	psoDesc.InputLayout.pInputElementDescs = inputDescs.data();
	psoDesc.InputLayout.NumElements = inputLayoutCount;
	psoDesc.PrimitiveTopologyType = (shaderStages.dShader && shaderStages.hShader) ? D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH : (D3D12_PRIMITIVE_TOPOLOGY_TYPE)info.topologyType;
	psoDesc.NumRenderTargets = info.renderTargetCount;

	for (int i = 0; i < info.renderTargetCount; ++i)
	{
		psoDesc.RTVFormats[i] = DXGI_FORMAT_R8G8B8A8_UNORM;
	}

	psoDesc.SampleDesc.Count = 1;
	psoDesc.pRootSignature = rootSignature ? rootSignature->GetRootSignature() : nullptr;
	result = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&solidPipeline));
	psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	result = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&wireframePipeline));

	this->rootSignature = rootSignature;
	graphicsPipelineInfo = info;
}

ID3D12PipelineState* GE::GraphicsPipeline::GetWireframePipeline()
{
	return wireframePipeline;
}

ID3D12PipelineState* GE::GraphicsPipeline::GetSolidPipeline()
{
	return solidPipeline;
}

ID3D12RootSignature* GE::GraphicsPipeline::GetRootSignature()
{
	if (rootSignature)return rootSignature->GetRootSignature();
	return nullptr;
}

int GE::GraphicsPipeline::GetTopologyType()
{
	return (int)graphicsPipelineInfo.topologyType;
}
