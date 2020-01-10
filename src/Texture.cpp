#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cassert>

Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;

    auto imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	assert(imageData != NULL);

	// Making space for the texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);


	// Wraps texture around, if 512x512, and looking for pixel 513,
	// it will wrap back to zero.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// If the texture takes up more or fewer pixels than is specifies,
	// this will fill in the gaps.
	//
	// GL_LINEAR - some filtering, extrapolates
    // GL_NEAREST - no filtering! (pixelated effect)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Sends the texture to the GPU!
	// level - mipmapping, different resolutions at different distances.
	//			Higher resolution at nearer distances, lower at further
	//
	// internalFormat - way to format pixels
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imageData); // pick up @ 18:23

	stbi_image_free(imageData);
}

Texture::~Texture() { glDeleteTextures(1, &m_texture); }

// Setup OpenGL to use whatever texture we're binding.
void Texture::bind(unsigned int unit)
{
    assert(unit <= 31);

	// Change which texture OpenGL is working with
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);

}

