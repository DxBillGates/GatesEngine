#pragma once
#include "IGraphicsPipeline.h"

#include <string>
#include <map>

namespace GE
{
	class GraphicsPipelineManager
	{
	private:
		std::map<std::string, IGraphicsPipeline*> graphicsPipelines;
	public:
		GraphicsPipelineManager();
		~GraphicsPipelineManager();
		void Add(IGraphicsPipeline* newGraphicsPipeline, const std::string& name);
		IGraphicsPipeline* Get(const std::string& name);
	};
}