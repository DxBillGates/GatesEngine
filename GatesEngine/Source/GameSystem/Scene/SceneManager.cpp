#include "..\..\..\Header\GameSystem\Scene\SceneManager.h"

GE::SceneManager::SceneManager()
	: currentScene(nullptr)
	, beforeScene(nullptr)
{
}

GE::SceneManager::~SceneManager()
{
	for (auto& scene : scenes)
	{
		delete scene;
	}
}

void GE::SceneManager::Initialize(const SceneInitializer& initializer)
{
	for (auto& scene : scenes)
	{
		scene->Initialize();
		scene->SetSceneInitializer(initializer);
	}
}

void GE::SceneManager::Update(float deltaTime)
{
	if (!currentScene)return;

	currentScene->Update(deltaTime);

	// 現在のシーンがシーン変更しようとしているか確認
	ChangeSceneInfo changeSceneInfo = currentScene->IsChangeScene();
	if (!changeSceneInfo.flag)return;

	// シーンを変更して初期化するか確認
	ChangeScene(changeSceneInfo.name);
	if (!changeSceneInfo.initNextSceneFlag)return;

	currentScene->Initialize();
}

void GE::SceneManager::Draw()
{
	if (!currentScene)return;

	currentScene->Draw();
}

void GE::SceneManager::LateDraw()
{
	if (!currentScene)return;

	currentScene->LateDraw();
}

GE::Scene* GE::SceneManager::AddScene(Scene* newScene)
{
	scenes.push_back(newScene);
	addScene = newScene;
	return addScene;
}

GE::Scene* GE::SceneManager::ChangeScene(const std::string& sceneName)
{
	Scene* returnScene = nullptr;
	beforeScene = currentScene;

	for (auto& scene : scenes)
	{
		if (scene->GetSceneName() == sceneName)
		{
			currentScene = returnScene = scene;
			break;
		}
	}

	return returnScene;
}

GE::Scene* GE::SceneManager::GetCurrentScene()
{
	return currentScene;
}

GE::Scene* GE::SceneManager::GetBeforeScene()
{
	return beforeScene;
}

GE::Scene* GE::SceneManager::GetScene(const std::string& sceneName)
{
	Scene* returnScene = nullptr;
	for (auto& scene : scenes)
	{
		if (scene->GetSceneName() == sceneName)
		{
			returnScene = scene;
			break;
		}
	}

	return returnScene;
}
