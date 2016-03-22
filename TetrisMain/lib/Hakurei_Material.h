#ifndef __HAKUREI_FRAMEWORK__MATERIAL__
#define __HAKUREI_FRAMEWORK__MATERIAL__

#include "all.h"

#define DEFAULT_COLOR_SAMPLER       "colormap"

namespace Hakurei
{
    class Material
    {
    public:
        Hakurei::ShaderProgram* prog;
        Bool useTexture;
        String colorSampler;
        Hakurei::Texture* texture;
        float alpha;


        Material(String vShader, String fShader, String colorSamplerName = DEFAULT_COLOR_SAMPLER);
        String setSamplerUniform(String samplerName, String fShader);
        void setAlpha(float a);
        void addTexture(Hakurei::Texture* _texture);
    };
}

#endif


