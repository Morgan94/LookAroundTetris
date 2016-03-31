#version 410

in vec3 position;
in vec4 color;

out vec4 pcolor;

void main()
{
	position[0] = position[0] / 10.0 - 0.8;
	position[1] = position[1] / 10.0 - 0.8;
	position[2] = 0;
	gl_Position = vec4(position,1);
	pcolor = vec4(1,1,1,1);
}
