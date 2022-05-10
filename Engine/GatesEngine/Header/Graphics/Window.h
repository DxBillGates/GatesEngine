#pragma once
#include "..\Util\Math\Vector2.h"
#include <string>
#include <Windows.h>

namespace GE
{
	class Window
	{
		using Vector2 = GE::Math::Vector2;
	private:
		HWND hwnd;
		WNDCLASSEX wndClass;
		MSG msg;
		Vector2 size;
		Vector2 pos;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Window();
		~Window();

		/// <summary>
		/// MainWindow�����֐�
		/// </summary>
		/// <param name="windowSize">�E�B���h�E�T�C�Y</param>
		/// <param name="title">�E�B���h�E�^�C�g��</param>
		/// <returns>����</returns>
		bool Create(const Vector2& windowSize,const std::string& title);

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
		Vector2 GetWindowSize();

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
	};
}
