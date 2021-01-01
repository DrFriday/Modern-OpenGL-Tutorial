#ifndef MODERN_OPENGL_TUTORIAL_CAMERA_HPP
#define MODERN_OPENGL_TUTORIAL_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/*
 * Future improvements:
 * Update camera when window gets resized
 * Rotate forward and up to change that during the game.
 */
class Camera
{
  public:
    Camera(const glm::vec3& position, float fov, float aspect, float zNear,
           float zFar) :
        m_position(position),
        m_perspective(glm::perspective(fov, aspect, zNear, zFar)),
        m_forward(glm::vec3(0, 0, 1)), m_up(glm::vec3(-1, 1, 0))
    {
    }

    glm::mat4 getViewProjection() const {
        return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
    }

  private:
    glm::vec3 m_position;
    glm::mat4 m_perspective;
    /**
     * Whatever direction we perceive as forward
     */
    glm::vec3 m_forward;
    /**
     * Whatever direction we perceive is up
     */
    glm::vec3 m_up;
};

#endif // MODERN_OPENGL_TUTORIAL_CAMERA_HPP
