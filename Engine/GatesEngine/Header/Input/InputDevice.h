#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "Keyboard.h"
#include "Mouse.h"
#include "XInputController.h"

#include <dinput.h>
#include <Xinput.h>

namespace GE
{
	//�L�[�{�[�h��}�E�X�Ƃ��������͊֌W���Ǘ�����V���O���g���N���X
	class InputDevice
	{
	private:
		HWND hwnd;
		IDirectInput8* dInput;
		Keyboard keyboard;
		Mouse mouse;
		XInputController xctrler;
		//DCtrler dctrler;
	public:
		/// <summary>
		/// �V���O���g���̃|�C���^��Ԃ��֐�
		/// </summary>
		/// <returns>�V���O���g���̃|�C���^</returns>
		static InputDevice* GetInstance();

		/// <summary>
		/// �e�����o�𐶐�����֐�
		/// </summary>
		/// <param name="hwnd">�g�p���Ă���Window�̃n���h��</param>
		/// <param name="hInstance">�g�p���Ă���Window�̃C���X�^���X�n���h��</param>
		void Create(HWND hwnd, HINSTANCE hInstance);

		/// <summary>
		/// �e�f�o�C�X�̏�����������֐�
		/// </summary>
		void Initialize();

		/// <summary>
		/// �e�f�o�C�X�̍X�V������֐�
		/// </summary>
		void Update();

		/// <summary>
		/// �L�[�{�[�h�̏���ێ����Ă���N���X�̃|�C���^��Ԃ��֐�
		/// </summary>
		/// <returns>�L�[�{�[�h�̏���ێ����Ă���N���X�̃|�C���^</returns>
		Keyboard* GetKeyboard();

		/// <summary>
		/// �}�E�X����ێ����Ă���N���X�̃|�C���^��Ԃ��֐�
		/// </summary>
		/// <returns>�}�E�X����ێ����Ă���N���X�̃|�C���^</returns>
		Mouse* GetMouse();

		/// <summary>
		/// �ڑ�����Ă���XInputController��Ԃ�
		/// </summary>
		/// <returns></returns>
		XInputController* GetXCtrler();

		/// <summary>
		/// �g�p���Ă���Window�Ƀt�H�[�J�X�������Ă��邩�m�F����֐�
		/// </summary>
		/// <returns>����</returns>
		bool GetIsFocus();

		//XCtrler* GetXInputCtrler();
		//DCtrler* GetDInputCtrler();
	protected:
		InputDevice();
		InputDevice(const InputDevice&) = delete;
		~InputDevice() = default;
		InputDevice& operator=(const InputDevice&) = delete;
	};
}