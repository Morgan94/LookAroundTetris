#version 410

in vec4 pcolor;
in vec2 puv;

out vec4 fragColor;

uniform sampler2D colormap;
uniform float alpha;

void main()
{
	fragColor = texture(colormap,puv);
	fragColor.a = alpha;
}

