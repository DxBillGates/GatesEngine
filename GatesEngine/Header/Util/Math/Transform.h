#pragma once
#include "Math.h"

namespace GE
{
	struct Transform
	{
		Math::Vector3 position = {};
		Math::Vector3 rotation = {};
		Math::Vector3 scale = { 1,1,1 };


		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Transform()
		{
		}


		/// <summary>
		/// �ʒu�A��]�A�T�C�Y���w�肷��R���X�g���N�^
		/// </summary>
		/// <param name="pos">�ʒu</param>
		/// <param name="rotation">��]</param>
		/// <param name="scale">�T�C�Y</param>
		Transform(const Math::Vector3& pos, const Math::Vector3& rotation, const Math::Vector3& scale)
			: position(pos)
			, rotation(rotation)
			, scale(scale)
		{
		}

		/// <summary>
		/// Transform���w�肷��R���X�g���N�^
		/// </summary>
		/// <param name="transform">�R�s�[����Transform</param>
		Transform(const Transform& transform)
			: position(transform.position)
			, rotation(transform.rotation)
			, scale(transform.scale)
		{
		}

		/// <summary>
		/// �s���Ԃ��֐�
		/// </summary>
		/// <returns>�s��</returns>
		Math::Matrix4x4 GetMatrix();

		/// <summary>
		/// �I�C���[�p��Ԃ��֐�
		/// </summary>
		/// <returns>�I�C���[�p</returns>
		Math::Vector3 GetEulerAngle();

		/// <summary>
		/// �O���x�N�g����Ԃ��֐�
		/// </summary>
		/// <returns>�O���x�N�g��</returns>
		Math::Vector3 GetForward();

		/// <summary>
		/// �E���x�N�g����Ԃ��֐�
		/// </summary>
		/// <returns>�E���x�N�g��</returns>
		Math::Vector3 GetRight();

		/// <summary>
		/// ��x�N�g����Ԃ��֐�
		/// </summary>
		/// <returns>��x�N�g��</returns>
		Math::Vector3 GetUp();
	};
}