#include "..\..\Header\Graphics\Layer.h"

GE::Layer::Layer()
	: name(std::string())
	, renderTexture(nullptr)
	, depthTexture(nullptr)
{
}

GE::Layer::~Layer()
{
	delete renderTexture;
	delete depthTexture;
}

void GE::Layer::Create(const std::string& name, IRenderTexture* newRenderTexture, IDepthTexture* newDepthTexture)
{
	this->name = name;
	renderTexture = newRenderTexture;
	depthTexture = newDepthTexture;
}

GE::IRenderTexture* GE::Layer::GetRenderTexture()
{
	return renderTexture;
}

GE::IDepthTexture* GE::Layer::GetDepthTexture()
{
	return depthTexture;
}

void GE::Layer::SetName(const std::string& name)
{
	this->name = name;
}
