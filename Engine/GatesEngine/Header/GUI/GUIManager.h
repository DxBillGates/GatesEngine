#pragma once
#include "../../External/imgui/imgui.h"
#include "../../External/imgui/imgui_impl_win32.h"
#include "../../External/imgui/imgui_impl_dx12.h"

#include "../../Header/Graphics/IGraphicsDeviceDx12.h"
#include "../../Header/Graphics/Window.h"

namespace GE
{
	class GUIManager
	{
	private:
		static bool isInitialize;
		static IGraphicsDeviceDx12* pGraphicsDevice;
	public:
		static void Initialize(HWND hwnd, IGraphicsDeviceDx12* graphicsDevice);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void StartFrame(bool isShowDemo = false);
		static void EndFrame();

		static IGraphicsDeviceDx12* GetGraphicsDevice();
		static void Finalize();
	};
}
