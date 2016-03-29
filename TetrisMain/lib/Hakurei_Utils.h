#ifndef __HAKUREI_FRAMEWORK__UTILS__
#define __HAKUREI_FRAMEWORK__UTILS__

#include "all.h"

#define BUFF_SIZE       1024

// init and exit
void init_GLFW(void);
void init_GLEW(void);
void GL_Initialization(void);
void shutDown(int return_code);
void exitOnError(String error);

#include "Hakurei_ShaderProgram.h"
#include "Hakurei_Texture.h"
#include "Hakurei_Material.h"
#include "Hakurei_Mesh.h"
#include "Hakurei_KeyHandler.h"
#include "Hakurei_OpenCamera.h"
#include "Hakurei_OpenScene.h"

// Drawing routines
Hakurei::OpenScene* getScene();
void enableThings();
void disableThings();
void swapBuffers();
void updateStuff();
Sint32 fixedMod(Sint32 x, Sint32 n);
void setCallback(GLenum key, KeyCallback func);
void unsetCallback(GLenum key);
float FrameRate(float limit = 0);

#endif


