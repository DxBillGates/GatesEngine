#include "..\..\..\Header\GameFramework\GameObject\GameObjectManager.h"

GE::GameObjectManager::GameObjectManager()
{
}

GE::GameObjectManager::~GameObjectManager()
{
	for (auto& object : gameObjects)
	{
		delete object;
	}
	gameObjects.clear();
}

void GE::GameObjectManager::Awake()
{
	for (auto& object : gameObjects)
	{
		object->Awake();
	}
}

void GE::GameObjectManager::Start()
{
	for (auto& object : gameObjects)
	{
		object->Start();
	}
}

void GE::GameObjectManager::Update(float deltaTime)
{
	for (auto& object : gameObjects)
	{
		object->Update(deltaTime);

		// Hierarchy‚ÌGameObject‚ð‘I‘ð‚µ‚½‚çInspector‚É‚»‚ÌGameObject‚ð“o˜^
		if (hierarchyGui.OnGui(object))
		{
			inspectorGui.SetCurrentSelectGameObject(object);
		}
	}
	inspectorGui.OnGui();
}

void GE::GameObjectManager::Draw()
{
	for (auto& object : gameObjects)
	{
		object->Draw();
	}
}

void GE::GameObjectManager::LateDraw()
{
	for (auto& object : gameObjects)
	{
		object->LateDraw();
	}
}

GE::GameObject* GE::GameObjectManager::AddGameObject(GameObject* newGameObject)
{
	gameObjects.push_back(newGameObject);
	return newGameObject;
}

GE::GameObject* GE::GameObjectManager::FindGameObject(const std::string& name)
{
	GameObject* returnObject = nullptr;
	for (auto& object : gameObjects)
	{
		if (object->GetName() != name)continue;

		returnObject = object;
		break;
	}
	return returnObject;
}

GE::GameObject* GE::GameObjectManager::FindGameObjectWithTag(const std::string& name, const std::string& tag)
{
	GameObject* returnObject = nullptr;
	for (auto& object : gameObjects)
	{
		if (object->GetName() != name)continue;
		if (object->GetTag() != tag)continue;

		returnObject = object;
		break;
	}
	return returnObject;
}
