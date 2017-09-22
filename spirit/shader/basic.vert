#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 color;

out vec4 out_color;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
	out_color = color;
    gl_Position = pr_matrix * vec4(aPos, 1.0);
}