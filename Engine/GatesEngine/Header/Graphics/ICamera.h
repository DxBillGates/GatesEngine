#pragma once
#include "..\Util\Math\Vector3.h"
#include "..\Util\Math\Matrix4.h"
#include "CBufferStruct.h"

#include <d3d12.h>

namespace GE
{
	class ICamera
	{
	public:
		virtual ~ICamera(){}
		virtual const CameraInfo& GetCameraInfo() = 0;
		virtual void SetPosition(const Math::Vector3& setPos) = 0;
		virtual void SetViewMatrix(const Math::Matrix4x4& setMatrix) = 0;
		virtual void SetProjectionMatrix(const Math::Matrix4x4& setMatrix) = 0;
	};
}
