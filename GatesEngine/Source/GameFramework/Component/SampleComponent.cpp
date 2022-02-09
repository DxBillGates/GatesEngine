#include "..\..\..\Header\GameFramework\Component\SampleComponent.h"
#include "..\..\..\Header\Util\Utility.h"

GE::SampleComponent::SampleComponent()
	: inputDevice(nullptr)
{
}

GE::SampleComponent::~SampleComponent()
{
}

void GE::SampleComponent::Awake()
{
	Utility::Printf("SampleComponent Awake()\n");
}

void GE::SampleComponent::Start()
{
	Utility::Printf("SampleComponent Start()\n");
	inputDevice = InputDevice::GetInstance();
}

void GE::SampleComponent::Update(float deltaTime)
{
	if (inputDevice->GetKeyboard()->CheckPressTrigger(Keys::SPACE))
	{
		Utility::Printf("SampleComponent Update() : press space key\n");
	}

	if (inputDevice->GetMouse()->GetCheckPressTrigger(MouseButtons::LEFT_CLICK))
	{
		Utility::Printf("SampleComponent Update() : press left click\n");
	}

	if (inputDevice->GetXCtrler()->CheckHitButtonTrigger(XInputControllerButton::XINPUT_B))
	{
		Utility::Printf("SampleComponent Update() : press b button\n");
	}
}

void GE::SampleComponent::Draw()
{
}
