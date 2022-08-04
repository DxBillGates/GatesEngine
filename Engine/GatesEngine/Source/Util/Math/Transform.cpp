#include "..\..\..\Header\Util\Math\Transform.h"

GE::Math::Matrix4x4 GE::Transform::GetMatrix()
{
	return Math::Matrix4x4::Scale(scale) * Math::Quaternion::Euler(rotation).Rotation() * Math::Matrix4x4::Translate(position);
}

GE::Math::Vector3 GE::Transform::GetEulerAngle()
{
	return Math::Vector3();
}

GE::Math::Vector3 GE::Transform::GetForward()
{
	GE::Math::Axis axis = GetMatrix().GetAxis();
	return axis.z;
}

GE::Math::Vector3 GE::Transform::GetRight()
{
	GE::Math::Axis axis = GetMatrix().GetAxis();
	return axis.x;
}

GE::Math::Vector3 GE::Transform::GetUp()
{
	GE::Math::Axis axis = GetMatrix().GetAxis();
	return axis.y;
}
