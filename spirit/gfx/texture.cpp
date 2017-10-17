#include "texture.h"

namespace spirit {

    Texture::Texture()
    : _w(0), _h(0), _size(0), _texture(0), _id(0)
    {
        // Set the GL blend mode.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Initialize SDL Image
        const int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        int init = IMG_Init(flags);
        if ((init & flags) != flags)
        {
            std::cout << "IMG_Init: Failed to initialize required jpg and png support!\n"
                      << "IMG_Init: " << IMG_GetError();
        }

        // Iniitialize SDL TTF
        if(TTF_Init() == -1) 
        {
            std::cout << "TTF_Init: " << TTF_GetError() << '\n';
        }

        // Enable GL Texure for 2D and 3D.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_3D);

        // Set the texture id by finding the next avaliable slot. This
        // ID is the same as the OpenGL texture i.e. GL_TEXTURE0 + _id
        auto it = std::find(_g_slots.begin(), _g_slots.end(), 0);
        if (it == _g_slots.end())
        {
            std::cout << "Texture::Texture() ERROR: _g_slots is full.\n";
        }
        _id = std::distance(_g_slots.begin(), it);
        std::cout << "ID: " << _id << '\n';
    }

    Texture::Texture(std::string file, std::string key) : Texture()
    {

    }

    Texture::~Texture()
    {
        _g_slots[_id] = false;
        glDeleteTextures(1, &_texture);
    }

    void Texture::insert_image(std::string file, std::string key)
    {
        _map[key] = LayerX(file);
        _size++;
    }

    void Texture::insert_font(std::string file, std::string key, int fsize)
    {
        _map[key] = LayerX(file, fsize);
        _size++;
    }

    void Texture::generate()
    {
        // Create all surfaces. Determine the w / h for the texture by finding 
        // the max w and h of all the surfaces.
        for (auto it = _map.begin(); it != _map.end(); ++it)
        {
            it->second.init(std::distance(_map.begin(), it));
            _w = std::max(_w, it->second.w);
            _h = std::max(_h, it->second.h);
        }

        // Generate and bind the texture in OpenGL.
        glGenTextures(1, &_texture);
        bind();

        // Allocate the storage in OpenGL.
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, _w, _h, _size);

        // TODO: add mipmaps

        // Generate each layer. After the layer is generated free the SDL
        // surface. 
        std::cout << "Main W / H: " << _w << " " << _h << '\n';
        for (auto it = _map.begin(); it != _map.end(); ++it)
        {
            it->second.generate(_w, _h);
            it->second.free();
        }

        // Set texture parameters.
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

        // Unbind the texture.
        unbind();
    }

    void Texture::bind()
    {
        glActiveTexture(GL_TEXTURE0 + _id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    const LayerX& Texture::operator[](std::string key)
    {
        // Confirm the key is in the map.
        auto it = _map.find(key);
        if (it == _map.end())
        {
            std::cout << "Texture operator[]: Key " << key 
                      << " not found in map.\n";
        }
        // Return a reference to the layer.
        return it->second;
    }

    GLuint Texture::get_id() const
    {
        return _id;
    }

    GLsizei Texture::get_w() const
    {
        return _w;
    }

    GLsizei Texture::get_h() const
    {
        return _h;
    }

}