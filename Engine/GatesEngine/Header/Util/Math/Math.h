#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Easing.h"

namespace GE
{
	namespace Math
	{
		struct GaussFilterData
		{
			GE::Math::Vector4 data[16];
		};

		const float PI = 3.14159265f;

		/// <summary>
		/// �x���@����ʓx�@�ɕϊ�����֐�
		/// </summary>
		/// <param name="value">�x��</param>
		/// <returns>���W�A��</returns>
		float ConvertToRadian(float value);

		/// <summary>
		/// ���`��Ԋ֐�
		/// </summary>
		/// <param name="s">�X�^�[�g</param>
		/// <param name="e">�G���h</param>
		/// <param name="t">�^�C��</param>
		/// <returns>���`��Ԃ̒l</returns>
		float Lerp(float s, float e, float t);

		// �K�E�V�A���t�B���^�̏d�݂��v�Z����֐�
		float GaussFilter(const GE::Math::Vector2& pos, float value);
		// �Q�ƃs�N�Z���ւ̏��ƃK�E�V�A���t�B���^�̏d�݂��v�Z���ăZ�b�g����֐�
		void SetGaussFilterData(const GE::Math::Vector2& size, GE::Math::Vector2& dir, float gaussValue, GaussFilterData* data, int dataSize);
	}
}
