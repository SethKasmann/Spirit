#include "texture.h"

namespace spirit {

Texture::Texture() : _w(0), _h(0), _size(0), _texture(0), _id(0) {
  // Set the GL blend mode.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Initialize SDL Image
  const int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  int init = IMG_Init(flags);
  if ((init & flags) != flags) {
    std::cout
        << "IMG_Init: Failed to initialize required jpg and png support!\n"
        << "IMG_Init: " << IMG_GetError();
  }

  // Iniitialize SDL TTF
  if (TTF_Init() == -1) {
    std::cout << "TTF_Init: " << TTF_GetError() << '\n';
  }

  // Enable GL Texure for 2D and 3D.
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_3D);

  // Set the texture id by finding the next avaliable slot. This
  // ID is the same as the OpenGL texture i.e. GL_TEXTURE0 + _id
  auto it = std::find(_g_slots.begin(), _g_slots.end(), 0);
  if (it == _g_slots.end()) {
    std::cout << "Texture::Texture() ERROR: _g_slots is full.\n";
  }
  _id = std::distance(_g_slots.begin(), it);
}

Texture::Texture(std::string file, std::string key) : Texture() {}

Texture::~Texture() {
  _g_slots[_id] = false;
  glDeleteTextures(1, &_texture);
}

void Texture::insert_image(std::string file, std::string key) {
  _map[key] = std::unique_ptr<SubTexture>(new Image(file));
}

void Texture::insert_font(std::string file, std::string key, size_t size) {
  for (auto &c : _g_characters) {
    _map[key + _tag + c] = std::unique_ptr<SubTexture>(new Font(file, c, size));
  }
}

void Texture::insert_sheet(std::string file, std::string key, const glm::vec4* positions, size_t size)
{
  _map[key] = std::unique_ptr<SubTexture>(new SpriteSheet(file, positions, size));
}

// Algorithm to pack each SubTexture within a 3D Open GL texture
// while minimizing the height as much as possible.
void Texture::fit(
    std::unordered_map<std::string, std::unique_ptr<SubTexture>>::iterator
        begin,
    std::unordered_map<std::string, std::unique_ptr<SubTexture>>::iterator end,
    int x, int y, int z, int w, int h) {
  // Check if the width or height is 0
  if (w == 0 || h == 0)
    return;

  for (; begin != end; ++begin) {
    // Continue if the sub texture has already been placed.
    if (begin->second->get_placed())
      continue;

    if (begin->second->get_w() <= w && begin->second->get_h() <= h) {
      // Set the position and the placed flag of this sub texture.
      // std::cout << x + w - begin->second->get_w() << " " << y + h -
      // begin->second->get_h() << '\n';
      begin->second->set_position(glm::vec3(x + w - begin->second->get_w(),
                                            y + h - begin->second->get_h(), z));
      begin->second->set_placed(true);
      // Recursive call to the left region remaining.
      fit(std::next(begin), end, x, 0, z, w - begin->second->get_w() - 1, h);
      // Recurive call to the upper region remaining.
      fit(std::next(begin), end, x + w - begin->second->get_w() + 1, 0, z,
          begin->second->get_w() - 1, h - begin->second->get_h() - 1);
      break;
    }
  }
  return;
}

void Texture::generate() {
  // Create all surfaces. Determine the w / h for the texture by finding
  // the max w and h of all the surfaces.
  for (auto it = _map.begin(); it != _map.end(); ++it) {
    it->second->load();
    _w = std::max(_w, it->second->get_w());
    _h = std::max(_h, it->second->get_h());
  }

  // Iterate through the map and run the fit function. This will set the
  // location (x, y, z) of each 2D sub texture. It will also determine
  // the height needed for the 3D texture.
  for (auto it = _map.begin(); it != _map.end(); ++it) {
    if (it->second->get_placed())
      continue;

    fit(it, _map.end(), 0, 0, _size, _w, _h);

    ++_size;
  }

  // Generate and bind the texture in OpenGL.
  glGenTextures(1, &_texture);
  bind();

  // Allocate the storage in OpenGL.
  glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, _w, _h, _size);

  // Generate each layer. After the layer is generated free the SDL
  // surface.
  for (auto it = _map.begin(); it != _map.end(); ++it) {
    it->second->generate(_w, _h);
    it->second->free();
  }

  // glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

  // Set texture parameters.
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR /*_MIPMAP_NEAREST*/);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Unbind the texture.
  unbind();
}

void Texture::bind() const {
  glActiveTexture(GL_TEXTURE0 + _id);
  glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
}

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D_ARRAY, 0); }

void Texture::link_to_shader(const Shader& shader)
{
  shader.set_uniform_1i("tex_array", _id);
}

GLuint Texture::get_id() const { return _id; }

GLsizei Texture::get_w() const { return _w; }

GLsizei Texture::get_h() const { return _h; }

const SubTexture &Texture::operator[](std::string key) const {
  // Confirm the key is in the map.
  auto it = _map.find(key);
  if (it == _map.end()) {
    std::cout << "Texture operator[]: Key " << key << " not found in map.\n";
  }
  // Return a reference to the layer.
  return *(it->second);
}
}