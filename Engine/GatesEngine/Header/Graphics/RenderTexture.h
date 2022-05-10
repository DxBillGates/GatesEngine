#pragma once
#include "IRenderTexture.h"
#include "IShaderResourceHeap.h"

#include <d3d12.h>

namespace GE
{
	class RenderTexture : public IRenderTexture
	{
	private:
		ID3D12Device* device;

		// renderTarget

		ID3D12DescriptorHeap* rtvHeap;
		Color color;
		D3D12_RESOURCE_STATES currentResourceState;

		// texture

		ID3D12Resource* buffer;
		Math::Vector2 size;
		int srvNum;
	public:
		RenderTexture();
		~RenderTexture();
		void Create(ID3D12Device* device, IShaderResourceHeap* shaderResourceHeap,const Math::Vector2& setSize, const Color& setColor);

		// IRenderTarget interface

		D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() override;
		const Math::Vector2& GetSize() override;
		D3D12_RESOURCE_STATES GetCurrentResourceState() override;
		const Color& GetColor() override;
		void SetCurrentResourceState(D3D12_RESOURCE_STATES state) override;
		void SetColor(const Color& color) override;
		void Prepare(ID3D12GraphicsCommandList* cmdList) override;

		// ITexture interface

		int GetSRVNumber() override;

		// interface

		void EndDraw(ID3D12GraphicsCommandList* cmdList);
	};
}
