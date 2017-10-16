#include "texturearray.h"

namespace spirit {

    std::array<bool, 32> TextureArray::_texture_slots = {0};

    TextureArray::TextureArray(GLsizei w, GLsizei h)
    : _w(w), _h(h), _size(0), _image(nullptr)
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

        // Enable GL Texure for 2D and 3D.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_3D);

        for (std::array<bool, 32>::iterator it = _texture_slots.begin(); it != _texture_slots.end(); ++it)
        {
            if (*it == false)
            {
                _id = std::distance(_texture_slots.begin(), it);
                *it = true;
            }
        }

    }

    TextureArray::~TextureArray()
    {
        _texture_slots[_id] = false;
        glDeleteTextures(1, &_texture);
    }

    void TextureArray::_add_layer(Layer& layer)
    {
        // Create SDL surface. Check to verify the image was loaded properly.
        _image = IMG_Load(layer.get_file().c_str());

        if (_image == nullptr)
        {
            std::cout << "IMG_Load: " << layer.get_file() << " could not be loaded.\n"
                      << "IMG_Load: " << IMG_GetError();
        }

        int divisor = 1;
        for (int i = 0; i < _mipmap_count; ++i)
        {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, // Texture type 
                         i,                      // Mipmap level
                         0,                      // X offset
                         0,                      // Y offset
                         layer.get_location(),                  // Layer offset
                         _image->w / divisor,           // Width
                         _image->h / divisor,           // Height
                         layer.get_count(),                      // Layer count
                         GL_RGBA,                // Pixel type
                         GL_UNSIGNED_BYTE,       // Storate type
                         _image->pixels);        // Pixel data

            // Update divisor. Each mipmap gives a new w/h divided by a power of 2.
            divisor <<= 1;
        }

        // Free the surface.
        SDL_FreeSurface(_image);
        _image = nullptr;
    }

    void TextureArray::insert(std::string file, std::string key, int num_layers)
    {
        _layer_map[key] = _size;
        _layers.push_back(Layer(file, num_layers, _size));
        _size += num_layers;
    }

    void TextureArray::generate_texture(int mipmap_count)
    {
        _mipmap_count = mipmap_count;

        // Generate and bind the texture.
        glGenTextures(1, &_texture);
        bind();

        // Allocate the storage
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, _mipmap_count, GL_RGBA8, _w, _h, _size);

        // Add 2D layer to the 3D texture.
        for (std::vector<Layer>::iterator it = _layers.begin(); it != _layers.end(); ++it)
            _add_layer(*it);

        // Set texture parameters.
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

        // Unbind the texture.
        unbind();
    }

    void TextureArray::bind()
    {
        glActiveTexture(GL_TEXTURE0 + _id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
    }

    void TextureArray::unbind()
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

}