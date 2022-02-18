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
	bounds.max = bounds.center + bounds.size / 2;
	bounds.min = bounds.center + -bounds.size / 2;


	const float MAX_HIT_TIME = 0.5f;
	hitFlagController.SetMaxTimeProperty(MAX_HIT_TIME);
	hitFlagController.Update(deltaTime);
}

GE::ColliderType GE::Collider::GetType()
{
	return type;
}

const GE::Math::Axis& GE::Collider::GetAxis()
{
	return localAxis;
}

const GE::Bounds& GE::Collider::GetBounds()
{
	return bounds;
}

void GE::Collider::Hit()
{
	hitFlagController.SetTime(0);
	hitFlagController.SetFlag(true);
}
