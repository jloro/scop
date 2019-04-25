#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 vp;
uniform mat4 model;
uniform int f;
uniform int texOn;

smooth out vec3 s_color;
flat out vec3 f_color;
flat out int tex;
flat out int is_flat;
out vec3 pos;

void main()
{
	gl_Position = vp * model * vec4(aPos, 1.0);
	s_color = aCol;
	f_color = aCol;
	tex = texOn;
	pos = aPos;
    is_flat = f;
}
