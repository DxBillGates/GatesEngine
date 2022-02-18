#pragma once
#include "ColliderInfo.h"
#include "..\..\Util\Math\Axis.h"

namespace GE
{
	class ICollider
	{
	public:
		virtual ~ICollider() {}
		virtual ColliderType GetType() = 0;
		virtual const Math::Axis& GetAxis() = 0;
		virtual const Bounds& GetBounds() = 0;
		virtual void Hit() = 0;
	};
}