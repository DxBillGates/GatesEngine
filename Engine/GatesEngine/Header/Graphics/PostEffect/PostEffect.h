#pragma once
#include "..\IRenderTexture.h"

namespace GE
{
	class PostEffect
	{
	private:
		IRenderTexture* pSource;
	public:
		virtual ~PostEffect() {}
		void SetSource(IRenderTexture* source)
		{
			pSource = source;
		}
		virtual void Execute() = 0;
		virtual IRenderTexture* GetResult() = 0;
	};
}
