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

		// ICollider interface

		ColliderType GetType() override;
		const Math::Axis& GetAxis() override;
		const Bounds& GetBounds() override;
		void Hit() override;
	};
}
