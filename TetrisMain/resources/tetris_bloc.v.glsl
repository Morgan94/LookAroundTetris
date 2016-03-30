#version 410

in vec3 position;
in vec2 uv;

out vec2 puv;

uniform mat4 mvp;
uniform mat4 transformMatrix;

void main()
{
	gl_Position = mvp * transformMatrix * vec4(position,1);
	puv = uv;
}
