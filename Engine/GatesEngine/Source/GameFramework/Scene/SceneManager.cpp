#include "..\..\..\Header\GameFramework\Scene\SceneManager.h"

GE::SceneManager::SceneManager()
	: currentScene(nullptr)
	, beforeScene(nullptr)
	, addScene(nullptr)
{
}

GE::SceneManager::~SceneManager()
{
	for (auto& scene : scenes)
	{
		delete scene;
	}
}

void GE::SceneManager::Initialize()
{
	currentScene->Initialize();
}

void GE::SceneManager::Update(float deltaTime)
{
	if (!currentScene)return;

	currentScene->Update(deltaTime);

	// 現在のシーンがシーン変更しようとしているか確認
	ChangeSceneInfo& changeSceneInfo = currentScene->IsChangeScene();
	if (!changeSceneInfo.flag)return;

	// シーンを変更して初期化するか確認
	ChangeScene(changeSceneInfo.name);
	changeSceneInfo = ChangeSceneInfo();

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
	addScene->SetSceneInitializer(sceneInitializer);
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

GE::Scene* GE::SceneManager::GetAddScene()
{
	return addScene;
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

void GE::SceneManager::SetSceneInitializer(const SceneInitializer& initializer)
{
	sceneInitializer = initializer;
}
