#include "texturearray.h"

namespace spirit {

    TextureArray::TextureArray(GLsizei w, GLsizei h)
    : _w(w), _h(h), _size(0), _image(nullptr)
    {
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
    }

    TextureArray::~TextureArray()
    {
        glDeleteTextures(1, &_texture);
    }

    void TextureArray::_add_layer(std::string& file, int level)
    {
        // Create SDL surface. Check to verify the image was loaded properly.
        _image = IMG_Load(file.c_str());

        if (_image == nullptr)
        {
            std::cout << "IMG_Load: " << file << " could not be loaded.\n"
                      << "IMG_Load: " << IMG_GetError();
        }

        int divisor = 1;
        for (int i = 0; i < _mipmap_count; ++i)
        {
            std::cout << "mipmap: " << i << '\n'
                      << "layer : " << level << '\n';
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, // Texture type 
                         i,                      // Mipmap level
                         0,                      // X offset
                         0,                      // Y offset
                         level,                  // Layer offset
                         _w / divisor,           // Width
                         _h / divisor,           // Height
                         1,                      // Layer count
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

    void TextureArray::insert(std::string file)
    {
        _file_paths.push_back(file);
        _size++;
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
        for (std::vector<std::string>::iterator it = _file_paths.begin(); it != _file_paths.end(); ++it)
            _add_layer(*it, std::distance(_file_paths.begin(), it));

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
        glBindTexture(GL_TEXTURE_2D_ARRAY, _texture);
    }

    void TextureArray::unbind()
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

}