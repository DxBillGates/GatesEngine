#pragma once
#include "Scene.h"
#include <vector>

namespace GE
{
	class SceneManager
	{
	private:
		std::vector<Scene*> scenes;
		Scene* currentScene;
		Scene* beforeScene;
		Scene* addScene;
		SceneInitializer sceneInitializer;
	public:
		SceneManager();
		~SceneManager();
		void Initialize();
		void Update(float deltaTime);
		void Draw();
		void LateDraw();

		Scene* AddScene(Scene* newScene);
		Scene* ChangeScene(const std::string& sceneName);
		Scene* GetCurrentScene();
		Scene* GetBeforeScene();
		Scene* GetAddScene();
		Scene* GetScene(const std::string& sceneName);
		void SetSceneInitializer(const SceneInitializer& initializer);
	};
}