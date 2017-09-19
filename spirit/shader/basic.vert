#version 330 core
layout (location = 0) in vec4 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform mat4 ortho = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);

void main()
{
    gl_Position = aPos * ortho * vw_matrix;
    ourColor = aColor; // set the output variable to a dark-red color
}