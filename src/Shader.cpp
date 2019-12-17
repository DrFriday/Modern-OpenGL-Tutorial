#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& fileName) : m_program(glCreateProgram()) {}

Shader::~Shader() { glDeleteProgram(m_program); }

void Shader::bind() {}

std::string Shader::loadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
        return "";
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

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}