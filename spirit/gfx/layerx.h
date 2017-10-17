#ifndef LAYERX_H
#define LAYERX_H

#include <string>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

namespace spirit {

    class LayerX
    {
    public:
        LayerX()
        {}
        LayerX(std::string file)
        : _file(file)
        , _surface(nullptr)
        , _font(nullptr)
        , _fsize(0)
        {}
        LayerX(std::string file, int fsize)
        : _file(file)
        , _surface(nullptr)
        , _font(nullptr)
        , _fsize(fsize)
        {}
        void init(int offset_z)
        {
            // Set the layer offset.
            z = offset_z;
            
            // Create SDL surface. Check to verify the image was loaded properly.
            _surface = IMG_Load(_file.c_str());

            if (_surface == nullptr)
            {
                std::cout << "IMG_Load: " << _file << " could not be loaded.\n"
                          << "IMG_Load: " << IMG_GetError();
            }

            w = _surface->w;
            h = _surface->h;

            std::cout << "setting w / h:" << w << " " << h << '\n';
        }
        void free()
        {
            if (_surface != nullptr)
            {
                SDL_FreeSurface(_surface);
                _surface = nullptr;
            }
        }
        void generate(int tex_w, int tex_h)
        {
            // Set x / y offsets.
            x = tex_w - w;
            y = tex_h - h;

            std::cout << "Generating a layer.\n";
            std::cout << "x: " << x << " y: " << y << " z: " << z << '\n';

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                            0,
                            x,
                            y,
                            z,
                            w,
                            h,
                            1,
                            GL_RGBA,
                            GL_UNSIGNED_BYTE,
                            _surface->pixels);
        }
        int x, y, z, w, h;
    private:
        std::string _file;
        SDL_Surface* _surface;
        TTF_Font* _font;
        int _fsize;
    };

}

#endif