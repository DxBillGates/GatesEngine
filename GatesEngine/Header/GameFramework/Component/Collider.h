#pragma once
#include "Component.h"
#include "..\Collision\ICollider.h"
#include "..\FlagController.h"

namespace GE
{
	class Collider : public Component, public ICollider
	{
	protected:
		ColliderType type;
		Math::Matrix4x4 localRotation;
		Math::Axis localAxis;
		Bounds bounds;
		FlagController hitFlagController;
		bool drawEnabled;
	public:
		Collider();
		virtual ~Collider() = 0;

		void Update(float deltaTime) override;
		void SetLocalRotation(const Math::Vector3& axis,float angle);
		void SetLocalRotation(const Math::Vector3& value);

		// ICollider interface

		ColliderType GetType() override;
		const Math::Axis& GetAxis() override;
		const Bounds& GetBounds() override;
		Transform* GetParent() override;
		Math::Matrix4x4 GetMatrix() override;
		void Hit(ICollider* hitCollider, GameObject* other) override;
	};
}
