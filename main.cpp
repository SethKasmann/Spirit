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
#include "font.h"
#include "inputhandler.h"
#include <cmath>
#include <vector>
#include <memory>
#include <string>


int main()
{
    spirit::Window window("Test", 960, 540);
    spirit::InputHandler input;
    spirit::Shader shader("spirit/shader/basic.vert", "spirit/shader/basic.frag");

    spirit::Texture texture;
    texture.insert_image("spirit/image/bomb1.png", "bomb1");
    texture.insert_image("spirit/image/bomb0.png", "bomb0");
    texture.insert_image("spirit/image/bomb2.png", "bomb2");
    texture.insert_font("spirit/font/OpenSans.ttf", "sans_test", 30);
    texture.generate();

    spirit::Text text(glm::vec3(0, 0, 0), texture, "sans_test", "hi", 255, 0, 0, 255);

    std::vector<spirit::Object2d> sprites;

    for (int i = 0; i < 960; i += 10)
    {
        for (int j = 0; j < 540; j += 10)
        {
            sprites.push_back(spirit::Object2d(glm::vec3(i, j, 0), 10, 10, texture, "bomb1"));
        }
    }

    spirit::Batch batch(&shader, &texture);
    //spirit::Batch batch2(&shader, &texture, );

    int x, y;

    spirit::FPSCounter fps;
    while (!window.closed())
    {
        //batch.push(&text);
        for (auto& s : sprites)
            batch.push(&s);
        if (input.keydown(SDL_SCANCODE_W))
            window.get_camera().move(0.0f, -0.1f);
        if (input.keydown(SDL_SCANCODE_S))
            window.get_camera().move(0.0f, 0.1f);
        if (input.keydown(SDL_SCANCODE_D))
            window.get_camera().move(-0.1f, 0.0f);
        if (input.keydown(SDL_SCANCODE_A))
            window.get_camera().move(0.1f, 0.0f);

        if (input.keydown(SDL_SCANCODE_EQUALS))
            window.get_camera().zoom(0.01f);
        else if (input.keydown(SDL_SCANCODE_MINUS))
            window.get_camera().zoom(-0.01f);

        batch.set_projection(window.get_camera().get_projection());
        batch.set_modelview(window.get_camera().get_modelview());
        window.mouse_position(&x, &y);
        shader.enable();
        texture.bind();
        shader.set_vec2("light_position", glm::vec2(x * 960.0f / window.get_w(), 540.0f - y * 540.0f / window.get_h()));
        window.clear();
        batch.render();
        
        window.update();
        
        if (fps.update())
        {
            text.set_text(texture, "sans_test", fps.to_string(), 255, 0, 0, 255);
            std::cout << fps.to_string() << '\n';
        }

        int error = glGetError();
        if (error)
            std::cout << "GL ERROR: " << error << '\n';


    }

    return 0;
}