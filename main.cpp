/* Spirit game engine test file */

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "window.h"
#include "vec.h"
#include "matrix.h"
#include "misc.h"
#include "shader.h"
#include <cmath>

int main()
{
    spirit::Window window("Test", 600, 600);
    bool quit = false;

    spirit::Shader shader("spirit/shader/basic.vert", "spirit/shader/basic.frag");

    float vertices[] = {
        // positions         // colors
         -1, -1, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        0, 1, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         1,  -1, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    shader.enable();
    float r = 0.0;
    while (!window.closed())
    {
        if (r == 360)
            r = 0;
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        window.clear();
        spirit::mat4 mat(1);
        mat.orthographic(-1, 1, -1, 1, -1, 1);
        spirit::mat4 mat2(1);
        mat2.rotation(r, spirit::vec3(0, 0, 1));
        //glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), "ortho"), 1, GL_FALSE, *mat);
        glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), "vw_matrix"), 1, GL_FALSE, *mat2);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.update();
        r += .1;
    }

    return 0;
}