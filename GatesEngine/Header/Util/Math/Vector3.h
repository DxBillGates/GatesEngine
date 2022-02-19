#pragma once
namespace GE
{
	namespace Math
	{
		struct Vector3
		{
			union
			{
				struct
				{
					float x;
					float y;
					float z;
				};
				float value[3];
			};

			/// <summary>
			/// �[���������R���X�g���N�^
			/// </summary>
			Vector3();

			/// <summary>
			/// x,y,z��xyz�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="xyz"></param>
			Vector3(float xyz);

			/// <summary>
			/// x,y,z��x,y,z�ŏ���������R���X�g���N�^
			/// </summary>
			/// <param name="x"></param>
			/// <param name="y"></param>
			/// <param name="z"></param>
			Vector3(float x, float y, float z);

			/// <summary>
			/// ���̃C���X�^���X�̒�����Ԃ��֐�
			/// </summary>
			/// <returns>����</returns>
			float Length() const;

			/// <summary>
			/// ���̃C���X�^���X�̐��K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <returns></returns>
			Vector3 Normalize();

			/// <summary>
			/// 2�̃x�N�g������Ȃ�x�N�g���̒�����Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>����</returns>
			static float Distance(const Vector3& v1, const Vector3& v2);

			/// <summary>
			/// ���K���x�N�g����Ԃ��֐�
			/// </summary>
			/// <param name="v">�x�N�g��</param>
			/// <returns>���K���x�N�g��</returns>
			static Vector3 Normalize(const Vector3& v);

			/// <summary>
			/// 2�̃x�N�g���̊O�ς�Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>�O��</returns>
			static Vector3 Cross(const Vector3& v1, const Vector3& v2);

			/// <summary>
			/// 2�̃x�N�g���̓��ς�Ԃ��֐�
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�x�N�g��</param>
			/// <returns>����</returns>
			static float Dot(const Vector3& v1, const Vector3& v2);

			/// <summary>
			/// 2�̃x�N�g���̐��`��Ԃ�Ԃ��֐�
			/// </summary>
			/// <param name="s">�X�^�[�g�ʒu</param>
			/// <param name="e">�I���ʒu</param>
			/// <param name="t">�^�C�� 0 ~ 1</param>
			/// <returns>���`��Ԍ���</returns>
			static Vector3 Lerp(const Vector3& s, const Vector3& e, float t);

			/// <summary>
			/// std::max()��3�����x�N�g����
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�ő�x�N�g��</param>
			/// <returns>�x�N�g��</returns>
			static Vector3 Max(const Vector3& v1, const Vector3& v2);

			/// <summary>
			/// std::min()��3�����x�N�g����
			/// </summary>
			/// <param name="v1">�x�N�g��</param>
			/// <param name="v2">�ŏ��x�N�g��</param>
			/// <returns>�x�N�g��</returns>
			static Vector3 Min(const Vector3& v1, const Vector3& v2);

			Vector3 operator+();
			Vector3 operator-();
			Vector3& operator+=(const Vector3& v);
			Vector3& operator-=(const Vector3& v);
			Vector3& operator*=(float s);
			Vector3& operator*=(const Vector3& v);
			Vector3& operator/=(float s);
		};
		const Vector3 operator+(const Vector3& v1, const Vector3& v2);
		const Vector3 operator-(const Vector3& v1, const Vector3& v2);
		const Vector3 operator*(const Vector3& v, float s);
		const Vector3 operator*(float s, const Vector3& v);
		const Vector3 operator*(const Vector3& v1, const Vector3& v2);
		const Vector3 operator/(const Vector3& v, float s);
		const Vector3 operator/(float s, const Vector3& v);
	}
}
