#pragma once
#include "Collider.h"

namespace GE
{
	class BoxCollider : public Collider
	{
	private:
		bool isSetCenter;
	public:
		BoxCollider();
		~BoxCollider();
		void Awake() override;
		void Draw() override;
		void OnGui() override;
		void SetSize(const Math::Vector3& size);
		void SetCenter(const Math::Vector3& pos);
		void DrawEnabled(bool flag);
		void SetType(ColliderType type);
	};
}
