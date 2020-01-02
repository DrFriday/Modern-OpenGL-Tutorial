#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;

    auto imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	// Making space for the texture
	glGenTextures(1, &m_texture);

	glBindTexture(GL_TEXTURE_2D, m_texture);

	stbi_image_free(imageData);
}

// Setup OpenGL to use whatever texture we're binding.
void Texture::bind(unsigned int unit)
{
    // stuff
}