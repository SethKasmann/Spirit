#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <iostream>
#include "glm.hpp"
#include "matrix_transform.hpp"

namespace spirit {
// Class to represent a 2D camera. Handles the orthographic matrix
// based on the screen size, and the translation/scaling based on
// camera movements.
class Camera2d {
public:
  Camera2d(float w, float h);
  void set_position(float x, float y);
  void set_projection(float w, float h);
  void set_scale(float scale);
  void zoom(float scale);
  void move(float dx, float dy);
  const glm::mat4 &get_projection() const;
  const glm::mat4 &get_modelview();
  float get_w() const;
  float get_h() const;
  float get_scale() const;
  const glm::vec2& get_position() const;

private:
  bool _update;
  float _w;
  float _h;
  float _scale;
  glm::vec2 _position;
  glm::mat4 _projection;
  glm::mat4 _modelview;
};
}

#endif