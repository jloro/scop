#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 vp;
uniform mat4 model;
uniform int f;
uniform int texOn;
uniform int greyOn;

smooth out vec3 s_color;
flat out vec3 f_color;
flat out int tex;
flat out int is_flat;
out vec3 pos;

void main()
{
	gl_Position = vp * model * vec4(aPos, 1.0);
	float grey = (aCol.x * 0.21 + aCol.y * 0.72 + aCol.z * 0.07) / 2.0f;
	vec3 color;
	if (greyOn == 0)
		color = aCol;
	else
		color = vec3(grey, grey, grey);
	s_color = color;
	f_color = color;
	tex = texOn;
	pos = aPos;
    is_flat = f;
}
