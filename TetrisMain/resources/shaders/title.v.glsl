#version 410

in vec3 position;
in vec2 uv;

out vec2 puv;

void main()
{
	gl_Position = vec4(position,1);
	puv = uv;
}
