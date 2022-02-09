#pragma once
#include "..\..\Audio\AudioManager.h"
#include "..\..\Input\InputDevice.h"

#include <string>

namespace GE
{
	struct SceneInitializer
	{
		AudioManager* audioManager;
		InputDevice* inputDevice;
	};

	struct ChangeSceneInfo
	{
		std::string name;
		bool flag;
		bool initNextSceneFlag;
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
	public:
		Scene();
		Scene(const std::string& sceneName);
		virtual ~Scene();
		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Draw();
		virtual void LateDraw();

		const std::string& GetSceneName();
		bool IsTerminateApplication();
		const ChangeSceneInfo& IsChangeScene();

		void SetSceneInitializer(const SceneInitializer& initializer);
	};
}
