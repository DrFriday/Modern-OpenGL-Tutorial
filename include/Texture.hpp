#pragma once

#include <string>

#include <GL/glew.h>

class Texture
{
  public:
    explicit Texture(const std::string& fileName);
    ~Texture();

	void bind(unsigned int unit);
  private:

	// Handle to the texture
    GLuint m_texture;
};