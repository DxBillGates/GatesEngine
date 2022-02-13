#pragma once
#include "..\Util\Math\Vector2.h"

namespace GE
{
	class ITexture
	{
	public:
		virtual ~ITexture() {}
		virtual int GetSRVNumber() = 0;
		virtual const Math::Vector2& GetSize() = 0;
	};
}
