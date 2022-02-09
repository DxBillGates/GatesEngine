#pragma once
#include "GameObject.h"
#include <vector>

namespace GE
{
	class GameObjectManager
	{
	private:
		std::vector<GameObject*> gameObjects;
	public:
		GameObjectManager();
		~GameObjectManager();
		void Awake();
		void Start();
		void Update(float deltaTime);
		void Draw();
		void LateDraw();

		GameObject* AddGameObject(GameObject* newGameObject);
		GameObject* FindGameObject(const std::string& name);
		GameObject* FindGameObjectWithTag(const std::string& name, const std::string& tag);
	};
}