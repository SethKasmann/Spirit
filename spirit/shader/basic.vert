#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 tex_coord;
layout (location = 3) in float tex_id;

out DATA
{
	vec4 color;
	vec4 position;
	vec3 tex_coord;
	float tex_id;
} out_data;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main()
{
    // set out data.
    out_data.position = ml_matrix * vec4(position, 1.0);
    out_data.tex_coord = tex_coord;
	out_data.color = color;
	out_data.tex_id = tex_id;

	// set gl position.
    gl_Position = pr_matrix * ml_matrix * vec4(position, 1.0);
}