#pragma once
#include "ICamera.h"
#include "CBufferAllocater.h"

namespace GE
{
	class Camera : public ICamera
	{
	protected:
		CameraInfo info;
	public:
		Camera()
			: info(CameraInfo())
		{

		}
		virtual ~Camera() {}
		virtual void Initialize() { info = CameraInfo(); }
		virtual void Update() {};
		const CameraInfo& GetCameraInfo() override { return info; }
		void SetPosition(const Math::Vector3& setPos)override { info.cameraPos = setPos; }
		void SetViewMatrix(const Math::Matrix4x4& setMatrix)override { info.viewMatrix = setMatrix; }
		void SetProjectionMatrix(const Math::Matrix4x4& setMatrix)override { info.projMatrix = setMatrix; }
	};
}