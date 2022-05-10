#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "Keys.h"
#include <dinput.h>

namespace GE
{
	class Keyboard
	{
	private:
		IDirectInputDevice8* device;
		BYTE currentKeys[256];
		BYTE beforeKeys[256];
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Keyboard();
		~Keyboard();

		/// <summary>
		/// �f�o�C�X�𐶐�����֐�
		/// </summary>
		/// <param name="input">DInput�̐e�f�o�C�X�̃|�C���^</param>
		/// <param name="hwnd">�g�p���Ă���Window�̃n���h��</param>
		void Create(IDirectInput8* input, HWND hwnd);

		/// <summary>
		/// �������֐�
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V�֐�
		/// </summary>
		void Update();

		/// <summary>
		/// �w�肵���L�[�����݂̃t���[���ŏ��߂ĉ����ꂽ���m�F����֐�
		/// </summary>
		/// <param name="key">�w��L�[</param>
		/// <returns>����</returns>
		bool CheckPressTrigger(Keys key);

		/// <summary>
		/// �w�肵���L�[�����݂̃t���[���ŏ��߂ė����ꂽ���m�F����֐�
		/// </summary>
		/// <param name="key">�w��L�[</param>
		/// <returns>����</returns>
		bool CheckReleaseTrigger(Keys key);

		/// <summary>
		/// �w�肵���L�[��������Ă��邩�m�F����֐�
		/// </summary>
		/// <param name="key">�w��L�[</param>
		/// <returns>����</returns>
		bool CheckHitKey(Keys key);

		/// <summary>
		/// ��������̃L�[��������Ă��邩�m�F����֐�
		/// </summary>
		/// <returns>����</returns>
		bool CheckHitKeyAll();
	};
}

