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
	// �e�̉�]�s��Ǝ��g�̉�]�s�񂩂玲���擾
	localAxis = Math::Matrix4x4(localRotation * Math::Matrix4x4::RotationZXY(transform->rotation)).GetAxis();

	// ���[���h�s�񂩂���ۂ̍��W���擾
	Math::Matrix4x4 worldMatrix = GetMatrix();
	Math::Vector3 pos = worldMatrix.GetPosition();

	// ���ۂ̃X�P�[�����擾
	Math::Vector3 scale = bounds.size * transform->scale / 2;

	// AABB��OBB��max��min�̍��W���قȂ�̂ŏC��
	if (type == ColliderType::AABB)
	{
		bounds.max = pos + scale;
		bounds.min = pos - scale;
	}
	else
	{
		bounds.max = pos + (localAxis.x + localAxis.y + localAxis.z) / 3 * scale;
		bounds.min = pos - (localAxis.x + localAxis.y + localAxis.z) / 3 * scale;
	}

	// hit����t���O�Ǘ�
	const float MAX_HIT_TIME = 0.1f;
	hitFlagController.SetMaxTimeProperty(MAX_HIT_TIME);
	if (hitFlagController.GetOverTimeTrigger())hitFlagController.SetFlag(false);
	hitFlagController.Update(deltaTime);
}

void GE::Collider::SetLocalRotation(const Math::Vector3& axis, float angle)
{
	localRotation = Math::Quaternion::Rotation(Math::Quaternion(axis, angle));
}

void GE::Collider::SetLocalRotation(const Math::Vector3& value)
{
	localRotation = Math::Matrix4x4::RotationZXY(value);
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

GE::Transform* GE::Collider::GetParent()
{
	return transform;
}

GE::Math::Matrix4x4 GE::Collider::GetMatrix()
{
	Math::Matrix4x4 scaleMatrix = Math::Matrix4x4::Scale(bounds.size);
	Math::Matrix4x4 translateMatrix = Math::Matrix4x4::Translate(bounds.center);
	return scaleMatrix * localRotation * translateMatrix * transform->GetMatrix();
}

void GE::Collider::Hit(ICollider* hitCollider, GameObject* other)
{
	gameObject->OnCollision(other);
	gameObject->OnCollision(hitCollider);

	hitFlagController.SetTime(0);
	hitFlagController.SetFlag(true);
}
