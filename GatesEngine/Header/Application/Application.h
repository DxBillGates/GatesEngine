#pragma once
#include <string>
#include "..\Util\Timer.h"
#include "..\Graphics\Window.h"
#include "..\Input\InputDevice.h"
#include "..\Audio\AudioManager.h"
#include "..\GameFramework\Scene\SceneManager.h"
#include "..\Graphics\GraphicsDeviceDx12.h"
#include "..\Graphics\Camera3D.h"

namespace GE
{
	// アプリケーションのベースクラス
	class Application
	{
	protected:
		Utility::Timer timer;
		Window mainWindow;
		InputDevice* inputDevice;
		AudioManager audioManager;
		SceneManager sceneManager;
		GraphicsDeviceDx12 graphicsDevice;
		Camera3D* mainCamera;
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