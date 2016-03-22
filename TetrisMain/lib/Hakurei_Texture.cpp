#include "Hakurei_Texture.h"

Sint16 le_short(Uint8 *bytes)
{
    return bytes[0] | ((char)bytes[1] << 8);
}

size_t freadAt(void* buffer, size_t s1, size_t s2, FILE* f, Uint8 offset)
{
    if(offset != 0xFFFFFFFF) fseek(f,offset,SEEK_SET);
    return fread(buffer,s1,s2,f);
}

Uint32 getFileSize(FILE* f)
{
    Uint64 p = ftell(f);
    fseek(f,0,SEEK_END);
    Uint64 s = ftell(f);
    fseek(f,p,SEEK_SET);
    return (Uint32)(s);
}

void Hakurei::Texture::read_TGA(const char *filename)
{
    struct tga_header {
        Sint8  id_length;
        Sint8  color_map_type;
        Sint8  data_type_code;
        Uint8  color_map_origin[2];
        Uint8  color_map_length[2];
        Sint8  color_map_depth;
        Uint8  x_origin[2];
        Uint8  y_origin[2];
        Uint8  width[2];
        Uint8  height[2];
        Sint8  bits_per_pixel;
        Sint8  image_descriptor;
    } header;
    Uint32 i, color_map_size;
    FILE *f;
    size_t read;

    f = fopen(filename, "rb");

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return;
    }

    read = fread(&header, 1, sizeof(header), f);

    if (read != sizeof(header)) {
        fprintf(stderr, "%s has incomplete tga header\n", filename);
        fclose(f);
        return;
    }
    if (header.data_type_code != 2) {
        fprintf(stderr, "%s is not an uncompressed RGB tga file\n", filename);
        fclose(f);
        return;
    }
    if (header.bits_per_pixel != 24 and header.bits_per_pixel != 32) {
        fprintf(stderr, "%s is not a 24-bit or 32-bit uncompressed RGB tga file but %i\n", filename, header.bits_per_pixel);
        fclose(f);
        return;
    }

    for (i = 0; i < header.id_length; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete id string\n", filename);
            fclose(f);
            return;
        }

    color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
    for (i = 0; i < color_map_size; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete color map\n", filename);
            fclose(f);
            return;
        }

    w = le_short(header.width);
    h = le_short(header.height);
    d = (header.bits_per_pixel/8);
    Uint32 pixels_size = w * h * d;
    pixels = new Uint8[pixels_size];

    read = fread(pixels, 1, pixels_size, f);

    if (read != pixels_size) {
        fprintf(stderr, "%s has incomplete image\n", filename);
        delete [] pixels;
    }

    fclose(f);
}

void Hakurei::Texture::read_BMP(const char *filename)
{
    struct bmp_header {
        Uint16 magic;
        Uint32 file_size;
        Uint16 unused1;
        Uint16 unused2;
        Uint32 data_offset;
        Uint32 width;
        Uint32 height;
    } header;

    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return;
    }

    freadAt(&(header.magic), 1, sizeof(unsigned short), f, 0x0);
    freadAt(&(header.file_size), 1, sizeof(unsigned int), f, 0x2);
    freadAt(&(header.unused1), 1, sizeof(unsigned short), f, 0x6);
    freadAt(&(header.unused2), 1, sizeof(unsigned short), f, 0x8);
    freadAt(&(header.data_offset), 1, sizeof(unsigned int), f, 0xA);
    freadAt(&(header.width), 1, sizeof(unsigned int), f, 0x12);
    freadAt(&(header.height), 1, sizeof(unsigned int), f, 0x16);

    if (header.magic != 0x4D42) { // 0x4D42 = BM
        fprintf(stderr, "%s is not a Windows Bitmap file\n", filename);
        fclose(f);
        return;
    }
    if (header.file_size != getFileSize(f)) {
        fprintf(stderr, "%s has not a valid bmp header\n", filename);
        fclose(f);
        return;
    }

    w = header.width;
    h = header.height;

    Uint8* pixels = new unsigned char[w * h * 3];
    Sint32 size_of_row = (w * 3) + (4 - (w * 3) % 4) % 4;
    Uint8 tmp;
    Uint32 row_offset;

    printf("Size of row: %u Bytes\n",size_of_row);

    for(Sint32 j = 0; j < h; j++) {
        row_offset = header.data_offset + j * size_of_row;
        freadAt(&(pixels[j*w*3]), sizeof(Uint8), w*3, f, row_offset);
        for(Sint32 i = 0; i < w; i++) {
            // Swap (B, G, R) to (R, G, B)
            tmp = pixels[(j*w+i)*3];
            pixels[(j*w+i)*3] = pixels[(j*w+i)*3+2];
            pixels[(j*w+i)*3+2] = tmp;
        }
    }

    fclose(f);
}

Hakurei::Texture::Texture(const String &imagepath, GLenum wrap_s, GLenum wrap_t, GLenum mag_filter, GLenum min_filter, bool aniso)
{
    NO_PERMISSION
    pixels = NULL;
    w = 0;
    h = 0;
    d = 0;

    // Loading in CPU
    GLenum format = 0;
    GLenum type = 0;
    String file = PATH_RESOURCES + imagepath;


    if(strstr(imagepath.c_str(),".tga") != NULL)
    {
        read_TGA(file.c_str());
        format = GL_BGR;
        type = GL_UNSIGNED_BYTE;
    }
    else if(strstr(imagepath.c_str(),".bmp") != NULL)
    {
        read_BMP(file.c_str());
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
    }


    // Uploading to GPU
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, type, pixels);

    // Wrapping
    wrapS = wrap_s;
    wrapT = wrap_t;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // Filtering
    magF = mag_filter;
    minF = min_filter;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magF);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minF);

    // Anisotropy
    anisotropy = aniso;
    if(anisotropy)
    {
        GLfloat maxAniso = 0.0F;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,maxAniso);
    }
    else
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0F);
}


