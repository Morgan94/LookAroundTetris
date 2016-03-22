#include "hakurei_Material.h"

Hakurei::Material::Material(String vShader, String fShader, String colorSamplerName)
{
    NO_PERMISSION
    useTexture = false;
    texture = NULL;
    colorSampler = colorSamplerName;
    alpha = 1;
    String vertexSh = PATH_RESOURCES + vShader;
    String fragmentSh = setSamplerUniform(colorSampler, PATH_RESOURCES + fShader);
    prog = new ShaderProgram(vertexSh, fragmentSh);
    remove(fragmentSh.c_str());
}


String Hakurei::Material::setSamplerUniform(String samplerName, String fShader)
{
    String newfShader = fShader + ".fsh";
    Bool edit = true;

    FILE* src = fopen(fShader.c_str(),"r");
    if(src == NULL)
    {
        CERR << "Error : Fragment Shader file " + fShader + " not found." << ENDL;
        return "";
    }
    FILE* dst = fopen(newfShader.c_str(),"w");
    if(dst == NULL)
    {
        CERR << "Error : Cannot create new shader file." << ENDL;
        fclose(src);
        return "";
    }
    if(samplerName.find(DEFAULT_COLOR_SAMPLER) != String::npos)
    {
        CERR << "Warning : samplerName contains default sampler name. Default sampler name will be used instead." << ENDL;
        edit = false;
    }

    char cbuffer[256];
    String buffer;
    Sint32 pos;
    while(fgets(cbuffer,256,src) != NULL)
    {
        buffer = String(cbuffer);
        if(edit)
        {
            while((pos = buffer.find(DEFAULT_COLOR_SAMPLER)) != String::npos)
            {
                String left = buffer.substr(0,pos);
                String right = buffer.substr(pos+8);
                buffer = left + samplerName + right;
            }
        }
        fprintf(dst,"%s",buffer.c_str());
    }

    fclose(src);
    fclose(dst);
    return newfShader;
}


void Hakurei::Material::setAlpha(float a)
{
    if(a < 0 || a > 1)
        return;
    alpha = a;
}


void Hakurei::Material::addTexture(Hakurei::Texture* _texture)
{
    texture = _texture;
    if(texture == NULL)
    {
        CERR << "Warning : Texture does not exist." << ENDL;
    }
    if(colorSampler.size() == 0)
    {
        CERR << "Warning : Trying to use texture without colorSampler." << ENDL;
    }
    useTexture = true;
}

