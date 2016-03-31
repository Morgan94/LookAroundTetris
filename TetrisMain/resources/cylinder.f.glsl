#version 410

in vec4 pcolor;

out vec4 fragColor;

void main()
{
    fragColor = pcolor;
    fragColor.a = 0.05;
}
