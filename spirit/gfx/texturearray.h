#ifndef TEXTUREARRAY_H
#define TEXTUREARRAY_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <algorithm>
#include <unordered_map>
#include "SDL2/SDL_image.h"

namespace spirit {

    // Class to keep track of a layer of a 3D texture.
    class Layer
    {
    public:
        Layer()
        : _num_layers(0), _location(0)
        { }
        Layer(std::string& file, int num_layers, int location)
        : _file(file), _num_layers(num_layers), _location(location)
        { }
        ~Layer() 
        { }
        const std::string& get_file() const { return _file; }
        int get_location() const { return _location; }
        int get_count() const { return _num_layers; }
    private:
        std::string _file;
        int _location;
        int _num_layers;
    };

    class TextureArray
    {
    private:
        void _add_layer(Layer& layer);
    public:
        TextureArray();
        TextureArray(GLsizei w, GLsizei h);
        ~TextureArray();
        void insert(std::string file, std::string key, int num_layers=1);
        void generate_texture(int mipmap_count=1);
        void bind();
        void unbind();
        const int operator[](std::string key)
        {
            return _layer_map[key];
        }
        GLsizei get_w() const
        {
            return _w;
        }
        GLsizei get_h() const
        {
            return _h;
        }
        int get_id() const
        {
            return _id;
        }
    private:
        std::vector<Layer> _layers;
        std::unordered_map<std::string, int> _layer_map; 
        int _mipmap_count;
        GLsizei _w, _h, _size;
        GLuint _texture;
        SDL_Surface* _image;
        int _id;
        static std::array<bool, 32> _texture_slots;
    };
}

#endif