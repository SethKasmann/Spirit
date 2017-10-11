#version 330 core

//layout (location = 0) out vec4 color;

out vec4 color;

in DATA
{
	vec4 color;
	vec4 position;
	vec2 tex_coord;
	float tex_id;
} out_data;

uniform sampler2D tex;
uniform vec2 light_position;

void main()
{
	//float intensity = 1.0 / length(out_data.position.xy - light_position);
    //color = out_data.color * intensity;
    if (out_data.tex_id > 0.0)
    {
	    color = texture(tex, out_data.tex_coord);
    }
    else
    {
    	color = out_data.color;
    }
}