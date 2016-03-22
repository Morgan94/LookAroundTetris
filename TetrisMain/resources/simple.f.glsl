#version 410

in vec4 pcolor;
out vec4 fragColor;

uniform float alpha;

void main()
{
    fragColor = pcolor;
    fragColor.a = alpha;
}
