#pragma once
#include "Component.h"
#include "..\..\Input\InputDevice.h"

namespace GE
{
	class SampleComponent : public Component
	{
	private:
		InputDevice* inputDevice;
		Math::Vector3 random;
		float speed;
	public:
		SampleComponent();
		~SampleComponent();
		void Awake() override;
		void Start() override;
		void Update(float deltaTime) override;
		void Draw() override;
		void LateDraw() override;
		void OnCollision(GameObject* other) override;
		void OnCollision(ICollider* hitCollider) override;
		void OnGui() override;
	};
}