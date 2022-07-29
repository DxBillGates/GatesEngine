#pragma once
#include "..\Util\Math\Vector3.h"
#include "IShaderResourceHeap.h"

#include <d3d12.h>

namespace GE
{
	class ShaderResourceHeap : public IShaderResourceHeap
	{
	private:
		ID3D12Device* device;
		ID3D12GraphicsCommandList* cmdList;
		ID3D12DescriptorHeap* heap;
		Math::Vector3 usedShaderResourceCount;
		int nextUseSrvDescriptorNumber;
		int nextUseUavDescriptorNumber;
	public:
		ShaderResourceHeap();
		~ShaderResourceHeap();
		void SetGraphicsDevice(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);
		void Create(const Math::Vector3& count);
		void Set();

		// interface

		ID3D12DescriptorHeap* GetHeap() override;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle() override;
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() override;
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForCBV(int value) override;
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForSRV(int value) override;
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForUAV(int value) override;
		int GetDescriptorHandleIncrementSize() override;
		const Math::Vector3& GetWillUseShaderResourceCount() override;
		int GetNextSRVNumber() override;
		int GetNextUAVNumber() override;

		void CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle) override;
		void CreateSRV(ID3D12Resource* buffer, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc) override;
		void CreateUAV(ID3D12Resource* buffer, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc) override;
	};
}