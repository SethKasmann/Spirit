#include "subtexture.h"

namespace spirit {

SubTexture::SubTexture() {}

SubTexture::SubTexture(std::string file)
    : _file(file), _position(glm::vec3(0.0f, 0.0f, 0.0f)), _w(0), _h(0),
      _placed(false) {}

// Get the file path.
const std::string &SubTexture::get_file() const { return _file; }

bool SubTexture::get_placed() const { return _placed; }

void SubTexture::set_placed(bool placed) { _placed = placed; }

void SubTexture::set_position(glm::vec3 position) { _position = position; }

// Access the w, h of the layer.
int SubTexture::get_w() const { return _w; }

int SubTexture::get_h() const { return _h; }
}