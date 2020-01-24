#include "Transform.hpp"

#include <glm/gtx/transform.hpp>

Transform::Transform(const glm::vec3& pos = glm::vec3(),
                     const glm::vec3& rot = glm::vec3(),
                     const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0)) :
    m_pos(pos), m_rot(rot), m_scale(scale)
{
}

glm::mat4 Transform::getModel() const
{
  auto posMatrix = glm::translate(m_pos);
  auto rotationXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
  auto rotationYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
  auto rotationZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
  auto scaleMatrix = glm::scale(m_scale);

  // Will apply in x, y, z. Matrix multiplication is NOT communitive!
  auto rotMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

  return posMatrix * rotMatrix * scaleMatrix;
}