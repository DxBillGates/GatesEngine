#include "..\..\Header\Graphics\RootSignatureManager.h"

GE::RootSignatureManager::RootSignatureManager()
{
}

GE::RootSignatureManager::~RootSignatureManager()
{
	for (auto& rootSignature : rootSignatures)
	{
		delete rootSignature.second;
	}
}

void GE::RootSignatureManager::Add(IRootSignature* newRootSignature, const std::string& name)
{
	rootSignatures.insert(std::make_pair(name, newRootSignature));
}

GE::IRootSignature* GE::RootSignatureManager::Get(const std::string& name)
{
	return rootSignatures.at(name);
}
