#ifndef __HAKUREI_FRAMEWORK__TEXTURE__
#define __HAKUREI_FRAMEWORK__TEXTURE__

#include "all.h"

namespace Hakurei
{
    class Texture
    {
    public:
        Uint32 textureID;
        Uint8* pixels;
        Uint32 w;
        Uint32 h;
        Uint32 d;

        // parameters
        GLenum wrapS;
        GLenum wrapT;
        GLenum magF;
        GLenum minF;
        Bool anisotropy;
        //Bool hasMipmaps; <-- always true for the moment

        Texture(const String& imagepath, GLenum wrap_s = GL_REPEAT, GLenum wrap_t = GL_REPEAT,
                GLenum mag_filter = GL_LINEAR, GLenum min_filter = GL_LINEAR, bool aniso = false);
    private:
        void read_TGA(const char *filename);
        void read_BMP(const char *filename);
    };
}

Sint16 le_short(Uint8 *bytes);
size_t freadAt(void* buffer, size_t s1, size_t s2, FILE* f, Uint8 offset);
Uint32 getFileSize(FILE* f);

#endif




