#include "..\..\..\Header\GameSystem\Component\Component.h"

GE::Component::Component()
	: gameObject(nullptr)
	, transform(nullptr)
	, enabled(true)
{
}

GE::GameObject* GE::Component::GetGameObject()
{
	return gameObject;
}

bool GE::Component::GetEnabled()
{
	return enabled;
}

void GE::Component::SetGameObject(GameObject* object)
{
	gameObject = object;
}

void GE::Component::SetTransform(Transform* transform)
{
	this->transform = transform;
}

void GE::Component::SetEnabled(bool flag)
{
	enabled = flag;
}
