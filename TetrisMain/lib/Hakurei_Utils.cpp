#include "Hakurei_Utils.h"


void shutDown(int return_code)
{
    glfwTerminate();
    exit(return_code);
}

void exitOnError(String error)
{
    std::cerr << "Error: " << error << ENDL;
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
        std::cerr << "Could not open a window" << ENDL;
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
        std::cerr << "ERROR: " << glewGetErrorString(GlewInitResult) << ENDL;
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
        scene = new Hakurei::OpenScene();
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
    KEY_UPDATE;
    CAMERA_UPDATE;
}

void enableThings()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void disableThings()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}


