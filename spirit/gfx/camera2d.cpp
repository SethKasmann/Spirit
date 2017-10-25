#include "camera2d.h"

namespace spirit {
Camera2d::Camera2d() : Camera2d(0.0f, 0.0f) {}

Camera2d::Camera2d(float x, float y)
    : _update(true), _scale(1.0f), _position(glm::vec2(x, y)),
      _projection(glm::mat4()), _modelview(glm::mat4()) {}

void Camera2d::set_position(float x, float y) {
  _position = glm::vec2(x, y);
  _update = true;
}

void Camera2d::set_ortho(int w, int h) {
  _projection = glm::ortho(-w / 2.0f, static_cast<float>(w / 2), -h / 2.0f,
                           static_cast<float>(h / 2));
}

void Camera2d::set_scale(float scale) {
  _scale = scale;
  _update = true;
}

void Camera2d::zoom(float scale) {
  _scale += scale;
  _update = true;
}

void Camera2d::move(float dx, float dy) {
  _position += glm::vec2(dx, dy);
  _update = true;
}

const glm::mat4 &Camera2d::get_projection() const { return _projection; }

const glm::mat4 &Camera2d::get_modelview() {
  if (_update) {
    _modelview =
        glm::translate(glm::mat4(), glm::vec3(_position.x, _position.y, 0.0f));
    _modelview = glm::scale(_modelview, glm::vec3(_scale, _scale, 1.0f));
    _update = false;
  }
  return _modelview;
}
}