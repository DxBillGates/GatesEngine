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
		/// OnCollision�n���̊֐��ň�ԍŏ��ɌĂ΂�܂�
		/// </summary>
		/// <param name="other">�q�b�g�����R���C�_�[���A�^�b�`����Ă���Q�[���I�u�W�F�N�g</param>
		virtual void OnCollision(GameObject* other) {}

		/// <summary>
		/// OnCollision(GameObject* other)�̂��ƂɌĂ΂�܂�
		/// </summary>
		/// <param name="hitCollider">�q�b�g�����R���C�_�[�̃C���^�[�t�F�C�X</param>
		virtual void OnCollision(ICollider* hitCollider) {}

		GameObject* GetGameObject();
		bool GetEnabled();
		
		void SetGameObject(GameObject* object);
		void SetTransform(Transform* transform);
		void SetEnabled(bool flag);
		void SetGraphicsDevice(IGraphicsDeviceDx12* graphicsDevice);
	};
}
