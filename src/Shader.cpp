#include "Shader.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& fileName)
{
  m_program = glCreateProgram();

  // File extensions are custom.
  m_shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  for (const auto& shader : m_shaders) glAttachShader(m_program, shader);

  // Telling each part what to expect, syncing them up!
  //
  // Tells OpenGL what part of the data to read as what variable
  //
  // Sends to shader
  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");

  // Can fail
  glLinkProgram(m_program);
  checkShaderError(m_program, GL_LINK_STATUS, true,
                   "Error: Program linking failed: ");

  glValidateProgram(m_program);
  checkShaderError(m_program, GL_VALIDATE_STATUS, true,
                   "Error: Program is invalid: ");

  m_uniforms[U_TRANSFORM] = glGetUniformLocation(m_program, "u_transform");
}

Shader::~Shader()
{
  for (auto& shader : m_shaders)
  {
    glDetachShader(m_program, shader);
    glDeleteShader(shader);
  }

  glDeleteProgram(m_program);
}

void Shader::bind() { glUseProgram(m_program); }

std::string Shader::loadShader(const std::string& fileName)
{
  std::ifstream file;
  file.open(fileName);

  if (!file.is_open())
  {
    std::stringstream ss;
    ss << "Unable to load shader: " << fileName << std::endl;
    throw std::runtime_error(ss.str().c_str());
  }

  std::stringstream ss;
  std::string line;

  while (file.good())
  {
    std::getline(file, line);
    ss << line << "\n";
  }

  return ss.str();
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram,
                              const std::string& errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = {0};

  if (isProgram)
  {
    glGetProgramiv(shader, flag, &success);
  }
  else
  {
    glGetShaderiv(shader, flag, &success);
  }

  if (success == GL_FALSE)
  {
    if (isProgram)
    {
      glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
    }
    else
    {
      glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
    }

    std::stringstream ss;
    ss << errorMessage << ": '" << error << "'" << std::endl;

    throw std::runtime_error(ss.str().c_str());
  }
}

GLuint Shader::createShader(const std::string& text, GLenum shaderType)
{
  auto shader = glCreateShader(shaderType);

  if (shader == 0)
  {
    throw std::runtime_error("Error: Shader creation failed");
  }

  // Can have multiple strings per shader
  const GLchar* shaderSourceStrings[1];
  shaderSourceStrings[0] = text.c_str();

  GLint shaderSourceStringLengths[1];
  shaderSourceStringLengths[0] = static_cast<GLint>(text.length());

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  checkShaderError(shader, GL_COMPILE_STATUS, false,
                   "Error: Shader compilation failed: ");

  return shader;
}
