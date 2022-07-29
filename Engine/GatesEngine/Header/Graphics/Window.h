#pragma once
#include "..\Util\Math\Vector2.h"
#include <string>
#include <Windows.h>

namespace GE
{
	enum class WindowMode
	{
		NONE,
		WINDOW,
		POP_UP,
	};

	struct WindowData
	{
		HINSTANCE hInstance;
		int cursorHandle;
		int iconHandle;
		
		Math::Vector2 windowSize;
		std::string title;
		WindowMode windowMode;

		WindowData()
			: hInstance(NULL)
			, cursorHandle(NULL)
			, iconHandle(NULL)
			, windowSize(Math::Vector2())
			, title("no title")
			, windowMode(WindowMode::WINDOW)
		{}

		WindowData(HINSTANCE hInstance, int cHandle, int iHandle, const Math::Vector2& size, const std::string& title, WindowMode mode)
			: hInstance(hInstance)
			, cursorHandle(cHandle)
			, iconHandle(iHandle)
			, windowSize(size)
			, title(title)
			, windowMode(mode)
		{}
	};

	class Window
	{
		using Vector2 = GE::Math::Vector2;
	private:
		HWND hwnd;
		WNDCLASSEX wndClass;
		MSG msg;
		static Vector2 size;
		Vector2 pos;
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Window();
		~Window();

		///// <summary>
		///// MainWindow生成関数
		///// </summary>
		///// <param name="windowSize">ウィンドウサイズ</param>
		///// <param name="title">ウィンドウタイトル</param>
		///// <returns>成否</returns>
		//bool Create(const Vector2& windowSize,const std::string& title,WindowMode mode = WindowMode::POP_UP);

		bool Create(const WindowData& windowData);

		/// <summary>
		/// MainWindow表示
		/// </summary>
		void PreviewWindow();

		/// <summary>
		/// Windowsへの応答などする関数
		/// </summary>
		/// <returns>成否</returns>
		bool ProcessMessage();

		/// <summary>
		/// MainWindowのハンドルを返す関数
		/// </summary>
		/// <returns>MainWindowのハンドル</returns>
		HWND GetHandle();

		/// <summary>
		/// MainWindowのインスタンスハンドルを返す関数
		/// </summary>
		/// <returns>MainWindowのインスタンスハンドル</returns>
		HINSTANCE GetHInstance();

		/// <summary>
		/// MainWindowのサイズを返す関数
		/// </summary>
		/// <returns>MainWindowのサイズ</returns>
		static Vector2 GetWindowSize();

		/// <summary>
		/// MainWindowのアスペクト比を返す関数
		/// </summary>
		/// <returns>MainWindowのアスペクト比</returns>
		float GetWindowAspect();

		/// <summary>
		/// MainWindowの左上の座標を設定する関数
		/// </summary>
		/// <param name="pos">位置(pixel)</param>
		void SetWindowPos(const Vector2& pos);

		/// <summary>
		/// MainWindowのタイトルを変更する関数
		/// </summary>
		/// <param name="changeTitle">設定する名前</param>
		void SetWindowTitle(const char* changeTitle);

		static void SetWindowSize(const Vector2& setSize);
	};
}
