#ifndef MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP
#define MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
  public:
    Transform(const glm::vec3& position = glm::vec3(),
              const glm::vec3& rotation = glm::vec3(),
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
        m_position(position),
        m_rotation(rotation), m_scale(scale)
    {
    }

    glm::mat4 getModel() const {
        glm::mat4 posMatrix = glm::translate(m_position);

        glm::mat4 scaleMatrix = glm::translate(m_scale);
    }

    void setPosition(glm::vec3& newValue) {
        m_position = newValue;
    }

    void setRotation(glm::vec3& newValue) {
        m_rotation = newValue;
    }

    void setScale(glm::vec3& newValue) {
        m_scale = newValue;
    }

    glm::vec3 getPosition() {
        return m_position;
    }

    glm::vec3 getRotation() {
        return m_rotation;
    }

    glm::vec3 getScale() {
        return m_scale;
    }

  private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

#endif // MODERN_OPENGL_TUTORIAL_TRANSFORM_HPP
