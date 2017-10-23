#include "object2d.h"

namespace spirit {

uint32_t rgba_to_uint(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  return static_cast<int>(a) << 24
       | static_cast<int>(b) << 16
       | static_cast<int>(g) << 8
       | static_cast<int>(r);
}

Object2d::Object2d(const glm::vec3 &pos, int w, int h, 
  uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _pos(pos), _w(w), _h(h), _type(obj_shape) {
  _color = rgba_to_uint(r, g, b, a);
  _tex_coords[0] = glm::vec3(0.0f, 1.0f, 0.0f);
  _tex_coords[1] = glm::vec3(1.0f, 1.0f, 0.0f);
  _tex_coords[2] = glm::vec3(1.0f, 0.0f, 0.0f);
  _tex_coords[3] = glm::vec3(0.0f, 0.0f, 0.0f);
}

Object2d::Object2d(const glm::vec3 &pos, const Texture &texture, const std::string& key)
    : _pos(pos), _type(obj_texture), _color(0) {
  _w = texture[key].get_w();
  _h = texture[key].get_h();
  _tex_coords = texture[key][0];
}

Object2d::Object2d(const glm::vec3 &pos, const Texture &texture, const std::string& key,
  uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : _pos(pos), _type(obj_text) {
  _color = rgba_to_uint(r, g, b, a);
  _w = texture[key].get_w();
  _h = texture[key].get_h();
  _tex_coords = texture[key][0];
}

uint32_t Object2d::get_color() const { return _color; }

const glm::vec3 &Object2d::get_pos() const { return _pos; }

int Object2d::get_w() const
{
  return _w;
}

int Object2d::get_h() const
{
  return _h;
}

float Object2d::get_type() const
{
  return _type;
}

const std::array<glm::vec3, 4> &Object2d::get_tex_coords() const {
  return _tex_coords;
}
}