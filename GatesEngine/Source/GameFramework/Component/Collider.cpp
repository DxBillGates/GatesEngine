#include "..\..\..\Header\GameFramework\Component\Collider.h"

GE::Collider::Collider()
	: type(ColliderType::NONE)
	, localRotation(Math::Matrix4x4::Identity())
	, localAxis(Math::Axis())
	, bounds(Bounds())
	, hitFlagController(FlagController())
	, drawEnabled(true)
{
}

GE::Collider::~Collider()
{
}

void GE::Collider::Update(float deltaTime)
{
	localAxis = localRotation.GetAxis();
	bounds.max = Math::Matrix4x4::Transform(bounds.center + bounds.size / 2,localRotation);
	bounds.min = Math::Matrix4x4::Transform(bounds.center + -bounds.size / 2, localRotation);


	const float MAX_HIT_TIME = 0.5f;
	hitFlagController.SetMaxTimeProperty(MAX_HIT_TIME);
	hitFlagController.Update(deltaTime);
}

void GE::Collider::SetLocalRotation(const Math::Vector3& axis, float angle)
{
	localRotation = Math::Quaternion::Rotation(Math::Quaternion(axis, angle));
}

void GE::Collider::SetLocalRotation(const Math::Vector3& value)
{
	Math::Vector3 vec = { value.z,value.x,value.y };
	localRotation = Math::Matrix4x4::RotationZXY(vec);
}

GE::ColliderType GE::Collider::GetType()
{
	return type;
}

const GE::Math::Axis& GE::Collider::GetAxis()
{
	localAxis = localRotation.GetAxis();
	return localAxis;
}

const GE::Bounds& GE::Collider::GetBounds()
{
	bounds.max = Math::Matrix4x4::Transform(bounds.center + bounds.size / 2, localRotation);
	bounds.min = Math::Matrix4x4::Transform(bounds.center + -bounds.size / 2, localRotation);

	return bounds;
}

void GE::Collider::Hit()
{
	hitFlagController.SetTime(0);
	hitFlagController.SetFlag(true);
}
