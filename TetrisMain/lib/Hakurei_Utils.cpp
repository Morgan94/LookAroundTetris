#include "Hakurei_Utils.h"


void shutDown(int return_code)
{
    glfwTerminate();
    exit(return_code);
}

void exitOnError(String error)
{
    CERR << "Error: " << error << ENDL;
    shutDown(-1);
}

void init_GLFW(void)
{
    /* GLFW initialization */
    const int window_width = SCREEN_W, window_height = SCREEN_H;
    if (!glfwInit())
        shutDown(1);
    // Create OpenGL 3.x Core Profile Context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(window_width, window_height, TITLE, NULL, NULL);
    if(w == NULL)
    {
        CERR << "Could not open a window" << ENDL;
        shutDown(1);
    }
    glfwMakeContextCurrent(w);
    return;
}

void init_GLEW(void)
{
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        CERR << "ERROR: " << glewGetErrorString(GlewInitResult) << ENDL;
        shutDown(1);
    }
    return;
}

void GL_Initialization(void)
{
    init_GLFW();
    init_GLEW();
    COUT << "OpenGL version: " << glGetString(GL_VERSION) << ENDL;
    COUT << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << ENDL;
    return;
}

Hakurei::OpenScene* getScene()
{
    static Hakurei::OpenScene* scene = NULL;

    if(scene == NULL) {
        scene = new Hakurei::OpenScene(false);
    }
    return scene;
}

void swapBuffers()
{
    GLFWwindow* w = glfwGetCurrentContext();
    glfwSwapBuffers(w);
}

void updateStuff()
{
    FrameRate(30);
    KEY_UPDATE;
    //CAMERA_UPDATE;
    getScene()->initDrawingScene();
}

void enableThings()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void disableThings()
{
    //glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}

Sint32 fixedMod(Sint32 x, Sint32 n)
{
    if(n <= 0)
        return 0;
    Sint32 out = x % n;
    while(out < 0) out += n;
    return out;
}

void setCallback(GLenum key, KeyCallback func)
{
    getScene()->camera->callbacks[key] = func;
    return;
}

void unsetCallback(GLenum key)
{
    getScene()->camera->callbacks[key] = NULL;
    return;
}


float FrameRate(float limit)
{
    static float last = 0;
    if(limit > 0)
    {
        float sleepTime = (1.0 / limit) - (glfwGetTime() - last);
        if(sleepTime > 0) usleep((Uint32)(sleepTime * 1000000));
    }
    float fps = 1.0 / (glfwGetTime() - last);
    last = glfwGetTime();
    return fps;
}

Uint32 RandomGen()
{
    Uint32 blocType = rand() % 7;
    return blocType;
}






