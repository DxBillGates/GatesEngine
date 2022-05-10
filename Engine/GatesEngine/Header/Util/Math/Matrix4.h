#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Axis.h"
namespace GE
{
	namespace Math
	{
		//4*4�s��
		struct Matrix4x4
		{
			union
			{
				struct
				{
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};
				float m[4][4];
			};

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			Matrix4x4();
			/// <summary>
			/// �������R���X�g���N�^
			/// </summary>
			/// <param name="m00">m00�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m01">m01�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m02">m02�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m03">m03�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m10">m10�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m11">m11�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m12">m12�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m13">m13�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m20">m20�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m21">m21�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m22">m22�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m23">m23�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m30">m30�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m31">m31�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m32">m32�ɑ΂��ăZ�b�g����l</param>
			/// <param name="m33">m33�ɑ΂��ăZ�b�g����l</param>
			Matrix4x4
			(
				float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33
			);

			/// <summary>
			/// �P�ʍs���Ԃ��֐�
			/// </summary>
			/// <returns>�P�ʍs��</returns>
			static Matrix4x4 Identity();

			/// <summary>
			/// �s��̊e����Ԃ��֐�
			/// </summary>
			/// <param name="m">�s��</param>
			/// <returns>�e��</returns>
			static Axis GetAxis(const Matrix4x4& m);

			/// <summary>
			/// �傫���s��𐶐�����֐�
			/// </summary>
			/// <param name="v">�傫��</param>
			/// <returns>�傫���s��</returns>
			static Matrix4x4 Scale(const Vector3& v);

			/// <summary>
			/// X���ł̉�]�s��𐶐�����֐�
			/// </summary>
			/// <param name="angle">���W�A��</param>
			/// <returns>X����]�s��</returns>
			static Matrix4x4 RotationX(float angle);

			/// <summary>
			/// Y���ł̉�]�s��𐶐�����֐�
			/// </summary>
			/// <param name="angle">���W�A��</param>
			/// <returns>Y����]�s��</returns>
			static Matrix4x4 RotationY(float angle);

			/// <summary>
			/// Z���ł̉�]�s��𐶐�����֐�
			/// </summary>
			/// <param name="angle">���W�A��</param>
			/// <returns>Z����]�s��</returns>
			static Matrix4x4 RotationZ(float angle);

			/// <summary>
			/// ZXY�̏��ŉ�]�s��𐶐�����֐�
			/// </summary>
			/// <param name="angles">���W�A���x�N�g��</param>
			/// <returns>ZXY��]�s��</returns>
			static Matrix4x4 RotationZXY(const Vector3& angles);

			/// <summary>
			/// ���s�ړ��s��𐶐�����֐�
			/// </summary>
			/// <param name="v">�ʒu</param>
			/// <returns>���s�ړ��s��</returns>
			static Matrix4x4 Translate(const Vector3& v);

			/// <summary>
			/// �x�N�g���ƍs�񂩂�V���ȍs��𐶐�����֐�
			/// </summary>
			/// <param name="v">�x�N�g��</param>
			/// <param name="m">�s��</param>
			/// <returns>�������ꂽ�s��</returns>
			static Vector3 Transform(const Vector3& v, const Matrix4x4& m);

			/// <summary>
			/// �s��̓]�u��Ԃ��֐�
			/// </summary>
			/// <param name="m">�s��</param>
			/// <returns>�]�u�s��</returns>
			static Matrix4x4 Transpose(const Matrix4x4& m);

			/// <summary>
			/// �t�s���Ԃ��֐�
			/// </summary>
			/// <param name="m">�s��</param>
			/// <returns>�t�s��</returns>
			static Matrix4x4 Inverse(const Matrix4x4& m);

			/// <summary>
			/// �s�񎮂𐶐�����֐�
			/// </summary>
			/// <param name="m">�s��</param>
			/// <returns>�s��</returns>
			static float Determinant(const Matrix4x4& m);

			/// <summary>
			/// ���̃C���X�^���X�̊e����Ԃ�
			/// </summary>
			/// <returns></returns>
			Axis GetAxis() const;

			Math::Vector3 GetPosition();

			/// <summary>
			/// �ʒu�A���_�ʒu�A��x�N�g�����w�肵�ăr���[�s��𐶐�����֐�
			/// </summary>
			/// <param name="pos">�ʒu</param>
			/// <param name="focasPos">���_�ʒu</param>
			/// <param name="upDir">��x�N�g��</param>
			/// <returns>�r���[�s��</returns>
			static Matrix4x4 GetViewMatrixLookAt(const Vector3& pos, const Vector3& focasPos, const Vector3& upDir);

			/// <summary>
			/// �ʒu�A�����A��x�N�g�����w�肵�ăr���[�s��𐶐�����֐�
			/// </summary>
			/// <param name="pos">�ʒu</param>
			/// <param name="direction">����</param>
			/// <param name="upDir">��x�N�g��</param>
			/// <returns>�r���[�s��</returns>
			static Matrix4x4 GetViewMatrixLookTo(const Vector3& pos, const Vector3& direction, const Vector3& upDir);

			/// <summary>
			/// �������e�s��𐶐�����֐�
			/// </summary>
			/// <param name="fov">����p(���ł͂Ȃ��c)</param>
			/// <param name="aspect">�A�X�y�N�g��</param>
			/// <param name="nearClip">�j�A�\�N���b�v</param>
			/// <param name="farClip">�t�@�[�N���b�v</param>
			/// <returns>�������e�s��</returns>
			static Matrix4x4 GetPerspectiveMatrix(float fov, float aspect, float nearClip = 1.0f, float farClip = 10000.0f);

			/// <summary>
			/// ���s���e�s��𐶐�����֐�
			/// </summary>
			/// <param name="size">�T�C�Y</param>
			/// <returns>���s���e�s��</returns>
			static Matrix4x4 GetOrthographMatrix(const Vector2& size);

			/// <summary>
			/// ���s���e�s��(���s��������I�u�W�F�N�g�Ή�)�𐶐�����֐�
			/// </summary>
			/// <param name="size">�T�C�Y</param>
			/// <param name="nearClip">�j�A�\�N���b�v</param>
			/// <param name="farClip">�t�@�[�N���b�v</param>
			/// <returns></returns>
			static Matrix4x4 GetOrthographMatrix(const Vector2& size, float nearClip, float farClip);
		};
		Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);
		Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
		Vector3 operator*(const Vector3& v, const Matrix4x4& m);
	}
}
