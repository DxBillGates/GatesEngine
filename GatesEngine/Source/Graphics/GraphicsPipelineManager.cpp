#include "..\..\Header\Graphics\GraphicsPipelineManager.h"

GE::GraphicsPipelineManager::GraphicsPipelineManager()
{
}

GE::GraphicsPipelineManager::~GraphicsPipelineManager()
{
	for (auto& graphicsPipeline : graphicsPipelines)
	{
		delete graphicsPipeline.second;
	}
}

void GE::GraphicsPipelineManager::Add(IGraphicsPipeline* newGraphicsPipeline, const std::string& name)
{
	graphicsPipelines.insert(std::make_pair(name, newGraphicsPipeline));
}

GE::IGraphicsPipeline* GE::GraphicsPipelineManager::Get(const std::string& name)
{
	return graphicsPipelines.at(name);
}
