#pragma once

#include <GL/glew.h>
#include <array>
#include <string>


constexpr int NUM_SHADERS = 2;

class Shader
{
 public:
  Shader(const std::string& fileName);
  ~Shader();

  void bind();

 private:
  // Handle to program
  GLuint m_program;
  std::array<GLuint, NUM_SHADERS> m_shaders;

  std::string loadShader(const std::string& fileName);
  void checkShaderError(GLuint shader, GLuint flag, bool isProgram,
                        const std::string& errorMessage);
  GLuint createShader(const std::string& text, GLenum shaderType);
};