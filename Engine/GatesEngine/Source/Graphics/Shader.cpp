#include "..\..\Header\Graphics\Shader.h"
#include "..\..\Header\Graphics\COMRelease.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

GE::Shader::Shader()
	: shaderBinaryData(nullptr)
{
}

GE::Shader::~Shader()
{
	COM_RELEASE(shaderBinaryData);
}

void GE::Shader::CompileShaderFile(const std::wstring& filename, const std::string& shaderTarget)
{
	ID3DInclude* include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	ID3DBlob* errorBlob = nullptr;
	HRESULT result;

	std::wstring firstPass = L"Resources/Shader/";

	std::wstring fullFilename = firstPass + filename;
	result = D3DCompileFromFile(fullFilename.c_str(), nullptr, include, "main", shaderTarget.c_str(), flag, 0, &shaderBinaryData, &errorBlob);
}

void GE::Shader::CompileShaderFileWithoutFormat(const std::wstring& filename, const std::string& shaderTarget)
{
	ID3DInclude* include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	ID3DBlob* errorBlob = nullptr;
	HRESULT result;

	std::wstring format = L".hlsl";
	std::wstring firstPass = L"Resources/Shader/";

	std::wstring fullFilename = firstPass + filename + format;
	result = D3DCompileFromFile(fullFilename.c_str(), nullptr, include, "main", shaderTarget.c_str(), flag, 0, &shaderBinaryData, &errorBlob);
}

ID3DBlob* GE::Shader::GetShaderBinaryData()
{
	return shaderBinaryData;
}
