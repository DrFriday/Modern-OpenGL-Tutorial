#pragma once

#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>


struct Vertex
{
 public:
  Vertex(const glm::vec3& pos, const glm::vec2& texCoord) :
      m_pos(pos), m_textureCoord(texCoord)
  {
  }

  glm::vec3 pos() const { return m_pos; }
  glm::vec2 texCoord() const { return m_textureCoord; }

 private:
  glm::vec3 m_pos;
  glm::vec2 m_textureCoord;
};

constexpr auto TRI_NUM_VERTICES = 3;
using Triangle = std::array<Vertex, TRI_NUM_VERTICES>;

class Mesh
{
 private:
 public:
  Mesh(Triangle triangle);
  Mesh(Vertex* vertices, unsigned int numVertices);
  ~Mesh();

  void draw();

 private:
  void initializeMesh(Vertex* data, unsigned int numVertices);

  GLuint m_vertexArrayObject;

  enum
  {
    POSITION,
    TEXCOORD,
    NUM_BUFFERS
  };

  // std::array<GLuint, 1> m_vertexArrayBuffers;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];

  // How much we want to draw
  unsigned int m_drawCount;
};