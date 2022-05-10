#include "..\..\Header\Input\Mouse.h"
#include <stdio.h>

using Vector2 = GE::Math::Vector2;

GE::Mouse::Mouse()
	: beforeMouseState({})
	, currentMouseState({})
	, device(nullptr)
	, hwnd()
{
}

GE::Mouse::~Mouse()
{
}

void GE::Mouse::Create(IDirectInput8 * input, HWND hwnd)
{
	HRESULT result;
	result = input->CreateDevice(GUID_SysMouse, &device, NULL);
	result = device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	result = device->SetDataFormat(&c_dfDIMouse2);
	this->hwnd = hwnd;
}

void GE::Mouse::Initialize()
{
	mousePos = Vector2();
	mouseMove = Vector2();
}

void GE::Mouse::Update()
{
	beforeMouseState = currentMouseState;

	HRESULT result;

	result = device->GetDeviceState(sizeof(currentMouseState), &currentMouseState);

	if (result != S_OK) {
		device->Acquire();
		result = device->GetDeviceState(sizeof(currentMouseState), &currentMouseState);
	}
	POINT mousePoint{};
	GetCursorPos(&mousePoint);
	//ScreenToClient(hwnd, &mousePoint);
	float a = (mousePoint.y / 1080.0f) * 23 * 3;
	mouseMove.x = mousePos.x - mousePoint.x;
	mouseMove.y = mousePos.y - mousePoint.y;
	mousePos.x = (float)mousePoint.x;
	mousePos.y = (float)mousePoint.y;
}

bool GE::Mouse::GetCheckHitButtonAll()
{
	for (int i = 0; i < 3; i++)
	{
		if (currentMouseState.rgbButtons[i])return true;
	}
	return false;
}

bool GE::Mouse::GetCheckHitButton(MouseButtons button)
{
	return currentMouseState.rgbButtons[(int)button];
}

bool GE::Mouse::GetCheckPressTrigger(MouseButtons button)
{
	return (!beforeMouseState.rgbButtons[(int)button]) && currentMouseState.rgbButtons[(int)button];
}

bool GE::Mouse::GetCheckReleaseTrigger(MouseButtons button)
{
	return (beforeMouseState.rgbButtons[(int)button]) && !currentMouseState.rgbButtons[(int)button];
}

float GE::Mouse::GetWheelValue()
{
	return (float)currentMouseState.lZ;
}

Vector2 GE::Mouse::GetMouseMove()
{
	//return mouseMove;
	return { (float)-currentMouseState.lX,(float)-currentMouseState.lY };
}

Vector2 GE::Mouse::GetMousePos()
{
	POINT point = { (LONG)mousePos.x,(LONG)mousePos.y };
	//ScreenToClient(hwnd, &point);
	//float a = (point.y / 1080.0f) * 23 * 3;
	return {(float)point.x,(float)point.y/* + a*/};
}

Vector2 GE::Mouse::GetClientMousePos()
{
	POINT point = { (LONG)mousePos.x,(LONG)mousePos.y };
	ScreenToClient(hwnd, &point);
	return { (float)point.x,(float)point.y };
}

Vector2 GE::Mouse::GetScreenMousePos()
{
	POINT point = { (LONG)mousePos.x,(LONG)mousePos.y };
	ClientToScreen(hwnd, &point);
	return { (float)point.x,(float)point.y };
}

void GE::Mouse::SetMouseCursor(const Vector2& setPos)
{
	POINT point = { (LONG)setPos.x,(LONG)setPos.y };
	//ClientToScreen(hwnd, &point);
	SetCursorPos(point.x,point.y);
	mousePos = setPos;
}
