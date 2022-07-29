#pragma once
#include "..\Util\Math\Vector2.h"
#include "IRenderTarget.h"
#include <vector>
#include <d3d12.h>

namespace GE
{
	class RenderTarget : public IRenderTarget
	{
	private:
		Math::Vector2 size;
		std::vector<ID3D12Resource*> rtvBuffer;
		ID3D12DescriptorHeap* rtvHeap;
		Color color;
		D3D12_RESOURCE_STATES currentResourceState;
		int index;
		int incrementSize;
	public:
		RenderTarget();
		~RenderTarget();
		void Create(ID3D12Device* device);
		void Cleanup();

		std::vector<ID3D12Resource*>& GetFrameBuffers();
		void SetIndex(int value);

		// interface

		D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() override;
		const Math::Vector2& GetSize() override;
		D3D12_RESOURCE_STATES GetCurrentResourceState() override;
		const Color& GetColor() override;
		void SetCurrentResourceState(D3D12_RESOURCE_STATES state) override;
		void SetColor(const Color& color) override;
		void Prepare(ID3D12GraphicsCommandList* cmdList) override;
	};
}