#pragma once

#include "obj_loader.hpp"

#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
  public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0)) :
        m_pos(pos), m_textureCoord(texCoord), m_normal(normal)
    {
    }

    glm::vec3 pos() const { return m_pos; }
    glm::vec2 texCoord() const { return m_textureCoord; }
    glm::vec3 normal() const { return m_normal; }

  private:
    glm::vec3 m_pos;
    glm::vec2 m_textureCoord;
    glm::vec3 m_normal; // up direction on a surface
};

class Mesh
{
  public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    Mesh(const std::string& fileName);
    ~Mesh();

    void draw() const;

  private:
    GLuint m_vertexArrayObject;

    enum
    {
        POSITION_VB,
        TEXTURE_COORD_VB,
        INDEX_VB,
        NORMAL_VB,
        NUM_BUFFERS,
    };

    std::array<GLuint, NUM_BUFFERS> m_vertexArrayBuffers;

    std::size_t m_drawCount;

    void initMesh(const IndexedModel& model);
};