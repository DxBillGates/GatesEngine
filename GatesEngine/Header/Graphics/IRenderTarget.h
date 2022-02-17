#pragma once
#include "..\Util\Math\Vector2.h"
#include "Color.h"
#include <d3d12.h>

namespace GE
{
	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() {}
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() = 0;
		virtual const Math::Vector2& GetSize() = 0;
		virtual D3D12_RESOURCE_STATES GetCurrentResourceState() = 0;
		virtual const Color& GetColor() = 0;
		virtual void SetCurrentResourceState(D3D12_RESOURCE_STATES state) = 0;
		virtual void SetColor(const Color& color) = 0;
		virtual void Prepare(ID3D12GraphicsCommandList* cmdList) = 0;
	};
}
