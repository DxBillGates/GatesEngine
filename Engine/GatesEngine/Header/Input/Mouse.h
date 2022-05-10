#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "MouseButtons.h"
#include "..\Util\Math\Vector2.h"
#include <dinput.h>

namespace GE
{
	class Mouse
	{
		using Vector2 = GE::Math::Vector2;
	private:
		HWND hwnd;
		IDirectInputDevice8* device;
		DIMOUSESTATE2 currentMouseState;
		DIMOUSESTATE2 beforeMouseState;
		Vector2 mousePos;
		Vector2 mouseMove;
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Mouse();
		~Mouse();

		/// <summary>
		/// �f�o�C�X�̐����֐�
		/// </summary>
		/// <param name="input">DInput�̐e�f�o�C�X�̃|�C���^</param>
		/// <param name="hwnd">�g�p���Ă���Window�̃n���h��</param>
		void Create(IDirectInput8* input,HWND hwnd);

		/// <summary>
		/// �������֐�
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V�֐�
		/// </summary>
		void Update();

		/// <summary>
		/// �}�E�X�̉�������̃L�[��������Ă��邩�m�F����֐�
		/// </summary>
		/// <returns>����</returns>
		bool GetCheckHitButtonAll();

		/// <summary>
		/// �w�肵���L�[��������Ă��邩�m�F����֐�
		/// </summary>
		/// <param name="button">�w��L�[</param>
		/// <returns>����</returns>
		bool GetCheckHitButton(MouseButtons button);

		/// <summary>
		/// �w�肵���L�[�����݂̃t���[���ŏ��߂ĉ����ꂽ���m�F����֐�
		/// </summary>
		/// <param name="button">�w��L�[</param>
		/// <returns>����</returns>
		bool GetCheckPressTrigger(MouseButtons button);

		/// <summary>
		/// �w�肵���L�[�����݂̃t���[���ŏ��߂ė����ꂽ���m�F����֐�
		/// </summary>
		/// <param name="button">�w��L�[</param>
		/// <returns>����</returns>
		bool GetCheckReleaseTrigger(MouseButtons button);

		/// <summary>
		/// �z�C�[���̏���Ԃ��֐�
		/// </summary>
		/// <returns>�z�C�[���̏��</returns>
		float GetWheelValue();
		
		/// <summary>
		/// �O�t���[������ǂꂾ���}�E�X�����������Ԃ��֐�
		/// </summary>
		/// <returns>�������s�N�Z����</returns>
		Vector2 GetMouseMove();

		/// <summary>
		/// �}�E�X�J�[�\�����ǂ̃s�N�Z���ɂ��邩��Ԃ��֐�
		/// </summary>
		/// <returns>�s�N�Z���ʒu</returns>
		Vector2 GetMousePos();

		Vector2 GetClientMousePos();

		Vector2 GetScreenMousePos();

		/// <summary>
		/// �}�E�X�J�[�\�����w�肵���s�N�Z���ɌŒ肷��֐�
		/// </summary>
		/// <param name="setPos">�w��s�N�Z��</param>
		void SetMouseCursor(const Vector2& setPos);
	};
}
