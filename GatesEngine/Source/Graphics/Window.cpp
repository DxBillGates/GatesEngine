#include "..\..\Header\Graphics\Window.h"

using Vector2 = GE::Math::Vector2;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

GE::Window::Window() :hwnd(HWND()), wndClass(WNDCLASSEX()), msg(MSG()), size(Vector2())
{
}

GE::Window::~Window()
{
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

bool GE::Window::Create(const Vector2& windowSize,const std::string& title)
{
	// ƒEƒBƒ“ƒhƒE‚ÌÝ’è
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WinProc;
	wndClass.lpszClassName = title.c_str();
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	// Window‚Ì“o˜^
	RegisterClassEx(&wndClass);

	// Window‚Ì¶¬
	RECT rect = { 0,0,(LONG)windowSize.x,(LONG)windowSize.y };
	AdjustWindowRect(&rect, WS_POPUP, false);
	hwnd = CreateWindow(wndClass.lpszClassName,
		wndClass.lpszClassName,
		WS_POPUP,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		wndClass.hInstance,
		nullptr);

	this->size = windowSize;

	if (hwnd == NULL)return false;
	return true;
}

void GE::Window::PreviewWindow()
{
	ShowWindow(hwnd, SW_SHOW);
}

bool GE::Window::Window::ProcessMessage()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		return false;
	}
	return true;
}

HWND GE::Window::GetHandle()
{
	return hwnd;
}

HINSTANCE GE::Window::GetHInstance()
{
	return wndClass.hInstance;
}

Vector2 GE::Window::GetWindowSize()
{
	return size;
}

float GE::Window::GetWindowAspect()
{
	return size.x / size.y;
}

void GE::Window::SetWindowPos(const Vector2& pos)
{
	MoveWindow(hwnd, (int)pos.x, (int)pos.y, (int)size.x, (int)size.y, TRUE);
	this->pos = pos;
}

void GE::Window::SetWindowTitle(const char* changeTitle)
{
	SetWindowText(hwnd, changeTitle);
}