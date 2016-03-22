#version 410

in vec3 position;
in vec4 color;
in vec2 uv;

out vec4 pcolor;
out vec2 puv;

uniform mat4 mvp;
uniform mat4 transformMatrix;

void main()
{
	gl_Position = mvp * transformMatrix * vec4(position,1);
	pcolor = color;
	puv = uv;
}
