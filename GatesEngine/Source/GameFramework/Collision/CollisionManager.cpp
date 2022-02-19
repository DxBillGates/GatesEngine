#include "..\..\..\Header\GameFramework\Collision\CollisionManager.h"

#include <array>
#include <cmath>

bool GE::CollisionManager::CheckHit(ICollider* col1, ICollider* col2)
{
	ColliderType col1Type = col1->GetType();
	ColliderType col2Type = col2->GetType();

	int bitResult = 0;
	bitResult = (int)col2Type | (int)col1Type;
	bool collisionCheck = false;

	switch ((CollisionBitCombination)bitResult)
	{
	case GE::CollisionBitCombination::NONE:
		break;
	case GE::CollisionBitCombination::SPHERE_SPHERE:
		collisionCheck = CheckSphere(col1, col2);
		break;
	case GE::CollisionBitCombination::SPHERE_AABB:
		if (col1Type == ColliderType::SPHERE)collisionCheck = CheckSphereToAABB(col1,col2);
		else collisionCheck = CheckSphereToAABB(col2, col1);
		break;
	case GE::CollisionBitCombination::SPHERE_OBB:
		if (col1Type == ColliderType::SPHERE)collisionCheck = CheckSphereToOBB(col1, col2);
		else collisionCheck = CheckSphereToOBB(col2, col1);
		break;
	case GE::CollisionBitCombination::SPHERE_CAPSULE:
		break;
	case GE::CollisionBitCombination::AABB_AABB:
		collisionCheck = CheckAABB(col1, col2);
		break;
	case GE::CollisionBitCombination::AABB_OBB:
		break;
	case GE::CollisionBitCombination::AABB_CAPSULE:
		break;
	case GE::CollisionBitCombination::OBB_OBB:
		collisionCheck = CheckOBB(col1, col2);
		break;
	case GE::CollisionBitCombination::OBB_CAPSULE:
		break;
	case GE::CollisionBitCombination::CAPSULE_CAPSULE:
		break;
	default:
		break;
	}

	return collisionCheck;
}

bool GE::CollisionManager::CheckSphere(ICollider* col1, ICollider* col2)
{
	Math::Vector3 center1 = col1->GetMatrix().GetPosition();
	Math::Vector3 center2 = col2->GetMatrix().GetPosition();

	Math::Vector3 scale1 = col1->GetBounds().size * col1->GetParent()->scale;
	Math::Vector3 scale2 = col2->GetBounds().size * col2->GetParent()->scale;

	float distance = Math::Vector3::Distance(center1, center2);
	return (distance * distance <= scale1.x * scale2.x);
}

bool GE::CollisionManager::CheckAABB(ICollider* col1, ICollider* col2)
{
	Math::Vector3 min1, min2, max1, max2;
	min1 = col1->GetBounds().min;
	max1 = col1->GetBounds().max;
	min2 = col2->GetBounds().min;
	max2 = col2->GetBounds().max;

	if (min1.x > max2.x)return false;
	if (max1.x < min2.x)return false;
	if (min1.y > max2.y)return false;
	if (max1.y < min2.y)return false;
	if (min1.z > max2.z)return false;
	if (max1.z < min2.z)return false;
	return true;
}

bool GE::CollisionManager::CheckOBB(ICollider* col1, ICollider* col2)
{
	const Bounds& bound1 = col1->GetBounds();
	const Bounds& bound2 = col2->GetBounds();
	const Math::Axis& axis1 = col1->GetAxis();
	const Math::Axis& axis2 = col2->GetAxis();


	Math::Vector3 center1 = col1->GetMatrix().GetPosition();
	Math::Vector3 center2 = col2->GetMatrix().GetPosition();
	const Math::Vector3 intervalVec = center2 - center1;


	Math::Vector3 scale1 = bound1.size * col1->GetParent()->scale / 2;
	Math::Vector3 scale2 = bound2.size * col2->GetParent()->scale / 2;

	Math::Vector3 ae1 = axis1.x * scale1.x;
	Math::Vector3 ae2 = axis1.y * scale1.y;
	Math::Vector3 ae3 = axis1.z * scale1.z;
	Math::Vector3 be1 = axis2.x * scale2.x;
	Math::Vector3 be2 = axis2.y * scale2.y;
	Math::Vector3 be3 = axis2.z * scale2.z;

	auto LengthSegmentSeparateAxis = [](const Math::Vector3& sep, const Math::Vector3& e1, const Math::Vector3& e2, const Math::Vector3& e3 = 0)
	{
		float r1 = std::fabs(Math::Vector3::Dot(sep, e1));
		float r2 = std::fabs(Math::Vector3::Dot(sep, e2));
		float r3 = (e3.Length() != 0) ? std::fabs(Math::Vector3::Dot(sep, e3)) : 0;
		return r1 + r2 + r3;
	};

	// •ª—£Ž² Ae1
	float rA = ae1.Length();
	float rB = LengthSegmentSeparateAxis(axis1.x, be1, be2, be3);
	float l = std::fabs(Math::Vector3::Dot(intervalVec, axis1.x));
	if (l > rA + rB)return false;

	// •ª—£Ž² Ae2
	rA = ae2.Length();
	rB = LengthSegmentSeparateAxis(axis1.y, be1, be2, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, axis1.y));
	if (l > rA + rB)return false;

	// •ª—£Ž² Ae3
	rA = ae3.Length();
	rB = LengthSegmentSeparateAxis(axis1.z, be1, be2, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, axis1.z));
	if (l > rA + rB)return false;

	// •ª—£Ž² Be1
	rA = LengthSegmentSeparateAxis(axis2.x, ae1, ae2, ae3);
	rB = be1.Length();
	l = std::fabs(Math::Vector3::Dot(intervalVec, axis2.x));
	if (l > rA + rB)return false;

	// •ª—£Ž² Be2
	rA = LengthSegmentSeparateAxis(axis2.y, ae1, ae2, ae3);
	rB = be2.Length();
	l = std::fabs(Math::Vector3::Dot(intervalVec, axis2.y));
	if (l > rA + rB)return false;

	// •ª—£Ž² Be3
	rA = LengthSegmentSeparateAxis(axis2.z, ae1, ae2, ae3);
	rB = be3.Length();
	l = std::fabs(Math::Vector3::Dot(intervalVec, axis2.z));
	if (l > rA + rB)return false;

	// •ª—£Ž² C11
	Math::Vector3 cross = Math::Vector3::Cross(axis1.x, axis2.x);
	rA = LengthSegmentSeparateAxis(cross, ae2, ae3);
	rB = LengthSegmentSeparateAxis(cross, be2, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C12
	cross = Math::Vector3::Cross(axis1.x, axis2.y);
	rA = LengthSegmentSeparateAxis(cross, ae2, ae3);
	rB = LengthSegmentSeparateAxis(cross, be1, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C13
	cross = Math::Vector3::Cross(axis1.x, axis2.z);
	rA = LengthSegmentSeparateAxis(cross, ae2, ae3);
	rB = LengthSegmentSeparateAxis(cross, be1, be2);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C21
	cross = Math::Vector3::Cross(axis1.y, axis2.x);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae3);
	rB = LengthSegmentSeparateAxis(cross, be2, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C22
	cross = Math::Vector3::Cross(axis1.y, axis2.y);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae3);
	rB = LengthSegmentSeparateAxis(cross, be1, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C23
	cross = Math::Vector3::Cross(axis1.y, axis2.z);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae3);
	rB = LengthSegmentSeparateAxis(cross, be1, be2);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C31
	cross = Math::Vector3::Cross(axis1.z, axis2.x);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae2);
	rB = LengthSegmentSeparateAxis(cross, be2, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C32
	cross = Math::Vector3::Cross(axis1.z, axis2.y);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae2);
	rB = LengthSegmentSeparateAxis(cross, be1, be3);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	// •ª—£Ž² C33
	cross = Math::Vector3::Cross(axis1.z, axis2.z);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae2);
	rB = LengthSegmentSeparateAxis(cross, be1, be2);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	return true;
}

bool GE::CollisionManager::CheckSphereToAABB(ICollider* sphere, ICollider* box)
{
	const Bounds& sphereBounds = sphere->GetBounds();
	const Bounds& boxBounds = box->GetBounds();

	Math::Vector3 sphereCenter = sphere->GetMatrix().GetPosition();
	Math::Vector3 localColliderRadius = sphereBounds.size;
	Math::Vector3 parentScale = sphere->GetParent()->scale;
	Math::Vector3 worldColliderSize = (localColliderRadius * parentScale) / 2;

	float radius = (worldColliderSize.x + worldColliderSize.y + worldColliderSize.z) / 3;

	float length = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (sphereCenter.value[i] < boxBounds.min.value[i])
		{
			length += (sphereCenter.value[i] - boxBounds.min.value[i]) * (sphereCenter.value[i] - boxBounds.min.value[i]);
		}
		if (sphereCenter.value[i] > boxBounds.max.value[i])
		{
			length += (sphereCenter.value[i] - boxBounds.max.value[i]) * (sphereCenter.value[i] - boxBounds.max.value[i]);
		}
	}

	if (length < radius * radius)
	{
		return true;
	}

	return false;
}

bool GE::CollisionManager::CheckSphereToOBB(ICollider* sphere, ICollider* box)
{
	const Bounds& sphereBounds = sphere->GetBounds();
	const Bounds& boxBounds = box->GetBounds();
	const Math::Axis& boxAxis = box->GetAxis();
	Math::Vector3 boxColliderSize = boxBounds.size * box->GetParent()->scale;

	Math::Vector3 boxCenter = box->GetMatrix().GetPosition();
	Math::Vector3 sphereCenter = sphere->GetMatrix().GetPosition();
	Math::Vector3 localColliderRadius = sphereBounds.size;
	Math::Vector3 parentScale = sphere->GetParent()->scale;
	Math::Vector3 worldColliderSize = (localColliderRadius * parentScale) / 2;

	float radius = (worldColliderSize.x + worldColliderSize.y + worldColliderSize.z) / 3;

	Math::Vector3 vec;
	for (int i = 0; i < 3; ++i)
	{
		Math::Vector3 axis = boxAxis.value[i] * boxColliderSize.value[i];
		float l = axis.Length()/2;
		if (l <= 0)continue;
		float s = Math::Vector3::Dot((sphereCenter - boxCenter), boxAxis.value[i]) / l;

		s = std::fabs(s);
		if (s > 1)
		{
			vec += (1 - s) * l * boxAxis.value[i];
		}
	}

	float length = vec.Length();
	if (length < radius)
	{
		return true;
	}

	return false;
}
