#pragma once

#include <glm/glm.hpp>

class Transform
{
 public:
  Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);

  // In gl, a matrix that contains the position, rotation, and scale of
  // something is generally called a model.
  glm::mat4 getModel() const;

  glm::vec3 pos() const { return m_pos; };
  glm::vec3 rot() const { return m_rot; };
  glm::vec3 scale() const { return m_scale; };

  void pos(glm::vec3& newPos) { m_pos = newPos; };
  void rot(glm::vec3& newRot) { m_rot = newRot; };
  void scale(glm::vec3& newScale) { m_scale = newScale; };

 private:
  glm::vec3 m_pos;
  glm::vec3 m_rot;
  glm::vec3 m_scale;
};