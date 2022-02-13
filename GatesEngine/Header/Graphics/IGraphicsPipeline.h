#pragma once
#include <d3d12.h>

namespace GE
{
	class IGraphicsPipeline
	{
	public:
		virtual ~IGraphicsPipeline() {}
		virtual ID3D12PipelineState* GetWireframePipeline() = 0;
		virtual ID3D12PipelineState* GetSolidPipeline() = 0;
		virtual ID3D12RootSignature* GetRootSignature() = 0;
		virtual int GetTopologyType() = 0;
	};
}