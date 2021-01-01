#ifndef MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP
#define MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
  public:
    explicit Transform(const glm::vec3& position = glm::vec3(),
              const glm::vec3& rotation = glm::vec3(),
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
        m_position(position),
        m_rotation(rotation), m_scale(scale)
    {
    }

    glm::mat4 getModel() const {
        glm::mat4 posMatrix = glm::translate(m_position);
        glm::mat4 rotXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
        glm::mat4 scaleMatrix = glm::scale(m_scale);

        auto rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        // Can get different effects depending on the order you multiply
        return posMatrix * rotMatrix * scaleMatrix;
    }

    void setPosition(const glm::vec3& newValue) {
        m_position = newValue;
    }

    void setRotation(const glm::vec3& newValue) {
        m_rotation = newValue;
    }

    void setScale(const glm::vec3& newValue) {
        m_scale = newValue;
    }

    glm::vec3& getPosition() {
        return m_position;
    }

    glm::vec3& getRotation() {
        return m_rotation;
    }

    glm::vec3& getScale() {
        return m_scale;
    }

  private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

#endif // MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP
