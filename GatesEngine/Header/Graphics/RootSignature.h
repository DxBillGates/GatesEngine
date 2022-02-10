#pragma once
#include "IRootSignature.h"

#include <vector>

namespace GE
{
	enum class DescriptorRangeType
	{
		CBV,
		SRV,
		UAV,
	};

	enum class TextureAddressMode
	{
		WRAP,
		CLAMP
	};

	enum class D3D12Filter
	{
		POINT,
		LINEAR
	};

	class RootSignature : public IRootSignature
	{
	private:
		ID3D12RootSignature* rootSignature;
	private:
		void CreateDescriptorRange(D3D12_DESCRIPTOR_RANGE& descRange, DescriptorRangeType type, int& count);
		void CreateStaticSampler(D3D12_STATIC_SAMPLER_DESC& samplerDesc, TextureAddressMode mode, D3D12Filter filter, int count);
	public:
		RootSignature();
		~RootSignature();
		void Create(ID3D12Device* device, const std::vector<DescriptorRangeType>& descriptorRangeTypes);

		// interface

		ID3D12RootSignature* GetRootSignature() override;
	};
}
