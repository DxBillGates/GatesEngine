#pragma once
#include "..\Util\Math\Vector2.h"

namespace GE
{
	class ITexture
	{
	public:
		virtual ~ITexture() {}
		virtual int GetSRVNumber() = 0;
	};
}
