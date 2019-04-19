#version 400 core
out vec4 FragColor;

smooth in vec3 color;
flat in int tex;
in vec3 pos;

uniform sampler2D myText;

void main()
{
	if (tex == 0)
		FragColor = vec4(color, 1.0f);
	else 
		FragColor = texture(myText, (-pos.zy + vec2(1.0) / 2));
}

