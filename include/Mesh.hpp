#pragma once

#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex
{
    Vertex(const glm::vec3& pos) : pos(pos) {}

    glm::vec3 pos;
};

constexpr auto TRI_NUM_VERTICES = 3;
using Triangle = std::array<Vertex, TRI_NUM_VERTICES>;

constexpr auto NUM_BUFFERS = 1;

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
        POSITION
    };
    //std::array<GLuint, 1> m_vertexArrayBuffers;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    // How much we want to draw
    unsigned int m_drawCount;
};