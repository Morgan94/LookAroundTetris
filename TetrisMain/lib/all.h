#ifndef __HAKUREI_FRAMEWORK__ALL__
#define __HAKUREI_FRAMEWORK__ALL__

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


// Normalized types //
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

// Screen dimensions //
#define SCREEN_W                1024
#define SCREEN_H                800
#define TITLE                   "My Own OpenGL Program"
#define PATH_RESOURCES          "../resources/"

// Attributes //
#define ATTRIB_POSITION         "position"
#define ATTRIB_NORMAL           "normal"
#define ATTRIB_TANGENT          "tangent"
#define ATTRIB_UV               "uv"
#define ATTRIB_COLOR            "color"

// Mesh transforms //
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


// Class definitions //
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
    class ShaderProgram;
    class Texture;
    class Material;
    class Mesh;
    class KeyHandler;
    class OpenCamera;
    class OpenScene;
}


#ifndef USE_FRAMEWORK__HAKUREI
    #define NO_PERMISSION   exitOnError("Oops, it seems you're not allowed to use this framework. Take it easy.");
#else
    #define NO_PERMISSION
#endif

#include "Hakurei_Utils.h"
/*#include "Hakurei_ShaderProgram.h"
#include "Hakurei_Texture.h"
#include "Hakurei_Material.h"
#include "Hakurei_Mesh.h"
#include "Hakurei_KeyHandler.h"
#include "Hakurei_OpenCamera.h"
#include "Hakurei_OpenScene.h"*/


#endif

