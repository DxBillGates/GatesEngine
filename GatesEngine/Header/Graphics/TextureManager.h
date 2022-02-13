#pragma once
#include "ITexture.h"

#include <map>
#include <string>

namespace GE
{
	class TextureManager
	{
	private:
		std::map<std::string, ITexture*> textures;
	public:
		TextureManager();
		~TextureManager();
		void Add(ITexture* newTex, const std::string& name);
		ITexture* Get(const std::string& name);
	};
}