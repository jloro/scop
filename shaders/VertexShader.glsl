#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 vp;
uniform mat4 model;
uniform mat4 transform;

out vec3 color;

void main()
{
	gl_Position = model * vp * transform *  vec4(aPos, 1.0);
	color = aPos;
}
