#include "image.h"

namespace spirit {

Image::Image(std::string file) : SubTexture(file), _surface(nullptr) {}

Image::~Image() { free(); }

// Convert an image file into a SDL Surface
void Image::load() {
  // Create SDL surface.
  _surface = IMG_Load(_file.c_str());

  // Verify the surface was created properly.
  if (_surface == nullptr) {
    std::cout << "IMG_Load: " << _file << " could not be loaded.\n"
              << "IMG_Load: " << IMG_GetError();
  }

  // Set the w, h of the layer.
  _w = _surface->w;
  _h = _surface->h;
}

// Free the SDL surface.
void Image::free() {
  if (_surface != nullptr) {
    SDL_FreeSurface(_surface);
    _surface = nullptr;
  }
}

// Generate the OpenGL Sub image within the 3D texture.
void Image::generate(int w, int h) {
  // Generate the sub image of our 3D texture.
  glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, _position.x, _position.y, _position.z,
                  _w, _h, 1, GL_RGBA, GL_UNSIGNED_BYTE, _surface->pixels);

  // Set the texture coordinates. A game object can copy these
  // coordinates to refer to this part of the image.
  float idnt_w = .5 / w;
  float idnt_h = .5 / h;
  _coordinates[0] =
      glm::vec3(_position.x / w + idnt_w, (_position.y + _h) / h - idnt_h, _position.z);
  _coordinates[1] =
      glm::vec3((_position.x + _w) / w - idnt_w, (_position.y + _h) / h - idnt_h, _position.z);
  _coordinates[2] =
      glm::vec3((_position.x + _w) / w - idnt_w, _position.y / h + idnt_h, _position.z);
  _coordinates[3] = glm::vec3(_position.x / w + idnt_w, _position.y / h + idnt_h, _position.z);
}

// [] operator to access the texture coordinates. For an image, this
// index will always be 0. [] operator is used because other layer
// objects may have multiple texture coordinates (such as a sprite
// sheet).
const std::array<glm::vec3, 4> &Image::operator[](int i) const {
  if (i > 0) {
    std::cout << "Image::operator[]: index out of bounds.\n";
  }
  return _coordinates;
}
}