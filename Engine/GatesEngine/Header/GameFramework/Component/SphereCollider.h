#pragma once
#include "Collider.h"

namespace GE
{
	class SphereCollider : public Collider
	{
	private:
		bool isSetCenter;
		float r;
	public:
		SphereCollider();
		~SphereCollider();
		void Awake() override;
		void Draw() override;
		void OnGui() override;
		void SetSize(float size);
		void SetCenter(const Math::Vector3& pos);
		void DrawEnabled(bool flag);
	};
}