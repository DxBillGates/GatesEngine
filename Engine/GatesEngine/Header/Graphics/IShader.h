#pragma once
#include <d3d12.h>

namespace GE
{
	class IShader
	{
	public:
		virtual ~IShader() {}
		virtual ID3DBlob* GetShaderBinaryData() = 0;
	};
}