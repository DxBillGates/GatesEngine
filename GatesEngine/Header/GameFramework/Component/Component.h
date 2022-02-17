#pragma once
#include "..\GameObject\GameObject.h"

namespace GE
{
	class Collider;
	class Component
	{
	protected:
		GameObject* gameObject;
		Transform* transform;
		bool enabled;

		IGraphicsDeviceDx12* graphicsDevice;
	public:
		Component();
		virtual ~Component() {}
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void Draw() {}
		virtual void LateDraw() {}
		virtual void OnCollision(GameObject* other) {}
		virtual void OnCollision(Collider* hitCollider) {}

		GameObject* GetGameObject();
		bool GetEnabled();
		
		void SetGameObject(GameObject* object);
		void SetTransform(Transform* transform);
		void SetEnabled(bool flag);
		void SetGraphicsDevice(IGraphicsDeviceDx12* graphicsDevice);
	};
}
