#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;
uniform mat4 transform;

out vec3 color;

void main()
{
	gl_Position = mvp * transform * vec4(aPos, 1.0);
	color = aPos;
}
