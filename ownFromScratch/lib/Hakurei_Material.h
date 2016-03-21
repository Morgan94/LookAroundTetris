#ifndef __HAKUREI_FRAMEWORK__MATERIAL__
#define __HAKUREI_FRAMEWORK__MATERIAL__

#include "all.h"

namespace Hakurei
{
    class Material
    {
    public:
        Hakurei::ShaderProgram* prog;
        Bool useTexture;
        Hakurei::Texture* texture;

        Material(String vShader, String fShader);
        void addTexture(Hakurei::Texture* _texture);
    };
}

#endif


