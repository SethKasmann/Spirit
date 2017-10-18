#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <array>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "glm.hpp"

namespace spirit {

    // The layer interface is a 2D image within a 3D texture. The location of
    // the layer is the z value within the texture.
    class Layer
    {
    public:
        Layer();
        Layer(std::string file);
        const std::string& get_file() const;
        int get_w() const;
        int get_h() const;
        virtual void load() = 0;
        virtual void free() = 0;
        virtual void generate(int w, int h, int z) = 0;
        virtual const std::array<glm::vec3, 4>& operator[](int i) const = 0;
    protected:
        glm::vec3 _position;
        int _w, _h;
        std::string _file;
    };

}

#endif