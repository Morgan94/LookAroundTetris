#version 410

in vec4 pcolor;
in vec2 puv;

out vec4 fragColor;

uniform sampler2D colormap;

void main()
{
fragColor = texture(colormap,puv);
}

