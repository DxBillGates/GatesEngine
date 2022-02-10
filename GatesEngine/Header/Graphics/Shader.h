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

		// シェーダーのファイルネーム＋フォーマット(.hlsl)からコンパイルする
		void CompileShaderFile(const std::wstring& filename, const std::string& shaderTarget);
		// filenameに.hlslをつかなくても関数内でつけてコンパイルする
		void CompileShaderFileWithoutFormat(const std::wstring& filename, const std::string& shaderTarget);

		// interface

		ID3DBlob* GetShaderBinaryData() override;
	};
}