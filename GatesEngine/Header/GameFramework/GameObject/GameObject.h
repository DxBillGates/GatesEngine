#pragma once
#include "..\..\Util\Math\Transform.h"
#include "..\..\Graphics\IGraphicsDeviceDx12.h"

#include <vector>
#include <string>

namespace GE
{
	class Component;
	class GameObject
	{
	private:
		GameObject* parent;
		std::vector<Component*> components;
		Transform transform;
		bool enabled;
		std::string name;
		std::string tag;

		static IGraphicsDeviceDx12* graphicsDevice;
	public:
		GameObject(const std::string& name = "unknown", const std::string& tag = "none");
		~GameObject();
		void Awake();
		void Start();
		void Update(float deltaTime);
		void Draw();
		void LateDraw();

		Transform* GetTransform();
		bool IsEnabled();
		const std::string& GetName();
		const std::string& GetTag();

		void SetParent(GameObject* object);
		void SetName(const std::string& name);
		void SetTag(const std::string & tag);
		void SetEnabled(bool flag);
		static void SetGraphicsDevice(IGraphicsDeviceDx12* gDevice);
		static bool IsSetGraphicsDevice();

		template<typename T>
		T* AddComponent();
	};


	template<typename T>
	inline T* GameObject::AddComponent()
	{
		T* t = new T();
		//Componentクラスから派生したものかチェック
		Component* pComponent = static_cast<Component*>(t);
		if (pComponent != nullptr)
		{
			components.push_back(pComponent);
			return t;
		}
		return nullptr;
	}
}