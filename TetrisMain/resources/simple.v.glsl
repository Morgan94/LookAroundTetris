#version 410

in vec3 position;
in vec4 color;

out vec4 pcolor;

uniform mat4 mvp;
uniform mat4 transformMatrix;

void main()
{
	gl_Position = mvp * transformMatrix * vec4(position,1);
	pcolor = color;
}
