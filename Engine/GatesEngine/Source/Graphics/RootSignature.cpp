#include "..\..\Header\Graphics\RootSignature.h"
#include "..\..\Header\Graphics\COMRelease.h"

void GE::RootSignature::CreateDescriptorRange(D3D12_DESCRIPTOR_RANGE& descRange, DescriptorRangeType type, int& count)
{
	descRange = {};
	descRange.NumDescriptors = 1;
	descRange.BaseShaderRegister = count;
	descRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	if (type == DescriptorRangeType::CBV)descRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	else if (type == DescriptorRangeType::SRV)descRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	else if (type == DescriptorRangeType::UAV)descRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;

	++count;
}

void GE::RootSignature::CreateStaticSampler(D3D12_STATIC_SAMPLER_DESC& samplerDesc, TextureAddressMode mode, D3D12Filter filter, int count)
{
	D3D12_TEXTURE_ADDRESS_MODE addressMode = (mode == TextureAddressMode::WRAP) ? D3D12_TEXTURE_ADDRESS_MODE_WRAP : D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	D3D12_FILTER samplingFilter = (filter == D3D12Filter::POINT) ? D3D12_FILTER_MIN_MAG_MIP_POINT : D3D12_FILTER_MIN_MAG_MIP_LINEAR;

	samplerDesc = {};
	samplerDesc.AddressU = addressMode;
	samplerDesc.AddressV = addressMode;
	samplerDesc.AddressW = addressMode;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = samplingFilter;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ShaderRegister = count;
}

GE::RootSignature::RootSignature()
	: rootSignature(nullptr)
{
}

GE::RootSignature::~RootSignature()
{
	COM_RELEASE(rootSignature);
}

void GE::RootSignature::Create(ID3D12Device* device, const std::vector<DescriptorRangeType>& descriptorRangeTypes)
{
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	int rangeCount = (int)descriptorRangeTypes.size();

	std::vector<D3D12_ROOT_PARAMETER> rootParams(rangeCount);
	std::vector<D3D12_DESCRIPTOR_RANGE> descRanges(rangeCount);

	int cbvCount, srvCount, uavCount;
	cbvCount = srvCount = uavCount = 0;
	bool isSampler = false;

	{
		// descRangeTypeにあったDescriptorRangeを設定
		int i = 0;
		for (const auto& descRangeType : descriptorRangeTypes)
		{
			if (descRangeType == DescriptorRangeType::CBV)CreateDescriptorRange(descRanges[i], descRangeType, cbvCount);
			else if (descRangeType == DescriptorRangeType::SRV)
			{
				CreateDescriptorRange(descRanges[i], descRangeType, srvCount);
				isSampler = true;
			}
			else if (descRangeType == DescriptorRangeType::UAV)CreateDescriptorRange(descRanges[i], descRangeType, uavCount);

			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &descRanges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

			++i;
		}
	}

	// スタティックサンプラの設定
	const int SAMPLER_COUNT = 4;
	std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplerDescs(SAMPLER_COUNT);
	if (isSampler)
	{
		CreateStaticSampler(staticSamplerDescs[0], TextureAddressMode::WRAP, D3D12Filter::POINT, 0);
		CreateStaticSampler(staticSamplerDescs[1], TextureAddressMode::CLAMP, D3D12Filter::POINT, 1);
		CreateStaticSampler(staticSamplerDescs[2], TextureAddressMode::WRAP, D3D12Filter::LINEAR, 2);
		CreateStaticSampler(staticSamplerDescs[3], TextureAddressMode::CLAMP, D3D12Filter::LINEAR, 3);
	}

	// rootSignatureDescの設定
	rootSignatureDesc.pStaticSamplers = isSampler ? staticSamplerDescs.data() : nullptr;
	rootSignatureDesc.NumStaticSamplers = isSampler ? SAMPLER_COUNT : 0;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams.data();
	rootSignatureDesc.NumParameters = rangeCount;

	// rootSignatureの生成
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* rootBlob = nullptr;
	HRESULT result;

	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootBlob, &errorBlob);
	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}
	result = device->CreateRootSignature(0, rootBlob->GetBufferPointer(), rootBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
}

void GE::RootSignature::Create(ID3D12Device* device, const Math::Vector3& descRangeCounts)
{
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	int rangeCount = (int)descRangeCounts.x + (int)descRangeCounts.y + (int)descRangeCounts.z;

	std::vector<D3D12_ROOT_PARAMETER> rootParams(rangeCount);
	std::vector<D3D12_DESCRIPTOR_RANGE> descRanges(rangeCount);

	bool isSampler = false;

	int count = 0;

	auto SetRootParams = [](D3D12_ROOT_PARAMETER& rootParam, const D3D12_DESCRIPTOR_RANGE* settingRange)
	{
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.DescriptorTable.pDescriptorRanges = settingRange;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	};

	// cbv range
	for (int i = 0; i < (int)descRangeCounts.x; ++i)
	{
		int value = i;
		CreateDescriptorRange(descRanges[i], DescriptorRangeType::CBV, value);
		SetRootParams(rootParams[i], &descRanges[i]);
		++count;
	}

	// srv range
	int preCount = count;
	for (int i = preCount; i < (int)descRangeCounts.y + preCount; ++i)
	{
		int value = i - preCount;
		CreateDescriptorRange(descRanges[i], DescriptorRangeType::SRV, value);
		SetRootParams(rootParams[i], &descRanges[i]);
		isSampler = true;
		++count;
	}

	// uav range
	preCount = count;
	for (int i = preCount; i < (int)descRangeCounts.z + preCount; ++i)
	{
		int value = i - preCount;
		CreateDescriptorRange(descRanges[i], DescriptorRangeType::UAV, value);
		SetRootParams(rootParams[i], &descRanges[i]);
		++count;
	}

	// スタティックサンプラの設定
	const int SAMPLER_COUNT = 4;
	std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplerDescs(SAMPLER_COUNT);
	if (isSampler)
	{
		CreateStaticSampler(staticSamplerDescs[0], TextureAddressMode::WRAP, D3D12Filter::POINT, 0);
		CreateStaticSampler(staticSamplerDescs[1], TextureAddressMode::CLAMP, D3D12Filter::POINT, 1);
		CreateStaticSampler(staticSamplerDescs[2], TextureAddressMode::WRAP, D3D12Filter::LINEAR, 2);
		CreateStaticSampler(staticSamplerDescs[3], TextureAddressMode::CLAMP, D3D12Filter::LINEAR, 3);
	}

	// rootSignatureDescの設定
	rootSignatureDesc.pStaticSamplers = isSampler ? staticSamplerDescs.data() : nullptr;
	rootSignatureDesc.NumStaticSamplers = isSampler ? SAMPLER_COUNT : 0;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams.data();
	rootSignatureDesc.NumParameters = rangeCount;

	// rootSignatureの生成
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* rootBlob = nullptr;
	HRESULT result;

	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootBlob, &errorBlob);
	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}
	result = device->CreateRootSignature(0, rootBlob->GetBufferPointer(), rootBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
}

ID3D12RootSignature* GE::RootSignature::GetRootSignature()
{
	return rootSignature;
}
