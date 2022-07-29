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
		/// �R���X�g���N�^
		/// </summary>
		Window();
		~Window();

		///// <summary>
		///// MainWindow�����֐�
		///// </summary>
		///// <param name="windowSize">�E�B���h�E�T�C�Y</param>
		///// <param name="title">�E�B���h�E�^�C�g��</param>
		///// <returns>����</returns>
		//bool Create(const Vector2& windowSize,const std::string& title,WindowMode mode = WindowMode::POP_UP);

		bool Create(const WindowData& windowData);

		/// <summary>
		/// MainWindow�\��
		/// </summary>
		void PreviewWindow();

		/// <summary>
		/// Windows�ւ̉����Ȃǂ���֐�
		/// </summary>
		/// <returns>����</returns>
		bool ProcessMessage();

		/// <summary>
		/// MainWindow�̃n���h����Ԃ��֐�
		/// </summary>
		/// <returns>MainWindow�̃n���h��</returns>
		HWND GetHandle();

		/// <summary>
		/// MainWindow�̃C���X�^���X�n���h����Ԃ��֐�
		/// </summary>
		/// <returns>MainWindow�̃C���X�^���X�n���h��</returns>
		HINSTANCE GetHInstance();

		/// <summary>
		/// MainWindow�̃T�C�Y��Ԃ��֐�
		/// </summary>
		/// <returns>MainWindow�̃T�C�Y</returns>
		static Vector2 GetWindowSize();

		/// <summary>
		/// MainWindow�̃A�X�y�N�g���Ԃ��֐�
		/// </summary>
		/// <returns>MainWindow�̃A�X�y�N�g��</returns>
		float GetWindowAspect();

		/// <summary>
		/// MainWindow�̍���̍��W��ݒ肷��֐�
		/// </summary>
		/// <param name="pos">�ʒu(pixel)</param>
		void SetWindowPos(const Vector2& pos);

		/// <summary>
		/// MainWindow�̃^�C�g����ύX����֐�
		/// </summary>
		/// <param name="changeTitle">�ݒ肷�閼�O</param>
		void SetWindowTitle(const char* changeTitle);

		static void SetWindowSize(const Vector2& setSize);
	};
}
