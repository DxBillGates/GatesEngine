#include "..\..\..\Header\GameFramework\GameObject\GameObject.h"
#include "..\..\..\Header\GameFramework\Component\Component.h"
#include "..\..\..\Header\Util\Utility.h"

GE::IGraphicsDeviceDx12* GE::GameObject::graphicsDevice = nullptr;

GE::GameObject::GameObject(const std::string& name, const std::string& tag)
	: parent(nullptr)
	, transform(Transform())
	, enabled(true)
	, name(name)
	, tag(tag)
{
}

GE::GameObject::~GameObject()
{
	for (auto& component : components)
	{
		delete component;
	}
	components.clear();
}

void GE::GameObject::Awake()
{
	if (!IsSetGraphicsDevice())Utility::Printf("GameObject : IGraphicsDeviceがセットされていません\n");
	for (auto& component : components)
	{
		component->SetGameObject(this);
		component->SetTransform(&transform);
		component->SetGraphicsDevice(graphicsDevice);
		component->Awake();
	}
}

void GE::GameObject::Start()
{
	for (auto& component : components)
	{
		component->Start();
	}
}

void GE::GameObject::Update(float deltaTime)
{
	if (!enabled)return;

	for (auto& component : components)
	{
		component->Update(deltaTime);
	}
}

void GE::GameObject::Draw()
{
	for (auto& component : components)
	{
		component->Draw();
	}
}

void GE::GameObject::LateDraw()
{
	for (auto& component : components)
	{
		component->LateDraw();
	}
}

void GE::GameObject::OnCollision(GameObject* other)
{
	for (auto& component : components)
	{
		component->OnCollision(other);
	}
}

void GE::GameObject::OnCollision(Collider* hitCollider)
{
	for (auto& component : components)
	{
		component->OnCollision(hitCollider);
	}
}

GE::Transform* GE::GameObject::GetTransform()
{
	return &transform;
}

bool GE::GameObject::IsEnabled()
{
	return enabled;
}

const std::string& GE::GameObject::GetName()
{
	return name;
}

const std::string& GE::GameObject::GetTag()
{
	return tag;
}

void GE::GameObject::SetParent(GameObject* object)
{
	parent = object;
}

void GE::GameObject::SetName(const std::string& name)
{
	this->name = name;
}

void GE::GameObject::SetTag(const std::string& tag)
{
	this->tag = tag;
}

void GE::GameObject::SetEnabled(bool flag)
{
	enabled = flag;
}

void GE::GameObject::SetGraphicsDevice(IGraphicsDeviceDx12* gDevice)
{
	graphicsDevice = gDevice;
}

bool GE::GameObject::IsSetGraphicsDevice()
{
	return (graphicsDevice) ? true : false;
}
