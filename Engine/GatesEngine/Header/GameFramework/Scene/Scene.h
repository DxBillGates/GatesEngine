#pragma once
#include "..\..\Audio\AudioManager.h"
#include "..\..\Input\InputDevice.h"
#include "..\..\Graphics\IGraphicsDeviceDx12.h"
#include "..\..\GameFramework\GameObject\GameObjectManager.h"

#include <string>

namespace GE
{
	struct SceneInitializer
	{
		AudioManager* audioManager;
		InputDevice* inputDevice;
		IGraphicsDeviceDx12* graphicsDevice;

		SceneInitializer()
			: audioManager(nullptr)
			, inputDevice(nullptr)
			, graphicsDevice(nullptr)
		{
		}

		SceneInitializer(AudioManager* audioManager, InputDevice* inputDevice,IGraphicsDeviceDx12* grpahicsDevice)
			: audioManager(audioManager)
			, inputDevice(inputDevice)
			, graphicsDevice(graphicsDevice)
		{
		}
	};

	struct ChangeSceneInfo
	{
		std::string name;
		bool flag;
		bool initNextSceneFlag;

		ChangeSceneInfo()
			: name({})
			, flag(false)
			, initNextSceneFlag(false)
		{
		}
	};

	class Scene
	{
	protected:
		std::string name;
		bool isTerminateApplication;

		bool isSetInitializer;
		ChangeSceneInfo changeSceneInfo;
		AudioManager* audioManager;
		InputDevice* inputDevice;
		IGraphicsDeviceDx12* graphicsDevice;
		GameObjectManager gameObjectManager;
	public:
		Scene();
		Scene(const std::string& sceneName);
		virtual ~Scene() {}
		virtual void Initialize() {}
		virtual void Update(float deltaTime){}
		virtual void Draw() {}
		virtual void LateDraw() {}

		const std::string& GetSceneName();
		bool IsTerminateApplication();
		ChangeSceneInfo& IsChangeScene();

		void SetSceneInitializer(const SceneInitializer& initializer);
	};
}
