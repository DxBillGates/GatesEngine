#pragma once
#include <d3d12.h>

namespace GE
{
	class IDepthStencil
	{
	public:
		virtual ~IDepthStencil() {}
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() = 0;
	};
}