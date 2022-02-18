#pragma once
#include "..\..\Util\Math\Vector3.h"

namespace GE
{
	enum class ColliderType
	{
		NONE,
		SPHERE,
		AABB,
		OBB,
		CAPSULE,
	};

	struct Bounds
	{
		Math::Vector3 center = {0,0,0};
		Math::Vector3 max = {0.5f};
		Math::Vector3 min = {-0.5f};
		Math::Vector3 size = 1;
	};
}