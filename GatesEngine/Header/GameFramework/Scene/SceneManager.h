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
	public:
		SceneManager();
		~SceneManager();
		void Initialize(const SceneInitializer& initializer);
		void Update(float deltaTime);
		void Draw();
		void LateDraw();

		Scene* AddScene(Scene* newScene);
		Scene* ChangeScene(const std::string& sceneName);
		Scene* GetCurrentScene();
		Scene* GetBeforeScene();
		Scene* GetAddScene();
		Scene* GetScene(const std::string& sceneName);
	};
}