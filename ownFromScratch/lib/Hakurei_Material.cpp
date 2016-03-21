#include "hakurei_Material.h"

Hakurei::Material::Material(String vShader, String fShader)
{
    NO_PERMISSION
    useTexture = false;
    texture = NULL;
    String vertexSh = PATH_RESOURCES + vShader;
    String fragmentSh = PATH_RESOURCES + fShader;
    prog = new ShaderProgram(vertexSh, fragmentSh);
}

void Hakurei::Material::addTexture(Hakurei::Texture* _texture)
{
    texture = _texture;
    if(texture == NULL)
    {
        CERR << "Warning : Texture does not exist." << ENDL;
    }
    useTexture = true;
}

