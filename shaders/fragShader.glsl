#version 400 core
out vec4 FragColor;

smooth in vec3 s_color;
flat in vec3 f_color;
flat in int tex;
flat in int is_flat;
in vec3 pos;

uniform sampler2D myText;

void main()
{
	if (tex == 0)
		FragColor = vec4(is_flat == 1 ? f_color : s_color, 1.0f);
	else 
		FragColor = texture(myText, (-pos.zy + vec2(1.0) / 2));
}

