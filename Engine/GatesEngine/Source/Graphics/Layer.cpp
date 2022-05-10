#include "..\..\Header\Graphics\Layer.h"

GE::Layer::Layer(IRenderTexture* newRenderTexture, IDepthTexture* newDepthTexture)
	: renderTexture(newRenderTexture)
	, depthTexture(newDepthTexture)
{
}

GE::Layer::~Layer()
{
	delete renderTexture;
	delete depthTexture;
}

void GE::Layer::Create(IRenderTexture* newRenderTexture, IDepthTexture* newDepthTexture)
{
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
