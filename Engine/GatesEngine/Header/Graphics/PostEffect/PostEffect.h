#pragma once
#include "..\IGraphicsDeviceDx12.h"
#include "..\IRenderTexture.h"

namespace GE
{

	struct EffectInfo
	{
		Math::Vector4 color;
		float threshold;
	};
	class PostEffect
	{
	protected:
		EffectInfo effectInfo;
		IRenderTexture* pSource;
	public:
		PostEffect() : pSource(nullptr) {}
		virtual ~PostEffect() {}

		const EffectInfo& GetEffectInfo()
		{
			return effectInfo;
		}
		void SetEffectInfo(const EffectInfo& value)
		{
			effectInfo = value;
		}
		void SetSource(IRenderTexture* source)
		{
			pSource = source;
		}
		virtual void Execute(IGraphicsDeviceDx12* graphicsDevice) = 0;
		virtual IRenderTexture* GetResult() = 0;
	};
}
