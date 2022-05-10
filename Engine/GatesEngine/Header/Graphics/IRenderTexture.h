#pragma once
#include "IRenderTarget.h"
#include "ITexture.h"

namespace GE
{
	class IRenderTexture : public IRenderTarget, public ITexture
	{
	public:
		virtual ~IRenderTexture() {};
		virtual void EndDraw(ID3D12GraphicsCommandList* cmdList) = 0;
	};
}
