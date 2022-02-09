#include "..\..\Header\Input\Keyboard.h"

GE::Keyboard::Keyboard()
{
	memset(&currentKeys, 0, sizeof(currentKeys));
	memset(&beforeKeys, 0, sizeof(beforeKeys));
}

GE::Keyboard::~Keyboard()
{
	device->Release();
}

void GE::Keyboard::Create(IDirectInput8 * input, HWND hwnd)
{
	HRESULT result;
	result = input->CreateDevice(GUID_SysKeyboard, &device, NULL);
	result = device->SetDataFormat(&c_dfDIKeyboard);
	result = device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE/* | DISCL_NOWINKEY*/);
}

void GE::Keyboard::Initialize()
{
	memset(&currentKeys, 0, sizeof(currentKeys));
	memset(&beforeKeys, 0, sizeof(beforeKeys));
}

void GE::Keyboard::Update()
{
	device->Acquire();
	for (int i = 0; i < 256; ++i)
	{
		beforeKeys[i] = currentKeys[i];
	}
	device->GetDeviceState(sizeof(currentKeys), &currentKeys);
}

bool GE::Keyboard::CheckPressTrigger(Keys key)
{
	if (key == Keys::NONE)return false;
	bool flag = false;
	int index = (int)key;
	if (!(beforeKeys[index] & 0x80) && (currentKeys[index] & 0x80))
	{
		flag = true;
	}
	return flag;
}

bool GE::Keyboard::CheckReleaseTrigger(Keys key)
{
	if (key == Keys::NONE)return false;
	bool flag = false;
	int index = (int)key;
	if ((beforeKeys[index] & 0x80) && !(currentKeys[index] & 0x80))
	{
		flag = true;
	}
	return flag;
}

bool GE::Keyboard::CheckHitKey(Keys key)
{
	if (key == Keys::NONE)return false;
	bool flag = false;
	int index = (int)key;
	if ((currentKeys[index] & 0x80))
	{
		flag = true;
	}
	return flag;
}

bool GE::Keyboard::CheckHitKeyAll()
{
	bool flag = false;
	for (int i = 0; i < 256; ++i)
	{
		if (currentKeys[i])
		{
			flag = true;
			break;
		}
	}
	return flag;
}
