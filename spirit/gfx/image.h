#ifndef IMAGE_H
#define IMAGE_H

#include "layer.h"

namespace spirit {

    // Class to load a 2D image as a layer. This will generate a sub image (2D)
    // within a texture object (3D).
    class Image : public Layer
    {
    public:
        Image(std::string file);
        ~Image();
        void load();
        void free();
        void generate(int w, int h, int z);
        const std::array<glm::vec3, 4>& operator[](int i) const;
    private:
        std::array<glm::vec3, 4> _coordinates;
        SDL_Surface* _surface;
    };

}

#endif