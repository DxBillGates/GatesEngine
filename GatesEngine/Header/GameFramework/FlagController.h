#pragma once

namespace GE
{
	/// <summary>
	/// �Q�[�����Ŏg�p����t���O���g���₷�������N���X
	/// </summary>
	class FlagController
	{
	protected:
		// �t���O
		bool flag;
		// �t���O���I���ɂȂ��Ă���̌o�ߎ���
		float elapsedTime;
		// �O�t���[���̌o�ߎ���
		float preElapsedTime;

		// ����^�C��
		float PROPERTY_MAX_TIME;
	public:
		FlagController();
		virtual ~FlagController();
		virtual void Initialize();
		virtual void Update(float deltaTime);

		// �o�ߎ��Ԃ�1�𒴂����t���[���̂�true��Ԃ�
		bool GetOverTimeTrigger();
		bool GetFlag();
		float GetTime();
		void SetFlag(bool setFlag);
		void SetTime(float setValue);
		void SetMaxTimeProperty(const float value);

		bool IsOverTime(float value = 1);
		bool IsUnderTime(float value = 1);
	};
}