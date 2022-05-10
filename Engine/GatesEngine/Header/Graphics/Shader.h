#pragma once
#include "IShader.h"

#include <string>

namespace GE
{
	class Shader : public IShader
	{
	private:
		ID3DBlob* shaderBinaryData;
	public:
		Shader();
		~Shader();

		// �V�F�[�_�[�̃t�@�C���l�[���{�t�H�[�}�b�g(.hlsl)����R���p�C������
		void CompileShaderFile(const std::wstring& filename, const std::string& shaderTarget);
		// filename��.hlsl�����Ȃ��Ă��֐����ł��ăR���p�C������
		void CompileShaderFileWithoutFormat(const std::wstring& filename, const std::string& shaderTarget);

		// interface

		ID3DBlob* GetShaderBinaryData() override;
	};
}