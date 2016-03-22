#version 410

in vec3 position;
in vec3 normal;
in vec2 uv;
in vec4 color;

out vec4 pposition;
out vec3 pnormal;
out vec2 puv;
out vec4 pcolor;

uniform mat4 mvp;
uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
// light properties
uniform vec3 lightdir;
uniform vec3 lightcolor;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;


void main()
{
    gl_Position = mvp * transformMatrix * vec4(position,1);
    pposition = viewMatrix * transformMatrix * vec4(position,1);
    pnormal = normalize(normalMatrix * mat3(transformMatrix) * normal);
    pcolor = color;
    puv = uv;
}


