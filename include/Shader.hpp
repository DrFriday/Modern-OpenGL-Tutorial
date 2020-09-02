#pragma once

#include <GL/glew.h>
#include <array>
#include <string>

class Shader
{
 public:
  Shader(const std::string& fileName);
  ~Shader();

  void bind();

 private:
  // Handle to program
  GLuint m_program;
  static const unsigned int NUM_SHADERS = 2;
  std::array<GLuint, NUM_SHADERS> m_shaders;

  enum
  {
    U_TRANSFORM,
    NUM_UNIFORMS
  };

  std::array<GLuint, NUM_UNIFORMS> m_uniforms;

  std::string loadShader(const std::string& fileName);
  void checkShaderError(GLuint shader, GLuint flag, bool isProgram,
                        const std::string& errorMessage);
  GLuint createShader(const std::string& text, GLenum shaderType);
};