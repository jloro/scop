#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4 vp;
uniform mat4 model;

smooth out vec3 color;

void main()
{
	gl_Position = vp * model * vec4(aPos, 1.0);
	color = aCol;
}
