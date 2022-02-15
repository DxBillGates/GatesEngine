#pragma once
#include "ILayer.h"

namespace GE
{
	class Layer : public ILayer
	{
	private:
		IRenderTexture* renderTexture;
		IDepthTexture* depthTexture;
	public:
		Layer(IRenderTexture* newRenderTexture = nullptr, IDepthTexture* newDepthTexture = nullptr);
		~Layer();
		void Create(IRenderTexture* newRenderTexture, IDepthTexture* newDepthTexture);

		// interface

		IRenderTexture* GetRenderTexture() override;
		IDepthTexture* GetDepthTexture() override;
	};
}
