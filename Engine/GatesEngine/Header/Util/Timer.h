#pragma once
#include <Windows.h>
namespace GE
{
	namespace Utility
	{
		class Timer
		{
		private:
			bool isShow;
			double fps;
			double frameTime;
			LARGE_INTEGER timeStart;
			LARGE_INTEGER timeEnd;
			LARGE_INTEGER timeFreq;
			LARGE_INTEGER startBuffer;
			LARGE_INTEGER endBuffer;
			float setFrameRate;
			bool isSetFrameRate;
			float elapsedApplicationTime;
		public:
			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			Timer();

			/// <summary>
			/// ���z�f�X�g���N�^
			/// </summary>
			virtual ~Timer();

			/// <summary>
			/// FPS���f�o�b�O�E�B���h�E�ɕ\�������邩�ݒ肷��֐�
			/// </summary>
			/// <param name="b">����</param>
			void SetIsShow(bool b);

			/// <summary>
			/// �O�t���[���Ɏg�p���ꂽ���Ԃ�ms�ŕԂ��֐�
			/// </summary>
			/// <returns>�O�t���[���Ɏg�p���ꂽ����(ms)</returns>
			float GetElapsedTime();

			/// <summary>
			/// �A�v���P�[�V�������n�܂��Ă���̎���(s)��Ԃ��֐�
			/// </summary>
			/// <returns>�A�v���P�[�V�������n�܂��Ă���̎���(s)</returns>
			float GetElapsedApplicationTime();

			/// <summary>
			/// �t���[���̎��Ԃ�}�邽�߂̃X�^�[�g�֐�
			/// </summary>
			void Start();

			/// <summary>
			/// �t���[���̎��Ԃ�}�邽�߂̃G���h�֐�
			/// </summary>
			/// <param name="isShow">ms��\�����邩</param>
			/// <param name="addComment">�ǉ��R�����g</param>
			void End(bool isShow = true, const char* addComment = "");

			/// <summary>
			/// �w�肳��Ă���FPS�ȏ�o�Ȃ��悤�ɂ���֐�
			/// </summary>
			/// <returns>����</returns>
			bool Update();

			/// <summary>
			/// �A�v���P�[�V�����̍ő�t���[�����[�g��ݒ肷��֐�
			/// </summary>
			/// <param name="value"></param>
			void SetFrameRate(float value);
		};
	}
}
