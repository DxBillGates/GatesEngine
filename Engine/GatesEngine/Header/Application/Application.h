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
		Application(const WindowData& windowData,const Math::Vector2& resolution);
		Application(const Math::Vector2& size, const GE::Math::Vector2& resolution,const std::string& title = "no title", WindowMode mode = WindowMode::POP_UP);
		virtual ~Application();
		virtual bool LoadContents();
		virtual bool Initialize();
		virtual bool Update();
		virtual bool Draw();
		virtual int Run();
	};
}