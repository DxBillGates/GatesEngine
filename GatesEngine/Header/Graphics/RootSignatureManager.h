#pragma once
#include "IRootSignature.h"

#include <string>
#include <map>

namespace GE
{
	class RootSignatureManager
	{
	private:
		std::map<std::string, IRootSignature*> rootSignatures;
	public:
		RootSignatureManager();
		~RootSignatureManager();
		void Add(IRootSignature* newRootSignature, const std::string& name);
		IRootSignature* Get(const std::string& name);
	};
}