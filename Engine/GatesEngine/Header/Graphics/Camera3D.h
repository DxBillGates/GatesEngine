#pragma once
#include "Camera.h"

namespace GE
{
	class Camera3D : public Camera
	{
	protected:
		Math::Vector3 direction;
		Math::Vector3 up;

		float yaw;
		float pitch;

		Math::Matrix4x4 rotation;

		Math::Vector2 windowSize;
		float aspect;
	public:
		Camera3D();
		virtual ~Camera3D() {}
		void Initialize() override;
		void SetDirection(const Math::Vector3& setVector) { direction = setVector; }
		void SetYaw(float value) { yaw = value; }
		void SetPitch(float value) { pitch = value; }
		void SetWindowSize(const Math::Vector2& size);
		void SetAspect(float value);
		const Math::Matrix4x4& GetRotation() { return rotation; }
	};
}
