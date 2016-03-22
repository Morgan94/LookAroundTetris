#version 410

in vec4 pposition;
in vec3 pnormal;
in vec2 puv;
in vec4 pcolor;

out vec4 fragColor;

uniform float alpha;
uniform int hasTexture;
uniform sampler2D colormap;
uniform sampler2D normalmap;
// light properties
uniform vec3 lightdir;
uniform vec3 lightcolor;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;



vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse)/*{{{*/
{
    /*!todo exercise 1: Implement the diffuse (Lambertian) illumination model*/
    float diff = max(dot(lightdirn, normal), 0.0);
    vec3 diffuse = diff * lightcolor * mydiffuse;
    return diffuse;
}/*}}}*/


vec3 ComputeLightSpecular (const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 eyedirn, const in vec3 myspecular, const in float myshininess) /*{{{*/
{
    /*!todo exercise 3: Implement the specular (Blinn-Phong) illumination model*/
    vec3 H = normalize(lightdirn + eyedirn);
    float spec = max(dot(H, normal), 0.0);
    vec3 specular = pow(spec, myshininess) * lightcolor * myspecular;
    return specular;
}/*}}}*/



void main()
{
    vec3 fragNormal = pnormal;
    //fragNormal = (texture(normalmap,uv).xyz * 2.0 - 1.0); <--- bump mapping
    fragNormal = normalize(fragNormal);

    // compute eye direction
    const vec3 eyepos = vec3(0,0,0);
    vec3 vertexCamera = vec3(pposition);
    vec3 eyedir = normalize(eyepos - vertexCamera);

    // diffuse
    vec3 L_diffuse = ComputeLightLambert(lightdir, lightcolor, fragNormal, diffuse);
    // specular
    vec3 L_specular = ComputeLightSpecular(lightdir, lightcolor, fragNormal, eyedir, specular, shininess);

    if(hasTexture == 1)
        fragColor = vec4(ambient * texture(colormap, puv).rgb + L_diffuse * texture(colormap, puv).rgb + L_specular, alpha);
    else
        fragColor = vec4(ambient * vec3(pcolor) + L_diffuse + L_specular, alpha);
}

