#include "camera2d.h"

namespace spirit {

// CTOR. Sets the initial orthographic matrix.
Camera2d::Camera2d(float w, float h)
    : _scale(1.0f), _position(glm::vec2(0)), _modelview(glm::mat4(1)) {
  set_projection(w, h);
  set_position(0, 0);
  set_scale(1);
}

// Set the camera position.
void Camera2d::set_position(float x, float y) {
  _position = glm::vec2(x, y);
  _update = true;
}

// Set the projection matrix.
void Camera2d::set_projection(float w, float h) {
  _w = w;
  _h = h;
  _projection = glm::ortho(-w / 2, w / 2, -h / 2, h / 2);
  _update = true;
}

// Set the scale factor.
void Camera2d::set_scale(float scale) {
  _scale = scale;
  _update = true;
}

void Camera2d::zoom(float scale) {
  // Zoom proportional to the currenct scale amount.
  if (scale > 0)
    _scale *= 1 + scale;
  if (scale < 0)
    _scale /= 1 + -scale;
  // TODO: add a MIN / MAX zoom cap.
  _update = true;
}

void Camera2d::move(float dx, float dy) {
  _position += glm::vec2(dx, dy);
  _update = true;
}

// Get the projection matrix.
const glm::mat4 &Camera2d::get_projection() const { return _projection; }

// Get and update (if necessary) the model matrix.
const glm::mat4 &Camera2d::get_modelview() {
  // Only recalculate the model matrix if there was a change.
  if (_update) {
    // Set the translation matrix.
    glm::mat4 translation =
        glm::translate(glm::mat4(1), glm::vec3(-_position.x, -_position.y, 0));

    // Set the scaling matrix.
    glm::mat4 scaling =
        glm::translate(glm::mat4(1), glm::vec3(_position.x, _position.y, 0));
    scaling = glm::scale(scaling, glm::vec3(_scale, _scale, 1));
    scaling = glm::translate(scaling, glm::vec3(-_position.x, -_position.y, 0));

    // Calculate the model matrix.
    _modelview = translation * scaling;
    _update = false;
  }
  return _modelview;
}

// Getters
float Camera2d::get_w() const
{
  return _w;
}

float Camera2d::get_h() const
{
  return _h;
}

float Camera2d::get_scale() const
{
  return _scale;
}

const glm::vec2& Camera2d::get_position() const
{
  return _position;
}
}