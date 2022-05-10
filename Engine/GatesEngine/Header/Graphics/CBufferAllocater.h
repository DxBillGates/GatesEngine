#pragma once
#include "IShaderResourceHeap.h"
#include "ICBufferAllocater.h"

namespace GE
{
	class CBufferAllocater : public ICBufferAllocater
	{
	private:
		ID3D12Device* device;
		ID3D12GraphicsCommandList* cmdList;
		IShaderResourceHeap* shaderResourceHeap;
		ID3D12Resource* buffer;
		struct { char buf[256]; }*mappedBuffer;
		int currentUsedNumber;
	public:
		CBufferAllocater();
		~CBufferAllocater();
		void SetGraphicsDevice(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, IShaderResourceHeap* shaderResourceHeap);
		void Create();

		// interface
		void ResetCurrentUsedNumber() override;
		int BindAndAttachData(int descIndex, const void* data, int size) override;
	};
}
