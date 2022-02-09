#pragma once
#include "Vector3.h"
#include "Matrix4.h"
namespace GE
{
	namespace Math
	{
		struct Quaternion
		{
			float x;
			float y;
			float z;
			float w;


			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			Quaternion();

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="x">�l</param>
			/// <param name="y">�l</param>
			/// <param name="z">�l</param>
			/// <param name="w">�l</param>
			Quaternion(float x, float y, float z, float w = 1.0f);

			/// <summary>
			/// ���ƃA���O������N�H�[�^�j�I���𐶐�����R���X�g���N�^
			/// </summary>
			/// <param name="v">��</param>
			/// <param name="angle">���W�A��</param>
			Quaternion(const Vector3& v, float angle);

			/// <summary>
			/// �s�񂩂�N�H�[�^�j�I���𐶐�����R���X�g���N�^
			/// </summary>
			/// <param name="m">�s��</param>
			Quaternion(const Matrix4x4& m);

			/// <summary>
			/// ���K��
			/// </summary>
			/// <param name="q">�N�H�[�^�j�I��</param>
			/// <returns>���K���N�H�[�^�j�I��</returns>
			static Quaternion Normalize(const Quaternion& q);

			/// <summary>
			/// �����𐶐�����֐�
			/// </summary>
			/// <param name="q">�N�H�[�^�j�I��</param>
			/// <returns>����</returns>
			static Quaternion Conjugate(const Quaternion& q);

			/// <summary>
			/// �N�H�[�^�j�I�����m�̓��ς�Ԃ��֐�
			/// </summary>
			/// <param name="q1">�N�H�[�^�j�I��</param>
			/// <param name="q2">�N�H�[�^�j�I��</param>
			/// <returns>���ό���</returns>
			static float Dot(const Quaternion& q1, const Quaternion& q2);

			/// <summary>
			/// �N�H�[�^�j�I���̒�����Ԃ��֐�
			/// </summary>
			/// <param name="q">�N�H�[�^�j�I��</param>
			/// <returns>����</returns>
			static float Length(const Quaternion& q);

			/// <summary>
			/// 2�̃N�H�[�^�j�I�����狅�ʐ��`��Ԃ𐶐�����֐�
			/// </summary>
			/// <param name="q1">�N�H�[�^�j�I��</param>
			/// <param name="q2">�N�H�[�^�j�I��</param>
			/// <param name="t">�^�C�� 0 ~ 1</param>
			/// <returns>���ʐ��`���</returns>
			static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

			/// <summary>
			/// 2�̃N�H�[�^�j�I��������`��Ԃ𐶐�����֐�
			/// </summary>
			/// <param name="q1">�N�H�[�^�j�I��</param>
			/// <param name="q2">�N�H�[�^�j�I��</param>
			/// <param name="t">�^�C�� 0 ~ 1</param>
			/// <returns>���`���</returns>
			static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);

			/// <summary>
			/// �N�H�[�^�j�I�������]�s��𐶐�����֐�
			/// </summary>
			/// <param name="q"><�N�H�[�^�j�I��/param>
			/// <returns>��]�s��</returns>
			static Matrix4x4 Rotation(const Quaternion& q);

			/// <summary>
			/// �Z�b�g����Ă�N�H�[�^�j�I�������]�s����쐬����
			/// </summary>
			/// <returns>��]�s��</returns>
			Matrix4x4 Rotation();

			/// <summary>
			/// �N�H�[�^�j�I���̎���Ԃ��֐�
			/// </summary>
			/// <param name="q">�N�H�[�^�j�I��</param>
			/// <returns>���x�N�g��</returns>
			static Vector3 GetAxis(const Quaternion& q);

			Quaternion operator+();
			Quaternion operator-();
			Quaternion& operator+=(const Quaternion& q);
			Quaternion& operator-=(const Quaternion& q);
			Quaternion& operator*=(float s);
			Quaternion& operator/=(float s);
			Quaternion& operator*=(const Quaternion& q);
		};
		Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
		Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
		Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
		Quaternion operator*(const Quaternion& q, float s);
		Quaternion operator*(float s, const Quaternion& q);
		Quaternion operator/(const Quaternion& q, float s);
	}
}