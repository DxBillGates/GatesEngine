#pragma once
#include "..\..\Util\Math\Vector3.h"

namespace GE
{
	enum class ColliderType
	{
		NONE = 0x00,
		SPHERE = 0x01,
		AABB = 0x02,
		OBB = 0x04,
		CAPSULE = 0x08,
	};

	enum class CollisionBitCombination
	{
		NONE = 0,

		SPHERE_SPHERE = 1,
		SPHERE_AABB = 3,
		SPHERE_OBB = 5,
		SPHERE_CAPSULE = 9,

		AABB_AABB = 2,
		AABB_OBB = 6,
		AABB_CAPSULE = 10,

		OBB_OBB = 4,
		OBB_CAPSULE = 7,

		CAPSULE_CAPSULE = 8,
	};

	struct Bounds
	{
		Math::Vector3 center = {0,0,0};
		Math::Vector3 max = {0.5f};
		Math::Vector3 min = {-0.5f};
		Math::Vector3 size = 1;
	};
}