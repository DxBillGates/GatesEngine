#include "..\..\Header\Graphics\TextureManager.h"

GE::TextureManager::TextureManager()
{
}

GE::TextureManager::~TextureManager()
{
	for (auto& tex : textures)
	{
		delete tex.second;
	}
}

void GE::TextureManager::Add(ITexture* newTex, const std::string& name)
{
	textures.insert(std::make_pair(name, newTex));
}

GE::ITexture* GE::TextureManager::Get(const std::string& name)
{
	return textures.at(name);
}
