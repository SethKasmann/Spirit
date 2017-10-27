#ifndef SHEET_H
#define SHEET_H

#include "subtexture.h"
#include <vector>

namespace spirit {

class SpriteSheet : public SubTexture {
public:
  SpriteSheet(std::string file, const glm::vec4 *positions, size_t size);
  ~SpriteSheet();
  void load();
  void free();
  void generate(int w, int h);
  const std::array<glm::vec3, 4> &operator[](int i) const;

private:
  std::vector<std::array<glm::vec3, 4>> _coordinates;
  SDL_Surface *_surface;
  std::vector<glm::vec4> _positions;
  size_t _size;
};

}

#endif