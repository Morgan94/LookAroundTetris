#ifndef __TP_BRAEM_OPEN_GL_FRAMEWORK__
#define __TP_BRAEM_OPEN_GL_FRAMEWORK__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stack>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <math.h>
#ifndef PI
    #define PI  3.14159265359
#endif


typedef bool            Bool;
typedef std::string     String;
typedef glm::vec2       Vec2f;
typedef glm::vec3       Vec3f;
typedef glm::vec4       Vec4f;
typedef GLubyte         Uint8;
typedef GLbyte          Sint8;
typedef GLushort        Uint16;
typedef GLshort         Sint16;
typedef GLuint          Uint32;
typedef GLint           Sint32;
typedef GLulong         Uint64;
typedef long            Sint64;
#define Vector          std::vector
#define Map             std::map
#ifdef __linux__
    #define COUT                std::cout << "\033[0m"
    #define CERR                std::cerr << "\033[0;31m"
    #define ENDL                "\033[0m" << std::endl
#else
    #define COUT                std::cout
    #define CERR                std::cerr
    #define ENDL                std::endl
#endif


#define SCREEN_W            1024
#define SCREEN_H            800
#define TITLE               "My Own OpenGL Program"
#define PATH_RESOURCES          "../resources/"

// ATTRIBUTES NAME //
#define ATTRIB_POSITION         "position"
#define ATTRIB_NORMAL           "normal"
#define ATTRIB_TANGENT          "tangent"
#define ATTRIB_UV               "uv"
#define ATTRIB_COLOR            "color"

// mesh transforms //
#define NO_TRANSFORM                0
#define SET_TRANSFORM               1
#define SET_TRANSFORM_AS_DEFAULT    2
#define DEFAULT_TRANSFORM           3
#define TRANSFORM_TRANSLATION       0
#define TRANSFORM_ROTATION          1
#define TRANSFORM_SCALE             2
#define TRANSFORM_ALL               3

// Keys //
#define GLFW_KEYS                   350
#define KEY_PRESSED(K)              getScene()->kh->pressed(K)
#define KEY_UPDATE                  getScene()->kh->update()
#define KEY_RESET                   getScene()->kh->resetKeyState()

// Camera //
#define CAMERA_UPDATE               getScene()->camera->moveCameraFromInputs(); getScene()->updateCamera()



void shutDown(int return_code);
void exitOnError(String error);
void init_GLFW(void);
void init_GLEW(void);
void GL_Initialization(void);

namespace Hakurei
{
    class Vertex
    {
    public:
        Vec3f position;
        Vec3f normal;
        Vec3f tangent;
        Vec2f uv;
        Vec4f color;

        Vertex( const Vec3f& p = Vec3f(),
                const Vec3f& n = Vec3f(),
                const Vec3f& t = Vec3f(0,0,0),
                const Vec2f& u = Vec2f(),
                const Vec4f& c = Vec4f(1,1,1,1)) :
                position(p),
                normal(n),
                tangent(t),
                uv(u),
                color(c) {}
    };



    class Triangle
    {
    public:
        Uint32 i0;
        Uint32 i1;
        Uint32 i2;

        Triangle( Uint32 _i0 = 0, Uint32 _i1 = 0, Uint32 _i2 = 0)
        {
            i0 = _i0;
            i1 = _i1;
            i2 = _i2;
        }
    };



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



    class Material
    {
    public:
        Hakurei::ShaderProgram* prog;
        Bool useTexture;
        Hakurei::Texture* texture;

        Material(String vShader, String fShader);
        void addTexture(Hakurei::Texture* _texture);
    };



    class Mesh
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        std::map<String, Uint32> vbos;
        Uint32 ibo;
        Uint32 vao;
        glm::mat4 transformMatrix;
        glm::mat4 defaultMatrix;

        // vertices converted to arrays
        float* _P;
        Uint32 length_p;
        float* _N;
        Uint32 length_n;
        float* _T;
        Uint32 length_t;
        float* _U;
        Uint32 length_u;
        float* _C;
        Uint32 length_c;
        Uint32* _I;
        Uint32 length_i;

        Mesh();
        void computeNormals();
        void getPositions();
        void getNormals();
        void getTangents();
        void getUVs();
        void getColors();
        void getIndexes();
        void createVBO();
        void createIBO();
        void createVAO();
        void transform(Uint8 transformType, Uint8 transformAction = NO_TRANSFORM, Vec3f v = Vec3f(), float angle = 0);
        void resetObjectTransform();
        void setObjectTransformAsDefault();
        Bool importOBJ(String OBJfile);
        //void objData(); <-- for debug purpose
    };



    class KeyHandler
    {
    public:
        Bool key[GLFW_KEYS];
        Bool keyRepeat;

        KeyHandler(Bool _keyRepeat = false);
        void enableKeyRepeat();
        void disableKeyRepeat();
        void update();
        Bool pressed(Sint32 k);
        void resetKeyState();
    };



    class OpenCamera
    {
    public:
        Vec3f position;
        float FoV; // radians
        float angleH; // radians
        float angleV; // radians
        float camSpeed;
        float angleSpeed;
        double mouseX;
        double mouseY;
        // automatically updated
        Vec3f direction;
        Vec3f rightvector;
        Vec3f upvector;

        OpenCamera();
        void moveCameraFromInputs();
    };



    class OpenScene
    {
    public:
        Map<String, Mesh*> objects;
        Map<String, Material*> materials;
        // matrices
        glm::mat4 MVP;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat3 normalMatrix;
        // camera
        Hakurei::OpenCamera* camera;
        // light stuff
        Vec3f lightdir;
        Vec3f lightcolor;
        Vec3f ambient;
        Vec3f diffuse;
        Vec3f specular;
        float shininess;
        // key handler
        Hakurei::KeyHandler* kh;
        // used texture unit
        Uint32 textureUnit;

        OpenScene();
        Hakurei::Mesh* getObjectByName(String objName);
        Hakurei::Material* getMaterialByName(String matName);
        void updateCamera();
        void addMaterial(String mat_name, Hakurei::Material* material);
        void removeMaterial(String mat_name);
        void addObject(String obj_name, Hakurei::Mesh* object);
        void removeObject(String obj_name);
        void drawObject(String objName, String matName);
        void drawObjectInScene(String object, String material);
        void updateProgramUniforms(ShaderProgram *prog, Mesh *obj, Material *mat);
        void resetTransforms();
        void initDrawingScene();
    };
}


Sint16 le_short(Uint8 *bytes);
size_t freadAt(void* buffer, size_t s1, size_t s2, FILE* f, Uint8 offset);
Uint32 getFileSize(FILE* f);
#define BUFF_SIZE       1024
Uint8* fileContents(const char *srcf, Uint32* length);

Hakurei::OpenScene* getScene();

void enableThings();
void disableThings();
void drawObjectInScene(Hakurei::OpenScene* scene, String object, String material, Bool textured /* + text parameters */);
void swapBuffers();
void updateStuff();

#endif
