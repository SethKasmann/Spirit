/* Spirit game engine test file */

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "window.h"
#include "misc.h"
#include "shader.h"
#include "buffer.h"
#include "vertexarray.h"
#include "fpscounter.h"
#include "object2d.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "renderer2d.h"
#include "batch.h"
#include "texture.h"
#include "texturearray.h"
#include <cmath>
#include <vector>
#include <memory>
#include <string>


int main()
{
    //srand(time(NULL));
    spirit::Window window("Test", 960, 540);

    spirit::Shader shader("spirit/shader/basic.vert", "spirit/shader/basic.frag");

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE0);

    spirit::TextureArray textures(416, 64);
    textures.insert("spirit/image/bomb1.png", "bomb1", 1);
    textures.insert("spirit/image/bomb0.png", "bomb0", 1);
    textures.generate_texture();

    std::vector<spirit::Object2d> sprites;

    for (int i = 0; i < 540; i += 64)
    {
        switch (rand() % 2)
        {
            case 0:
                sprites.push_back(spirit::Object2d(glm::vec3(0, i, 0), glm::vec2(416, 64), textures, "bomb1"));
                break;
            case 1:
                sprites.push_back(spirit::Object2d(glm::vec3(0, i, 0), glm::vec2(416, 64), textures, "bomb0"));
                break;
        }
    }

    spirit::Batch batch(&shader, &textures, glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));
    for (auto& e : sprites)
    {
        batch.push(&e);
    }

    int x, y;

    spirit::FPSCounter fps;
    while (!window.closed())
    {
        window.mouse_position(&x, &y);
        shader.enable();
        textures.bind();
        shader.set_vec2("light_position", glm::vec2(x * 960.0f / window.get_w(), 540.0f - y * 540.0f / window.get_h()));
        window.clear();
        batch.render();
        
        window.update();
        
        if (fps.update())
            std::cout << fps << '\n';

        int error = glGetError();
        if (error)
            std::cout << "GL ERROR: " << error << '\n';
            
    }

    return 0;
}