#pragma once
#include "..\GameObject\GameObject.h"

namespace GE
{
	class ICollider;
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

		/// <summary>
		/// OnCollision系統の関数で一番最初に呼ばれます
		/// </summary>
		/// <param name="other">ヒットしたコライダーがアタッチされているゲームオブジェクト</param>
		virtual void OnCollision(GameObject* other) {}

		/// <summary>
		/// OnCollision(GameObject* other)のあとに呼ばれます
		/// </summary>
		/// <param name="hitCollider">ヒットしたコライダーのインターフェイス</param>
		virtual void OnCollision(ICollider* hitCollider) {}

		bool IsOpenTreeNodeGui();
		virtual void OnGui() {}

		GameObject* GetGameObject();
		bool GetEnabled();
		
		void SetGameObject(GameObject* object);
		void SetTransform(Transform* transform);
		void SetEnabled(bool flag);
		void SetGraphicsDevice(IGraphicsDeviceDx12* graphicsDevice);
	};
}
