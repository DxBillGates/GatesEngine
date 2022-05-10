#include "..\..\Header\Graphics\RenderQueue.h"

GE::RenderQueue::RenderQueue()
	: currentSetRenderTarget(nullptr)
	, currentSetDepthStencil(nullptr)
	, currentSetPipeline(nullptr)
	, currentSetPipelineIsWireframe(false)
	, currentSetDrawMesh(nullptr)
	, depth(0)
{
}

void GE::RenderQueue::SetLayer(IRenderTarget* setRenderTarget, IDepthStencil* setDepthStencil)
{
	currentSetRenderTarget = setRenderTarget;
	currentSetDepthStencil = setDepthStencil;
}

void GE::RenderQueue::SetPipeline(IGraphicsPipeline* setPipeline,bool isWireframe)
{
	currentSetPipeline = setPipeline;
	currentSetPipelineIsWireframe = isWireframe;
}

void GE::RenderQueue::AddSetShaderResource(const ShaderResourceCommand& command)
{
	currentSetShaderResources.push_back(command);
}

void GE::RenderQueue::AddSetConstantBufferInfo(const ShaderResourceCommand& command)
{
	currentSetConstantBufferViews.push_back(command);
}

void GE::RenderQueue::SetMesh(IMesh* drawMesh)
{
	currentSetDrawMesh = drawMesh;
}

void GE::RenderQueue::SetDepth(float value)
{
	depth = value;
}

void GE::RenderQueue::AddCommand()
{
	RenderingCommand addCommand;
	addCommand =
	{
		currentSetRenderTarget,
		currentSetDepthStencil,
		currentSetPipeline,
		currentSetPipelineIsWireframe,
		currentSetShaderResources,
		currentSetConstantBufferViews,
		currentSetDrawMesh,
		depth 
	};
	renderingCommands.emplace_back(addCommand);

	currentSetConstantBufferViews.clear();
	currentSetShaderResources.clear();
}

void GE::RenderQueue::ZSortCommand()
{
}

void GE::RenderQueue::Execute(ID3D12GraphicsCommandList* cmdList, IShaderResourceHeap* shaderResourceHeap)
{
	for (auto& command : renderingCommands)
	{
		IRenderTarget* renderTarget = command.renderTarget;
		IDepthStencil* depthStencil = command.depthStencil;
		IGraphicsPipeline* usePipeline = command.pipeline;

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetHandle();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = (depthStencil) ? depthStencil->GetHandle() : D3D12_CPU_DESCRIPTOR_HANDLE();

		D3D12_VIEWPORT viewport = {};
		D3D12_RECT _rect = {};

		viewport.Height = renderTarget->GetSize().y;
		viewport.Width = renderTarget->GetSize().x;
		viewport.MaxDepth = 1;

		_rect.bottom = (LONG)renderTarget->GetSize().y;
		_rect.right = (LONG)renderTarget->GetSize().x;

		renderTarget->Prepare(cmdList);
		cmdList->RSSetViewports(1, &viewport);
		cmdList->RSSetScissorRects(1, &_rect);

		if(depthStencil)cmdList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);
		else cmdList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

		ID3D12PipelineState* pipeline = (command.isWireframe) ? usePipeline->GetWireframePipeline() : usePipeline->GetSolidPipeline();
		cmdList->SetPipelineState(pipeline);
		cmdList->SetGraphicsRootSignature(usePipeline->GetRootSignature());

		for (auto& shaderResourceCommand : command.shaderResources)
		{
			cmdList->SetGraphicsRootDescriptorTable(shaderResourceCommand.descIndex, shaderResourceHeap->GetGPUHandleForSRV(shaderResourceCommand.viewNumber));
		}

		for (auto& constantBufferViewCommand : command.constantBufferViews)
		{
			cmdList->SetGraphicsRootDescriptorTable(constantBufferViewCommand.descIndex, shaderResourceHeap->GetGPUHandleForCBV(constantBufferViewCommand.viewNumber));
		}

		GraphicsPipelinePrimitiveTopolotyType topologyType = (GraphicsPipelinePrimitiveTopolotyType)usePipeline->GetTopologyType();
		D3D_PRIMITIVE_TOPOLOGY primitiveType = {};

		if (topologyType == GraphicsPipelinePrimitiveTopolotyType::UNDIFINED)primitiveType = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		else if (topologyType == GraphicsPipelinePrimitiveTopolotyType::POINT)primitiveType = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		else if (topologyType == GraphicsPipelinePrimitiveTopolotyType::LINE)primitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		else if (topologyType == GraphicsPipelinePrimitiveTopolotyType::TRIANGLE)primitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		else if (topologyType == GraphicsPipelinePrimitiveTopolotyType::PATCH)primitiveType = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST;

		cmdList->IASetPrimitiveTopology(primitiveType);

		command.drawMesh->Draw();
	}

	renderingCommands.clear();
}
