#include "Mesh.hpp"

Mesh::Mesh(Triangle triangle) :
    m_vertexArrayBuffers(), m_drawCount(triangle.max_size())
{
  initializeMesh(triangle.data(), triangle.max_size());
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) :
    m_vertexArrayBuffers(), m_drawCount(numVertices)
{
  initializeMesh(vertices, numVertices);
}

Mesh::~Mesh() { glDeleteVertexArrays(1, &m_vertexArrayObject); }

void Mesh::draw()
{
  glBindVertexArray(m_vertexArrayObject);

  glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

  glBindVertexArray(0);
}

void Mesh::initializeMesh(Vertex* data, unsigned int numVertices)
{
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  std::array<glm::vec3, TRI_NUM_VERTICES> positions;
  std::array<glm::vec2, TRI_NUM_VERTICES> textureCoords;

  // positions.reserve(numVertices);
  // textureCoords.reserve(numVertices);

  for (decltype(numVertices) i = 0; i < numVertices; i++)
  {
    // positions.push_back(data[i].pos());
    // textureCoords.push_back(data[i].texCoord());
    positions[i] = data[i].pos();
    textureCoords[i] = data[i].texCoord();
  }

  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

  // Buffer for positions
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]),
               positions.data(), GL_STATIC_DRAW);
  // Binding to attrib location 0, look at Shader.cpp
  glEnableVertexAttribArray(POSITION);
  glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Buffer for texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD]);
  glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textureCoords[0]),
               textureCoords.data(), GL_STATIC_DRAW);
  // Binding to attrib location 1, look at Shader.cpp
  glEnableVertexAttribArray(TEXCOORD);
  glVertexAttribPointer(TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
}