#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include <GL/glew.h>
#include <iostream>
#include "glm.hpp"

namespace spirit {

    class Texture
    {
    public:
        Texture(const char* filename);
        void bind() const;
        void unbind() const;
        float get_w() const;
        float get_h() const;
        GLuint get_id() const;
        friend std::ostream& operator<<(std::ostream& o, const Texture& t);
    private:
        int _w, _h;
        GLuint _id;
        SDL_Surface* _image;
    };

}

#endif