#version 400 core
out vec4 FragColor;

smooth in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0f);
}

