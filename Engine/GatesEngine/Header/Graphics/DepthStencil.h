#pragma once
#include "..\Util\Math\Vector2.h"
#include "IDepthStencil.h"

namespace GE
{
	class DepthStencil : public IDepthStencil
	{
	private:
		Math::Vector2 size;
		ID3D12Resource* depthBuffer;
		ID3D12DescriptorHeap* dsvHeap;
	public:
		DepthStencil();
		~DepthStencil();
		void Create(const Math::Vector2& size,ID3D12Device* device);
		void Cleanup();

		// interface

		D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() override;
	};
}