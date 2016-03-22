#ifndef __HAKUREI_FRAMEWORK__SHADERPROGRAM__
#define __HAKUREI_FRAMEWORK__SHADERPROGRAM__

#include "all.h"

namespace Hakurei
{
    class ShaderProgram
    {
    public:
        Uint32 progID;
        Uint32 vShaderID;
        Uint32 fShaderID;
        std::map<String, Sint32> attributes;
        std::map<String, Sint32> uniforms;

        ShaderProgram(String vShader, String fShader);
        void getAttributes();
        void setUniform(const String uniName, const Uint32 val);
        void setUniform(const String uniName, const Sint32 val);
        void setUniform(const String uniName, const float val);
        void setUniform(const String uniName, const double val);
        void setUniform(const String uniName, const Vec2f& val);
        void setUniform(const String uniName, const Vec3f& val);
        void setUniform(const String uniName, const Vec4f& val);
        void setUniform(const String uniName, const glm::mat2& val, bool transpose = false);
        void setUniform(const String uniName, const glm::mat3& val, bool transpose = false);
        void setUniform(const String uniName, const glm::mat4& val, bool transpose = false);
        bool hasUniform(const String uniName);
    };
}

Uint8* fileContents(const char *srcf, Uint32* length);

#endif



