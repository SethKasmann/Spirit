#include "layer.h"

namespace spirit {

    Layer::Layer()
    {}

    Layer::Layer(std::string file)
    : _file(file)
    , _position(glm::vec3(0.0f, 0.0f, 0.0f))
    , _w(0)
    , _h(0)
    {}

    // Get the file path.
    const std::string& Layer::get_file() const
    {
        return _file;
    }

    // Access the w, h of the layer.
    int Layer::get_w() const
    {
        return _w;
    }

    int Layer::get_h() const
    {
        return _h;
    }
}