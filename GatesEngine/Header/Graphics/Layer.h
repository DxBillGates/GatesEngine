#pragma once
#include "ILayer.h"

namespace GE
{
	class Layer : public ILayer
	{
	private:
		std::string name;
		IRenderTexture* renderTexture;
		IDepthTexture* depthTexture;
	public:
		Layer();
		~Layer();
		void Create(const std::string& name, IRenderTexture* newRenderTexture, IDepthTexture* newDepthTexture);

		// interface

		IRenderTexture* GetRenderTexture();
		IDepthTexture* GetDepthTexture();
		void SetName(const std::string& name);
	};
}
