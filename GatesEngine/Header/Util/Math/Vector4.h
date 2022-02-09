#pragma once
#include "Vector3.h"
namespace GE
{
	namespace Math
	{
		struct Vector4
		{
			float x, y, z, w;

			/// <summary>
			/// �[���������R���X�g���N�^
			/// </summary>
			Vector4();

			/// <summary>
			/// x,y,z,w��xyzw�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="xyzw">�l</param>
			Vector4(float xyzw);

			/// <summary>
			/// x,y,z,w��x,y,z,w�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="x">�l</param>
			/// <param name="y">�l</param>
			/// <param name="z">�l</param>
			/// <param name="w">�l</param>
			Vector4(float x, float y, float z, float w);

			/// <summary>
			/// x,y,z���x�N�g���ŁAw���[������������R���X�g���N�^
			/// </summary>
			/// <param name="v">�x�N�g��</param>
			Vector4(const Vector3& v);

			/// <summary>
			/// ���̃C���X�^���X�̒�����Ԃ��֐�
			/// </summary>
			/// <returns>����</returns>
			float Length();

			/// <summary>
			/// ���̃C���X�^���X�̐��K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <returns>���K���x�N�g��</returns>
			Vector4 Normalize();

			/// <summary>
			/// ���K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <param name="v">�x�N�g��</param>
			/// <returns>���K���x�N�g��</returns>
			static Vector4 Normalize(const Vector4& v);

			Vector4 operator+();
			Vector4 operator-();
			Vector4& operator+=(const Vector4& v);
			Vector4& operator-=(const Vector4& v);
			Vector4& operator*=(float s);
			Vector4& operator/=(float s);
		};
		const Vector4 operator+(const Vector4& v1, const Vector4& v2);
		const Vector4 operator-(const Vector4& v1, const Vector4& v2);
		const Vector4 operator*(const Vector4& v, float s);
		const Vector4 operator*(float s, const Vector4& v);
		const Vector4 operator/(const Vector4& v, float s);
		const Vector4 operator/(float s, const Vector4& v);
	}
}
