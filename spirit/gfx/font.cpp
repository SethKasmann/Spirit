#include "font.h"

namespace spirit {

    Font::Font(std::string file, std::string text, size_t size)
    : SubTexture(file)
    , _text(text)
    , _surface(nullptr)
    , _size(size)
    {
        _color.r = 255;
        _color.g = 255;
        _color.b = 255;
        _color.a = 255;
    }

    Font::~Font()
    {
        free();
    }

    // Convert an Font file into a SDL Surface 
    void Font::load()
    {
        // Create the TTF font.
        TTF_Font* font = TTF_OpenFont(_file.c_str(), _size);
        // Verify the font was created propertly.
        if(font == nullptr) 
        {
            std::cout << "TTF_OpenFont: " << TTF_GetError() << '\n';
        }
        // Create SDL surface.
        _surface = TTF_RenderText_Blended(font, _text.c_str(), _color);

        // Verify the surface was created properly.
        if (_surface == nullptr)
        {
            std::cout << "Font::load: " << _file << " could not be converted to a font.\n"
                      << "Font::load: " << IMG_GetError();
        }

        // Set the w, h of the layer.
        _w = _surface->w;
        _h = _surface->h;
    }

    // Free the SDL surface and close the TTF Font.
    void Font::free()
    {
        if (_surface != nullptr)
        {
            SDL_FreeSurface(_surface);
            _surface = nullptr;
        }
    }

    // Generate the OpenGL Sub Font within the 3D texture.
    void Font::generate(int w, int h)
    {
        // Calculate the position. Z is given based on the layer number,
        // x and y offsets are calculated based on the layer size compared
        // to the 3D texture size.

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                        0,
                        _position.x,
                        _position.y,
                        _position.z,
                        _w,
                        _h,
                        1,
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        _surface->pixels);

        // Set the texture coordinates. A game object can copy these
        // coordinates to refer to this part of the font.
        float idnt_w = .5 / w;
        float idnt_h = .5 / h;
        _coordinates[0] = glm::vec3(_position.x / w + idnt_w, (_position.y + _h) / h - idnt_h, _position.z);
        _coordinates[1] = glm::vec3((_position.x + _w) / w - idnt_w,(_position.y + _h) / h - idnt_h, _position.z);
        _coordinates[2] = glm::vec3((_position.x + _w) / w - idnt_w, _position.y / h + idnt_h, _position.z);
        _coordinates[3] = glm::vec3(_position.x / w + idnt_w, _position.y / h + idnt_h, _position.z); 

        std::cout << "max w, h:" << w << " " << h << '\n';
        std::cout << "my w, h: " << _w << " " << _h << '\n';
        std::cout << _text << '\n';
        for (auto e : _coordinates)
        {
            std::cout << e.x << " " << e.y << " " << e.z << '\n';
        }    
    }

    // [] operator to access the texture coordinates. For an Font, this
    // index will always be 0. [] operator is used because other layer
    // objects may have multiple texture coordinates (such as a sprite
    // sheet).
    const std::array<glm::vec3, 4>& Font::operator[](int i) const
    {
        if (i > 0)
        {
            std::cout << "Font::operator[]: index out of bounds.\n";
        }
        return _coordinates;
    }

}