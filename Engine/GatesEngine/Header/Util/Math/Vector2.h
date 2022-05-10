#pragma once
namespace GE
{
	namespace Math
	{
		struct Vector2
		{
			float x;
			float y;

			/// <summary>
			/// �[���������̃R���X�g���N�^
			/// </summary>
			Vector2();

			/// <summary>
			/// x,y��xy�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="xy">�l</param>
			Vector2(float xy);

			/// <summary>
			/// x,y��x,y�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="x">�l</param>
			/// <param name="y">�l</param>
			Vector2(float x, float y);


			/// <summary>
			/// ���̃C���X�^���X�̒�����Ԃ��֐�
			/// </summary>
			/// <returns>����</returns>
			float Length();

			/// <summary>
			/// ���̃C���X�^���X�̐��K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <returns>���K���x�N�g��</returns>
			Vector2 Normalize();

			/// <summary>
			/// 2�̃x�N�g������Ȃ�x�N�g���̒�����Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>����</returns>
			static float Distance(const Vector2& v1, const Vector2& v2);

			/// <summary>
			/// ���K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <param name="v">�x�N�g��</param>
			/// <returns>���K���x�N�g��</returns>
			static Vector2 Normalize(const Vector2& v);

			/// <summary>
			/// 2�̃x�N�g���̊O�ς�Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>�O��</returns>
			static float Cross(const Vector2& v1, const Vector2& v2);

			/// <summary>
			/// 2�̃x�N�g���̓��ς�Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>����</returns>
			static float Dot(const Vector2& v1, const Vector2& v2);

			/// <summary>
			/// 2�̃x�N�g���̐��`��Ԃ�Ԃ��֐�
			/// </summary>
			/// <param name="s">�X�^�[�g�ʒu</param>
			/// <param name="e">�I���ʒu</param>
			/// <param name="t">�^�C�� 0 ~ 1</param>
			/// <returns>���`��Ԍ���</returns>
			static Vector2 Lerp(const Vector2& s, const Vector2& e, float t);

			Vector2 operator+();
			Vector2 operator-();
			Vector2& operator+=(const Vector2& v);
			Vector2& operator-=(const Vector2& v);
			Vector2& operator*=(float s);
			Vector2& operator/=(float s);
		};
		const Vector2 operator+(const Vector2& v1, const Vector2& v2);
		const Vector2 operator-(const Vector2& v1, const Vector2& v2);
		const Vector2 operator*(const Vector2& v, float s);
		const Vector2 operator*(float s, const Vector2& v);
		const Vector2 operator/(const Vector2& v, float s);
		const Vector2 operator/(float s, const Vector2& v);
	}
}