#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <GL/glew.h>
#include <array>
#include <memory>
#include <iterator>
#include "subtexture.h"
#include "image.h"
#include "font.h"

namespace spirit {

// Maximum texture ID's for open GL
#define MAX_TEX_SLOTS 32

// Global array to keep track of texture slots.
static std::array<bool, MAX_TEX_SLOTS> _g_slots;

class Texture {
public:
  Texture();
  Texture(std::string file, std::string key);
  ~Texture();
  void insert_image(std::string file, std::string key);
  void insert_font(std::string file, std::string key, std::string text,
                   size_t size, int r, int g, int b, int a = 255);
  void fit(std::unordered_map<std::string,
                              std::unique_ptr<SubTexture>>::iterator begin,
           std::unordered_map<std::string,
                              std::unique_ptr<SubTexture>>::iterator end,
           int x, int y, int z, int w, int h);
  void generate();
  void bind();
  void unbind();
  GLuint get_id() const;
  GLsizei get_w() const;
  GLsizei get_h() const;
  const SubTexture &operator[](std::string key);

private:
  std::unordered_map<std::string, std::unique_ptr<SubTexture>> _map;
  GLsizei _w, _h, _size;
  GLuint _texture, _id;
};
}

#endif