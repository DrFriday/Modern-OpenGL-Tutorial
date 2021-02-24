#pragma once

#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>
#include <vector>
#include "obj_loader.hpp"

struct Vertex
{
  public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord) : m_pos(pos), m_textureCoord(texCoord) {}

    glm::vec3 pos() const { return m_pos; }
    glm::vec2 texCoord() const { return m_textureCoord; }

  private:
    glm::vec3 m_pos;
    glm::vec2 m_textureCoord;
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
        NUM_BUFFERS
    };

    std::array<GLuint, NUM_BUFFERS> m_vertexArrayBuffers;

    std::size_t m_drawCount;

    void initMesh(const IndexedModel& model);
};