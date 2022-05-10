#pragma once
#include "IDepthTexture.h"
#include "IShaderResourceHeap.h"

#include <d3d12.h>

namespace GE
{
	class DepthTexture : public IDepthTexture
	{
	private:
		// depthStencil

		ID3D12DescriptorHeap* dsvHeap;

		// texture

		ID3D12Resource* buffer;
		Math::Vector2 size;
		int srvNum;
	public:
		DepthTexture();
		~DepthTexture();
		void Create(ID3D12Device* device, IShaderResourceHeap* shaderResourceHeap,const Math::Vector2& setSize);

		// IDepthStencil interface

		D3D12_CPU_DESCRIPTOR_HANDLE GetHandle();

		// ITexture interface

		int GetSRVNumber() override;
	};
}
