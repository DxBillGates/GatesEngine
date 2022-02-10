#pragma once
#include <d3d12.h>

namespace GE
{
	class IRootSignature
	{
	public:
		virtual ~IRootSignature() {}
		virtual ID3D12RootSignature* GetRootSignature() = 0;
	};
}