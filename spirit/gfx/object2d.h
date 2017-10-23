#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "buffer.h"
#include "vertexarray.h"
#include "glm.hpp"
#include "texture.h"
#include <array>
#include <vector>

namespace spirit {

// IDs to tell the fragment shader the type of object.
static const float obj_shape = 0.0;
static const float obj_texture = 1.0;
static const float obj_text = 2.0;

uint32_t rgba_to_uint(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

class Object2d {
public:
  Object2d(const glm::vec3 &pos, int w, int h, 
  uint8_t r, uint8_t g, uint8_t b, uint8_t a=255);
  Object2d(const glm::vec3 &pos, const Texture &texture, const std::string& key);
  Object2d(const glm::vec3 &pos, const Texture &texture, const std::string& key,
  uint8_t r, uint8_t g, uint8_t b, uint8_t a=255);
  uint32_t get_color() const;
  const glm::vec3 &get_pos() const;
  int get_w() const;
  int get_h() const;
  float get_type() const;
  const std::array<glm::vec3, 4> &get_tex_coords() const;
private:
  float _type;
  uint32_t _color;
  glm::vec3 _pos;
  int _w, _h;
  std::array<glm::vec3, 4> _tex_coords;
};

class Text
{
public:
  Text(const glm::vec3& pos, const Texture& texture, const std::string& key, const std::string& text,
    uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
  : _position(pos), _w(0), _h(0)
  {
    init(texture, key, text, r, g, b, a);
  }
  void init(const Texture& texture, const std::string& key, const std::string& text,
    uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
  {
    // Save a temporary position.
    glm::vec3 temp = _position;
    for (auto& c : text)
    {
      // Add each character object. The key for each character is a string
      // constructed like this:
      // "key" + "_S_" + char
      // For example, if your key is "Sans" and your letter is "r":
      // "Sans_S_r".
      _characters.push_back(Object2d(temp, texture, std::string(key + _tag + c), r, g, b, a));
      // Update the position of the next character.
      temp.x += texture[key + _tag + c].get_w();

      // Set the w/h. The width is the summation of the width of each character,
      // the height is the maximum height found.
      _h = std::max(_h, texture[key + _tag + c].get_h());
      _w += texture[key + _tag + c].get_w();
    }
  }
  void set_text(const Texture& texture, const std::string& key, const std::string& text,
    uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
  {
    _w = 0;
    _h = 0;
    _characters.clear();
    init(texture, key, text, r, g, b, a);
  }
  const Object2d* get_ptr() const
  {
    return _characters.data();
  }
  size_t get_size() const
  {
    return _characters.size();
  }
  int get_w() const
  {
    return _w;
  }
  int get_h() const
  {
    return _h;
  }
private:
  int _w;
  int _h;
  glm::vec3 _position;
  std::vector<Object2d> _characters;
};
}

#endif