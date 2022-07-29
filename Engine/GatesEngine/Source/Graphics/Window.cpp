#include "..\..\Header\Graphics\Window.h"
#include "../../Header/GUI/GUIManager.h"

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (GE::GUIManager::WndProc(hwnd, msg, wparam, lparam))
	{
		return true;
	}

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		UINT width = LOWORD(lparam);
		UINT height = HIWORD(lparam);
		GE::Window::SetWindowSize({ (float)width,(float)height });

		auto graphicsDevice = GE::GUIManager::GetGraphicsDevice();
		if (graphicsDevice)
		{
			graphicsDevice->OnResizeWindow({ (float)width,(float)height });
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

GE::Math::Vector2 GE::Window::size = GE::Math::Vector2();

GE::Window::Window() 
	: hwnd(HWND())
	, wndClass(WNDCLASSEX())
	, msg(MSG())
	, pos(Vector2())
{
}

GE::Window::~Window()
{
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

//bool GE::Window::Create(const Vector2& windowSize, const std::string& title, WindowMode mode)
//{
//	// ƒEƒBƒ“ƒhƒE‚ÌÝ’è
//	wndClass.cbSize = sizeof(WNDCLASSEX);
//	wndClass.lpfnWndProc = (WNDPROC)WinProc;
//	wndClass.lpszClassName = title.c_str();
//	wndClass.hInstance = GetModuleHandle(nullptr);
//	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//
//	// Window‚Ì“o˜^
//	RegisterClassEx(&wndClass);
//
//	// Window‚Ì¶¬
//	RECT rect = { 0,0,(LONG)windowSize.x,(LONG)windowSize.y };
//
//	DWORD windowMode = 0;
//	switch (mode)
//	{
//	case GE::WindowMode::WINDOW:
//		windowMode = WS_OVERLAPPEDWINDOW;
//		break;
//	case GE::WindowMode::POP_UP:
//		windowMode = WS_POPUP;
//		break;
//	}
//
//	AdjustWindowRect(&rect, windowMode, false);
//	hwnd = CreateWindow(wndClass.lpszClassName,
//		wndClass.lpszClassName,
//		windowMode,
//		0,
//		0,
//		rect.right - rect.left,
//		rect.bottom - rect.top,
//		nullptr,
//		nullptr,
//		wndClass.hInstance,
//		nullptr);
//
//	this->size = windowSize;
//
//	if (hwnd == NULL)return false;
//	return true;
//}

bool GE::Window::Create(const WindowData& windowData)
{
	// ƒEƒBƒ“ƒhƒE‚ÌÝ’è
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WinProc;
	wndClass.lpszClassName = windowData.title.c_str();
	wndClass.hInstance = windowData.hInstance == NULL ? GetModuleHandle(NULL) : windowData.hInstance;
	wndClass.hCursor = windowData.cursorHandle == 0 ? nullptr : LoadCursor(wndClass.hInstance, MAKEINTRESOURCE(windowData.cursorHandle));
	wndClass.hIcon = windowData.iconHandle == 0 ? nullptr : LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(windowData.iconHandle));

	// Window‚Ì“o˜^
	RegisterClassEx(&wndClass);

	// Window‚Ì¶¬
	RECT rect = { 0,0,(LONG)windowData.windowSize.x,(LONG)windowData.windowSize.y };

	DWORD windowMode = 0;
	switch (windowData.windowMode)
	{
	case GE::WindowMode::WINDOW:
		windowMode = WS_OVERLAPPEDWINDOW;
		break;
	case GE::WindowMode::POP_UP:
		windowMode = WS_POPUP;
		break;
	}

	AdjustWindowRect(&rect, windowMode, false);
	hwnd = CreateWindow(wndClass.lpszClassName,
		wndClass.lpszClassName,
		windowMode,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		wndClass.hInstance,
		nullptr);

	this->size = windowData.windowSize;

	if (hwnd == NULL)return false;
	return true;
}

void GE::Window::PreviewWindow()
{
	ShowWindow(hwnd, SW_MAXIMIZE);
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

GE::Math::Vector2 GE::Window::GetWindowSize()
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

void GE::Window::SetWindowSize(const Vector2& setSize)
{
	size = setSize;
}
