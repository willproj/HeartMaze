#pragma once
#include "Common.h"


namespace maze::renderer
{
	class Texture
	{
	public:
		
		static void BindTexture(int slot, GLuint tex);
		static GLuint CreateTexture(const std::string& filePath);
	};

}