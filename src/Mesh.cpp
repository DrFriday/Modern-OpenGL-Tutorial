#include "Mesh.hpp"

Mesh::Mesh(Triangle triangle) :
    m_vertexArrayBuffers(), m_drawCount(NUM_BUFFERS)
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

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    // Interpret this buffer as an array
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION]);

    // Put vertex data in our array, move to the GPU
    // GL_STATIC_DRAW - put the data somewhere it won't be changed
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(data[0]), data,
                 GL_STATIC_DRAW);

    // Going to be some attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}