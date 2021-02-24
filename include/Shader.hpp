#pragma once

#include <GL/glew.h>
#include <string>
#include <array>
#include "Transform.hpp"
#include "Camera.hpp"

constexpr int NUM_SHADERS = 2;

class Shader
{
  public:
    explicit Shader(const std::string& fileName);
    ~Shader();

    void bind() const;
    void update(const Transform& transform, const Camera& camera);

  private:

    // Handle to program
    GLuint m_program;
    std::array<GLuint, NUM_SHADERS> m_shaders;

    enum
    {
        TRANSFORM_U = 0,
        NUM_UNIFORMS
    };
    std::array<GLuint, NUM_UNIFORMS> m_uniforms;

	static std::string loadShader(const std::string& fileName);
    static void checkShaderError(GLuint shader, GLuint flag, bool isProgram,
                           const std::string& errorMessage);
    static GLuint createShader(const std::string& text, GLenum shaderType);
};