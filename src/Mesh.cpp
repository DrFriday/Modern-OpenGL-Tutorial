#include "Mesh.hpp"

#include <vector>

Mesh::~Mesh() { glDeleteVertexArrays(1, &m_vertexArrayObject); }

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
    m_vertexArrayObject(), m_vertexArrayBuffers(), m_drawCount(indices.size())
{
    IndexedModel model;

    for (const auto& vertex : vertices)
    {
        model.positions.push_back(vertex.pos());
        model.texCoords.push_back(vertex.texCoord());
        model.normals.push_back(vertex.normal());
    }

    model.indices = indices;

    initMesh(model);
}

Mesh::Mesh(const std::string& fileName) : m_vertexArrayObject(), m_vertexArrayBuffers() {
    IndexedModel model = OBJModel(fileName).ToIndexedModel();

    m_drawCount = model.indices.size();

    initMesh(model);
}

void Mesh::draw() const
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawElementsBaseVertex(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr, 0);

    glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel& model)
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers.data());

    // Buffer for positions
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), model.positions.data(),
                 GL_STATIC_DRAW);

    // Binding to attrib location 0, look at Shader.cpp
    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Buffer for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTURE_COORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), model.texCoords.data(),
                 GL_STATIC_DRAW);

    // Binding to attrib location 1, look at Shader.cpp
    glEnableVertexAttribArray(TEXTURE_COORD_VB);
    glVertexAttribPointer(TEXTURE_COORD_VB, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    // Going to be an array, but it's going to be referencing data in another array.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(),
                 GL_STATIC_DRAW);

    // Buffer for normals
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), model.normals.data(),
                 GL_STATIC_DRAW);

    // Binding to attrib location 3, look at Shader.cpp
    glEnableVertexAttribArray(NORMAL_VB);
    glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}
