#include "..\..\..\Header\GameFramework\Component\Component.h"

GE::Component::Component()
	: gameObject(nullptr)
	, transform(nullptr)
	, enabled(true)
	, graphicsDevice(nullptr)
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

void GE::Component::SetGraphicsDevice(IGraphicsDeviceDx12* graphicsDevice)
{
	this->graphicsDevice = graphicsDevice;
}
