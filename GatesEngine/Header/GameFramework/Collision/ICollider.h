#pragma once
#include "ColliderInfo.h"
#include "..\..\Util\Math\Axis.h"
#include "..\..\Util\Math\Transform.h"

namespace GE
{
	class GameObject;
	class ICollider
	{
	public:
		virtual ~ICollider() {}
		virtual ColliderType GetType() = 0;
		virtual const Math::Axis& GetAxis() = 0;
		virtual const Bounds& GetBounds() = 0;
		virtual Transform* GetParent() = 0;
		virtual Math::Matrix4x4 GetMatrix() = 0;
		virtual void Hit(ICollider* hitCollider,GameObject* other) = 0;
	};
}