#version 410

in vec3 position;
in vec4 color;

out vec4 pcolor;

void main()
{
	gl_Position = vec4(position,1);
	pcolor = color;
}
