#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <iostream>
#include <cmath>
#include "glm.hpp"
#include "matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "rotate_vector.hpp"

static const glm::vec3 xaxis = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 yaxis = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 zaxis = glm::vec3(0.0f, 0.0f, 1.0f);

class Camera3d {
public:
  // Default constructor. Sets the position at the origin, the up vector
  // along the y-axis, and the foward vector along the z-axis.
  Camera3d(float w, float h)
      : _w(w), _h(h)
      {
      	_fov = 45.0f;
      	float angle1=_fov/2.0;
		float angle2=180 - (90 + angle1);
		float Z = 0.5 * _h * sin(glm::radians(angle2))/sin(glm::radians(angle1));
      	_eye = glm::vec3(0, 0, Z);
      	_center = glm::vec3(0, 0, -1);
      	_up = glm::vec3(0, 1, 0);
      }
  // Getters
  glm::vec3 get_eye() const { return _eye; }
  glm::vec3 get_center() const { return _center; }
  glm::vec3 get_up() const { return _up; }
  // The left vector is the cross product of the up and forward vectors.
  // The return vector normalized.
  // e.g. up cross foward
  // Setters
  void set_eye(glm::vec3 &eye) { eye = eye; }
  void set_center(glm::vec3 &center) { _center = center; }
  void set_up(glm::vec3 &up) { _up = up; }
  void set_w(float w) { _w = w; }
  void set_h(float h) { _h = h; }
  // Transformations
  void move(glm::vec3 dir) { _eye += dir; }
  void rotate(float angle, glm::vec3 axis)
  {
  	_center = glm::rotate(_center, angle, axis);
  	_up = glm::rotate(_up, angle, axis);
  }

  glm::mat4 get_projection()
  {
  	return glm::perspective(_fov, _w / _h, 0.1f, 1000.0f);
  }

  glm::mat4 get_view() 
  {
  	std::cout << _eye.x << " " << _eye.y << " " << _eye.z << '\n';
  	return glm::lookAt(_eye, _eye + _center, _up); 
  }

private:
  glm::vec3 _eye;
  glm::vec3 _center;
  glm::vec3 _up;
  float _fov;
  float _w, _h;
};

#endif