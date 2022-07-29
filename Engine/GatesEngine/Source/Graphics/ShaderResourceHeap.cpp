#include "..\..\Header\Graphics\ShaderResourceHeap.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::ShaderResourceHeap::ShaderResourceHeap()
	: device(nullptr)
	, cmdList(nullptr)
	, heap(nullptr)
	, usedShaderResourceCount(Math::Vector3())
	, nextUseSrvDescriptorNumber(0)
	, nextUseUavDescriptorNumber(0)
{
}

GE::ShaderResourceHeap::~ShaderResourceHeap()
{
	COM_RELEASE(heap);
}

void GE::ShaderResourceHeap::SetGraphicsDevice(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	this->device = device;
	this->cmdList = cmdList;
}

void GE::ShaderResourceHeap::Create(const Math::Vector3& count)
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NodeMask = 0;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.NumDescriptors = (int)count.x + (int)count.y + (int)count.z;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	HRESULT result = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap));

	this->usedShaderResourceCount = count;
}

void GE::ShaderResourceHeap::Set()
{
	ID3D12DescriptorHeap* ppHeaps[] = { heap };
	cmdList->SetDescriptorHeaps(1, ppHeaps);
}

ID3D12DescriptorHeap* GE::ShaderResourceHeap::GetHeap()
{
	return heap;
}

D3D12_CPU_DESCRIPTOR_HANDLE GE::ShaderResourceHeap::GetCPUHandle()
{
	return heap->GetCPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE GE::ShaderResourceHeap::GetGPUHandle()
{
	return heap->GetGPUDescriptorHandleForHeapStart();
}

D3D12_GPU_DESCRIPTOR_HANDLE GE::ShaderResourceHeap::GetGPUHandleForCBV(int value)
{
	int incrementSize = GetDescriptorHandleIncrementSize();
	D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)incrementSize * value;
	return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE GE::ShaderResourceHeap::GetGPUHandleForSRV(int value)
{
	int incrementSize = GetDescriptorHandleIncrementSize();
	D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)incrementSize * ((UINT64)usedShaderResourceCount.x + 1);
	handle.ptr += (UINT64)incrementSize * value;
	return handle;
}

D3D12_GPU_DESCRIPTOR_HANDLE GE::ShaderResourceHeap::GetGPUHandleForUAV(int value)
{
	int incrementSize = GetDescriptorHandleIncrementSize();
	D3D12_GPU_DESCRIPTOR_HANDLE handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)incrementSize * ((UINT64)usedShaderResourceCount.x + 1);
	handle.ptr += (UINT64)incrementSize * ((UINT64)usedShaderResourceCount.y + 1);
	handle.ptr += (UINT64)incrementSize * value;
	return handle;
}

int GE::ShaderResourceHeap::GetDescriptorHandleIncrementSize()
{
	return device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

const GE::Math::Vector3& GE::ShaderResourceHeap::GetWillUseShaderResourceCount()
{
	return usedShaderResourceCount;
}

int GE::ShaderResourceHeap::GetNextSRVNumber()
{
	return nextUseSrvDescriptorNumber;
}

int GE::ShaderResourceHeap::GetNextUAVNumber()
{
	return 0;
}

void GE::ShaderResourceHeap::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc, D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
	device->CreateConstantBufferView(&cbvDesc, handle);
}

void GE::ShaderResourceHeap::CreateSRV(ID3D12Resource* buffer, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	int incrementSize = GetDescriptorHandleIncrementSize();
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += ((UINT64)usedShaderResourceCount.x + 1) * incrementSize + (UINT64)nextUseSrvDescriptorNumber * incrementSize;
	device->CreateShaderResourceView(buffer, &srvDesc, handle);
	++nextUseSrvDescriptorNumber;
}

void GE::ShaderResourceHeap::CreateUAV(ID3D12Resource* buffer, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += (UINT64)GetDescriptorHandleIncrementSize() * nextUseUavDescriptorNumber;
	device->CreateUnorderedAccessView(buffer, nullptr, &uavDesc, handle);
	++nextUseUavDescriptorNumber;
}
