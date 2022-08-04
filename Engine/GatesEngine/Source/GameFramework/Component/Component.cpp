#include "..\..\..\Header\GameFramework\Component\Component.h"
#include "..\..\..\Header\GUI\GUIManager.h"

#include <typeinfo>

GE::Component::Component()
	: gameObject(nullptr)
	, transform(nullptr)
	, enabled(true)
	, graphicsDevice(nullptr)
{
}

bool GE::Component::IsOpenTreeNodeGui()
{
	if (ImGui::TreeNode(typeid(*this).name()))
	{
		ImGui::Checkbox("Enabled", &enabled);
		return true;
	}


	return false;
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
