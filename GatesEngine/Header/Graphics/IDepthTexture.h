#pragma once
#include "IDepthStencil.h"
#include "ITexture.h"

namespace GE
{
	class IDepthTexture : public IDepthStencil, public ITexture
	{
	public:
		virtual ~IDepthTexture() {};
	};
}
