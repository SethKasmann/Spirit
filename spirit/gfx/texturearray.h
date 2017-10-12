#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <algorithm>
#include "SDL2/SDL_image.h"

namespace spirit {

    class TextureArray
    {
    private:
        void _add_layer(std::string& file, int level);
    public:
        TextureArray(GLsizei w, GLsizei h);
        ~TextureArray();
        void insert(std::string file);
        void generate_texture(int mipmap_count=1);
        void bind();
        void unbind();
    private:
        std::vector<std::string> _file_paths;
        int _mipmap_count;
        GLsizei _w, _h, _size;
        GLuint _texture;
        SDL_Surface* _image;
    };

}

#endif