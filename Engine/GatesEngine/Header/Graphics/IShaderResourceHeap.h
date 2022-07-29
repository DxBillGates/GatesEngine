#pragma once
#include "..\Util\Math\Vector3.h"

#include <d3d12.h>

namespace GE
{
	class IShaderResourceHeap
	{
	public:
		virtual ~IShaderResourceHeap() {}
		virtual ID3D12DescriptorHeap* GetHeap() = 0;
		virtual D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle() = 0;
		virtual D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle() = 0;
		virtual D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForCBV(int value) = 0;
		virtual D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForSRV(int value) = 0;
		virtual D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandleForUAV(int value) = 0;
		virtual int GetDescriptorHandleIncrementSize() = 0;
		virtual const Math::Vector3& GetWillUseShaderResourceCount() = 0;
		virtual int GetNextSRVNumber() = 0;
		virtual int GetNextUAVNumber() = 0;

		virtual void CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc,D3D12_CPU_DESCRIPTOR_HANDLE handle) = 0;
		virtual void CreateSRV(ID3D12Resource* buffer,const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc) = 0;
		virtual void CreateUAV(ID3D12Resource* buffer,const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc) = 0;
	};
}
