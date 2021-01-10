#include "renderer/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "renderer/vendor/stb_image.h"

namespace maze::renderer
{
	GLuint Texture::CreateTexture(const std::string& filePath)
	{
        GLuint tex;
        glGenTextures(1, &tex);

        int width, height, nrComponents;
        stbi_set_flip_vertically_on_load(true);

        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_image_free(data);
            
        }
        else
        {
            std::cout << "Texture failed to load at path: " << filePath << std::endl;
            stbi_image_free(data);
        }

        return tex;
	}

    void Texture::BindTexture(int slot, GLuint tex)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, tex);
    }


}