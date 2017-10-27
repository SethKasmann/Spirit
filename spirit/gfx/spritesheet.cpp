#include "spritesheet.h"

namespace spirit {

SpriteSheet::SpriteSheet(std::string file, const glm::vec4 *positions,
                         size_t size)
    : SubTexture(file), _surface(nullptr), _size(size) {
  for (size_t i = 0; i < size; ++i) {
    _positions.push_back(positions[i]);
  }
}

SpriteSheet::~SpriteSheet() { free(); }

void SpriteSheet::load() {
  // Create SDL surface.
  _surface = IMG_Load(_file.c_str());

  // Verify the surface was created properly.
  if (_surface == nullptr) {
    std::cout << "IMG_Load: " << _file << " could not be loaded.\n"
              << "IMG_Load: " << IMG_GetError();
  }
  // Set the position of the image within the sprite sheet.
  _w = _surface->w;
  _h = _surface->h;
}

void SpriteSheet::free() {
  if (_surface != nullptr) {
    SDL_FreeSurface(_surface);
    _surface = nullptr;
  }
}

void SpriteSheet::generate(int w, int h) {
  // Generate the sub image of our 3D texture.
  glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, _position.x, _position.y, _position.z,
                  _w, _h, 1, GL_RGBA, GL_UNSIGNED_BYTE, _surface->pixels);
  // Indent values for edges of sub images for OpenGL. This avoids stray pixels
  // on the edge of rendered images.
  float idnt_w = .5 / w;
  float idnt_h = .5 / h;
  for (std::vector<glm::vec4>::iterator it = _positions.begin();
       it != _positions.end(); ++it) {
    // Generate the texture coordinates for each sprite in the spritesheet.
    std::array<glm::vec3, 4> coordinate;
    coordinate[0] =
        glm::vec3((_position.x + it->x) / w + idnt_w,
                  (_position.y + it->y + it->w) / h - idnt_h, _position.z);
    coordinate[1] =
        glm::vec3((_position.x + it->x + it->z) / w - idnt_w,
                  (_position.y + it->y + it->w) / h - idnt_h, _position.z);
    coordinate[2] = glm::vec3((_position.x + it->x + it->z) / w - idnt_w,
                              (_position.y + it->y) / h + idnt_h, _position.z);
    coordinate[3] = glm::vec3((_position.x + it->x) / w + idnt_w,
                              (_position.y + it->y) / h + idnt_h, _position.z);
    // Add the texture coordinate to the vector.
    _coordinates.push_back(coordinate);
  }
}

const std::array<glm::vec3, 4> &SpriteSheet::operator[](int i) const {
  if (i > _size) {
    std::cout << "SpriteSheet::operator[]: index out of bounds\n";
  }
  return _coordinates[i];
}

}