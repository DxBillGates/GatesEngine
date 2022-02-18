#include "..\..\..\Header\GameFramework\Collision\CollisionManager.h"

#include <array>
#include <cmath>

bool GE::CollisionManager::CheckHit(ICollider* col1, ICollider* col2)
{
	ColliderType col1Type = col1->GetType();
	ColliderType col2Type = col2->GetType();

	if (col1Type == col2Type)
	{
		if (col1Type == ColliderType::SPHERE)CheckSphere(col1,col2);
		else if (col1Type == ColliderType::AABB)CheckAABB(col1, col2);
		else if (col1Type == ColliderType::OBB)CheckOBB(col1, col2);
	}
	return false;
}

bool GE::CollisionManager::CheckSphere(ICollider* col1, ICollider* col2)
{
	float distance = Math::Vector3::Distance(col1->GetBounds().center, col2->GetBounds().center);
	return (distance <= col1->GetBounds().size.x * col2->GetBounds().size.x);
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

	const Math::Vector3 intervalVec = bound2.center - bound1.center;


	Math::Vector3 ae1 = axis1.x * bound1.size.x;
	Math::Vector3 ae2 = axis1.y * bound1.size.y;
	Math::Vector3 ae3 = axis1.z * bound1.size.z;
	Math::Vector3 be1 = axis2.x * bound2.size.x;
	Math::Vector3 be2 = axis2.y * bound2.size.y;
	Math::Vector3 be3 = axis2.z * bound2.size.z;

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
	rB = LengthSegmentSeparateAxis(cross, be3, be3);
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
	cross = Math::Vector3::Cross(axis1.z, axis2.y);
	rA = LengthSegmentSeparateAxis(cross, ae1, ae2);
	rB = LengthSegmentSeparateAxis(cross, be1, be2);
	l = std::fabs(Math::Vector3::Dot(intervalVec, cross));
	if (l > rA + rB)return false;

	return true;
}
