#pragma once
#include <string>
#include "..\Util\Timer.h"
#include "..\Graphics\Window.h"
#include "..\Input\InputDevice.h"
#include "..\Audio\AudioManager.h"
#include "..\GameFramework\Scene\SceneManager.h"
#include "..\Graphics\GraphicsDeviceDx12.h"

namespace GE
{
	// �A�v���P�[�V�����̃x�[�X�N���X
	class Application
	{
	protected:
		Util::Timer timer;
		Window mainWindow;
		InputDevice* inputDevice;
		AudioManager audioManager;
		SceneManager sceneManager;
		GraphicsDeviceDx12 graphicsDevice;
	public:
		Application();
		Application(const Math::Vector2& size,const std::string& title);
		virtual ~Application();
		virtual bool LoadContents();
		virtual bool Initialize();
		virtual bool Update();
		virtual bool Draw();
		virtual int Run();
	};
}