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
#include <cmath>

int main()
{
    spirit::FPSCounter fps;
    spirit::Window window("Test", 960, 540);
    spirit::Shader shader("spirit/shader/basic.vert", "spirit/shader/basic.frag");
    spirit::Object2d sprite(glm::vec3(4, 3, 0), glm::vec2(8, 3), glm::vec4(0, 0, 1, 1));

    /*
    GLfloat verticies[] =
    {
        4, 3, 0,
        12, 3, 0,
        4, 6, 0,
        12, 6, 0,
    };

    GLushort indicies[] =
    {
        0, 1, 2, 1, 2, 3
    };
    */

    //spirit::VertexArray vao;
    //spirit::VertexBuffer vbo(verticies, 12, 4);
    //spirit::IndexBuffer ibo(indicies, 6);
    //vao.add_buffer(vbo, 0, 0, 0);

    glm::mat4 ortho = glm::mat4();
    ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    shader.enable();
    shader.set_mat4_fv("pr_matrix", ortho);

    spirit::Renderer2d renderer;

    //shader.set_mat4_fv("ml_matrix", trans);
    while (!window.closed())
    {
        window.clear();
        sprite.draw();
        renderer.bind();
        renderer.push(sprite);
        renderer.unbind();
        renderer.render();
        window.update();
        if (fps.update())
            std::cout << fps << '\n';
    }

    return 0;
}