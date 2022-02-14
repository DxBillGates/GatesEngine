#pragma once
#include "ITexture.h"
#include "IShaderResourceHeap.h"

#include <string>
#include <d3d12.h>

namespace GE
{
	class Texture : public ITexture
	{
	protected:
		ID3D12Resource* buffer;
		Math::Vector2 size;
		int srvNum;
	public:
		Texture();
		virtual ~Texture();
		void Load(const std::string& filename,ID3D12Device* device,IShaderResourceHeap* shaderResourceHeap);

		// interface
		int GetSRVNumber() override;
	};
}