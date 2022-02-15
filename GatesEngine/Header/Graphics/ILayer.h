#pragma once
#include "IRenderTexture.h"
#include "IDepthTexture.h"

#include <string>

namespace GE
{
	class ILayer
	{
	public:
		virtual ~ILayer() {}
		virtual IRenderTexture* GetRenderTexture() = 0;
		virtual IDepthTexture* GetDepthTexture() = 0;
	};
}
