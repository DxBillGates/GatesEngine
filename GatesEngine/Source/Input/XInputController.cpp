#include "..\..\Header\Input\XInputController.h"
#include <math.h>
#pragma comment (lib, "xinput.lib")

int GE::XInputController::nextPadIndex = 0;

GE::XInputController::XInputController()
{
	ctrlState = {};
	mIndex = nextPadIndex;
	DWORD result = XInputGetState(mIndex, &ctrlState);

	// �e�`�F�b�N�{�^���̃Z�b�g
	for (int i = 0; i < 14; ++i)
	{
		int addValue = 0;
		if (i >= 10)addValue = 2;
		int padValue = (int)powf(2, (float)(i + addValue));
		oldKey[i].button = (XInputControllerButton)padValue;
		oldKey[i].flag = false;
	}

	// LT,RT�����ԍ���2�ׂ̂��悶��Ȃ��̂ŃZ�b�g
	oldKey[14].button = XInputControllerButton::XINPUT_Y;
	oldKey[14].button = XInputControllerButton::XINPUT_LT;
	oldKey[15].button = XInputControllerButton::XINPUT_RT;

	// ���Ɏg�p����Ă���p�b�h��F������ۂɎg���C���f�b�N�X��i�߂�
	++nextPadIndex;
}

GE::XInputController::~XInputController()
{
}

void GE::XInputController::Initialize()
{
	// �e�`�F�b�N�{�^���̃Z�b�g
	for (int i = 0; i < 14; ++i)
	{
		int addValue = 0;
		if (i >= 10)addValue = 2;
		int padValue = (int)powf(2, (float)(i + addValue));
		oldKey[i].button = (XInputControllerButton)padValue;
		oldKey[i].flag = false;
	}

	// LT,RT�����ԍ���2�ׂ̂��悶��Ȃ��̂ŃZ�b�g
	oldKey[14].button = XInputControllerButton::XINPUT_Y;
	oldKey[14].button = XInputControllerButton::XINPUT_LT;
	oldKey[15].button = XInputControllerButton::XINPUT_RT;
}

void GE::XInputController::Update()
{
	for (int i = 0; i < 14; ++i)
	{
		if (ctrlState.Gamepad.wButtons & (int)oldKey[i].button)
		{
			oldKey[i].flag = true;
		}
		else
		{
			oldKey[i].flag = false;
		}
	}
	if (ctrlState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)oldKey[14].flag = true;
	else oldKey[14].flag = false;
	if (ctrlState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)oldKey[15].flag = true;
	else oldKey[15].flag = false;
	//���̃t���[�����ł̃R���g���[���[�̏�Ԃ��擾
	DWORD result = XInputGetState(mIndex, &ctrlState);
}

bool GE::XInputController::CheckHitAllButton()
{
	for (auto& checkButton : oldKey)
	{
		if (checkButton.flag)
		{
			return true;
		}
	}
	return false;
}

bool GE::XInputController::CheckHitButton(XInputControllerButton button)
{
	for (auto& checkButton : oldKey)
	{
		if (checkButton.button == button)
		{
			return checkButton.flag;
		}
	}
	return false;
}

bool GE::XInputController::CheckHitButtonTrigger(XInputControllerButton button)
{
	// 2�ׂ̂���Ŕ���ł��Ȃ��L�[���画��
	if (oldKey[14].button == button && !oldKey[14].flag)
	{
		if (ctrlState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			oldKey[14].flag = true;
			return true;
		}
	}
	if (oldKey[15].button == button && !oldKey[15].flag)
	{
		if (ctrlState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			oldKey[15].flag = true;
			return true;
		}
	}

	// 2�ׂ̂���Őݒ肳�ꂽ�L�[�̔���
	for (int i = 0; i < 14; ++i)
	{
		if (oldKey[i].button != button)continue;
		if (oldKey[i].flag)break;

		if (ctrlState.Gamepad.wButtons & (int)button)
		{
			oldKey[i].flag = true;
			return true;
		}
	}
	return false;
}

float GE::XInputController::GetRStickX()
{
	return ctrlState.Gamepad.sThumbRX / 32767.0f;
}

float GE::XInputController::GetRStickY()
{
	return ctrlState.Gamepad.sThumbRY / 32767.0f;
}

float GE::XInputController::GetLStickX()
{
	return ctrlState.Gamepad.sThumbLX / 32767.0f;
}

float GE::XInputController::GetLStickY()
{
	return ctrlState.Gamepad.sThumbLY / 32767.0f;
}

GE::Math::Vector2 GE::XInputController::GetRStick()
{
	return Math::Vector2(GetRStickX(), GetRStickY());
}

GE::Math::Vector2 GE::XInputController::GetLStick()
{
	return Math::Vector2(GetLStickX(), GetLStickY());
}
