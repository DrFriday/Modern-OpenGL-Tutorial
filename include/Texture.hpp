#pragma once

#include <GL/glew.h>

#include <string>

class Texture
{
 public:
  Texture(const std::string& fileName);
  ~Texture();

  void bind(unsigned int unit);

 private:
  // Handle to the texture
  GLuint m_texture;
};