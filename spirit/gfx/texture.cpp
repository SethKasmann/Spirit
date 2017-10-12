#include <string>
#include "texture.h"

namespace spirit {

    Texture::Texture(const char* filename)
    : _id(0), _image(nullptr)
    {
        // Initialize SDL Image
        int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        int init = IMG_Init(flags);
        if ((init & flags) != flags)
        {
            std::cout << "IMG_Init: Failed to initialize required jpg and png support!\n"
                      << "IMG_Init: " << IMG_GetError();
        }

        // Create SDL surface. Check to verify the image was loaded properly.
        _image = IMG_Load(filename);

        if (_image == nullptr)
        {
            std::cout << "IMG_Load: " << filename << " could not be loaded.\n"
                      << "IMG_Load: " << IMG_GetError();
        }

        _w = _image->w;
        _h = _image->h;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &_id);
        bind();

        int mode = GL_RGB;

        if (_image->format->BytesPerPixel == 4)
        {
            if (_image->format->Rmask == 0x000000ff) 
                mode = GL_RGBA;
            else
                mode = GL_BGRA;
        }
        else if (_image->format->BytesPerPixel == 3)
        {
            if (_image->format->Rmask == 0x000000ff) 
                mode = GL_RGB;
            else 
                mode = GL_BGR;
        }
        else
        {
            std::cout << "Texture::Texture: Unsupported pixel format.\n";
        }

        // Give image data to open GL.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, mode, _image->w, _image->h, 0, mode, GL_UNSIGNED_BYTE, _image->pixels);
        unbind();

        // Free SDL surface.
        SDL_FreeSurface(_image);
        _image = nullptr;
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    float Texture::get_w() const
    {
        return _w;
    }

    float Texture::get_h() const
    {
        return _h;
    }

    GLuint Texture::get_id() const
    {
        return _id;
    }

    std::ostream& operator<<(std::ostream& o, const Texture& t)
    {
        if (t._image == nullptr)
        {
            o << "Texture = nullptr\n";
            return o;
        }

        for (int x = 0; x < t.get_w(); ++x)
        {
            o << "X:" << x << '\n';
            for (int y = 0; y < t.get_h(); ++y)
            {
                o << "\tY:" << y << " ";
                int bpp = t._image->format->BytesPerPixel;
                uint8_t* p = static_cast<uint8_t*>(t._image->pixels) + y * t._image->pitch + x * bpp;

                switch(bpp)
                {
                    case 1:
                        o << *p;
                        break;
                    case 2:
                        o << *reinterpret_cast<uint16_t*>(p);
                        break;
                    case 3:
                        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                            o << ((p[0] << 16) | (p[1] << 8) | p[2]);
                        else
                            o << (p[0] | (p[1] << 8) | (p[2] << 16));
                        break;
                    case 4:
                        o << *reinterpret_cast<uint32_t*>(p);
                        break;
                    default:
                        o << "Texture bpp error. Unable to print.\n";
                        break;
                }
                o << '\n';
            }
            //o << '\n';
        }
        return o;
    }

}