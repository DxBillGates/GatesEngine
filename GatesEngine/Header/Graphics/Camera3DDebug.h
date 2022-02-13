#pragma once
#include "Camera3D.h"
#include "..\Input\InputDevice.h"

namespace GE
{
	class Camera3DDebug : public Camera3D
	{
	private:
		Keyboard* keyboard;
		Mouse* mouse;
		float moveSpeed;
	public:
		Camera3DDebug();
		~Camera3DDebug();
		void Initialize() override;
		void Update() override;
	};
}
