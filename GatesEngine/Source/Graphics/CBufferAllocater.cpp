#include "..\..\Header\Graphics\CBufferAllocater.h"
#include "..\..\Header\Graphics\COMRelease.h"

GE::CBufferAllocater::CBufferAllocater()
	: device(nullptr)
	, cmdList(nullptr)
	, shaderResourceHeap(nullptr)
	, buffer(nullptr)
	, mappedBuffer(nullptr)
	, currentUsedNumber(0)
{
}

GE::CBufferAllocater::~CBufferAllocater()
{
	COM_RELEASE(buffer);
}

void GE::CBufferAllocater::SetGraphicsDevice(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, IShaderResourceHeap* shaderResourceHeap)
{
	this->device = device;
	this->cmdList = cmdList;
	this->shaderResourceHeap = shaderResourceHeap;
}

void GE::CBufferAllocater::Create()
{
	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resDesc.Width = (UINT64)((1 + 0xff) & ~0xff) * (int)shaderResourceHeap->GetWillUseShaderResourceCount().x;
	HRESULT result = device->CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buffer));

	buffer->Map(0, {}, (void**)&mappedBuffer);
}

void GE::CBufferAllocater::ResetCurrentUsedNumber()
{
	currentUsedNumber = 0;
}

int GE::CBufferAllocater::BindAndAttachData(int descIndex, const void* data, int size)
{
	int sizeAligned = (size + 0xff) & ~0xff;
	int numRequired = sizeAligned / 0x100;

	if (currentUsedNumber + numRequired > (int)shaderResourceHeap->GetWillUseShaderResourceCount().x)return 0;

	int top = currentUsedNumber;

	memcpy(mappedBuffer + top, data, size);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbDesc = {};
	cbDesc.BufferLocation = buffer->GetGPUVirtualAddress() + (UINT64)top * 0x100;
	cbDesc.SizeInBytes = sizeAligned;

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = shaderResourceHeap->GetCPUHandle();
	cpuHandle.ptr += (UINT64)shaderResourceHeap->GetDescriptorHandleIncrementSize() * currentUsedNumber;
	device->CreateConstantBufferView(&cbDesc, cpuHandle);

	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = shaderResourceHeap->GetGPUHandle();
	gpuHandle.ptr += (UINT64)shaderResourceHeap->GetDescriptorHandleIncrementSize() * currentUsedNumber;

	//cmdList->SetGraphicsRootDescriptorTable(descIndex, gpuHandle);

	int useCBVNumber = currentUsedNumber;
	currentUsedNumber += numRequired;

	return useCBVNumber;
}
