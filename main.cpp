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
#include <cmath>
#include <vector>
#include <memory>


int main()
{
    //srand(time(NULL));
    spirit::Window window("Test", 960, 540);

    spirit::Shader shader("spirit/shader/basic.vert", "spirit/shader/basic.frag");

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    spirit::Texture tex("spirit/image/bombtest.png");

    std::vector<spirit::Object2d> sprites;
    for (float i = 0; i < 16.0f; i += 2.6)
    {
        for (float j = 0; j < 9.0f; j += .4)
        {
            if (rand() % 2 == 0)
            {
                sprites.push_back(spirit::Object2d(glm::vec3(i, j, 0), glm::vec2(2.6, .4), 
                glm::vec4(0, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
            }
            else
            {
                sprites.push_back(spirit::Object2d(glm::vec3(i, j, 0), glm::vec2(2.6, .4), 
                &tex));
            }
        }
    }
    spirit::Batch batch(&shader, glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
    for (auto& e : sprites)
    {
       batch.push_back(&e);
    }

    int x, y;
    tex.bind();
    shader.enable();
    shader.set_uniform_1i("tex", 0);
    shader.disable();
    tex.unbind();

    spirit::FPSCounter fps;
    while (!window.closed())
    {
        window.mouse_position(&x, &y);
        shader.enable();
        tex.bind();
        shader.set_vec2("light_position", glm::vec2(x * 16.0f / window.get_w(), 9.0f - y * 9.0f / window.get_h()));
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