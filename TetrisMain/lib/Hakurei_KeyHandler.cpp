#include "Hakurei_KeyHandler.h"


Hakurei::KeyHandler::KeyHandler(Bool _keyRepeat)
{
    NO_PERMISSION
    for(int i=0; i<GLFW_KEYS; i++)
        key[i] = false;
    if(_keyRepeat)
    {
        for(Uint32 i=0; i<GLFW_KEYS; i++)
            keyRepeat[i] = true;
    }
    else
    {
        for(Uint32 i=0; i<GLFW_KEYS; i++)
            keyRepeat[i] = false;
    }
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, GL_TRUE);
}

void Hakurei::KeyHandler::enableKeyRepeat(Sint32 key)
{
    if(key != -1)
        keyRepeat[key] = true;
    else
    {
        for(Uint32 i=0; i<GLFW_KEYS; i++)
            keyRepeat[i] = true;
    }
}

void Hakurei::KeyHandler::disableKeyRepeat(Sint32 key)
{
    if(key != -1)
        keyRepeat[key] = false;
    else
    {
        for(Uint32 i=0; i<GLFW_KEYS; i++)
            keyRepeat[i] = false;
    }
}

void Hakurei::KeyHandler::update()
{
    static Bool oldContext[GLFW_KEYS];
    static Bool initialized = false;

    if(!initialized)
    {
        for(int k=0; k<GLFW_KEYS; k++)
            oldContext[k] = false;
        initialized = true;
    }

    GLFWwindow* window = glfwGetCurrentContext();
    glfwPollEvents();
    for(int k=0; k<GLFW_KEYS; k++)
    {
        if(glfwGetKey(window,k) == GLFW_PRESS) // key pressed
        {
            if(!keyRepeat[k] && oldContext[k])
            {
                key[k] = false;
            }
            else
            {
                key[k] = true;
                oldContext[k] = true;
            }
        }
        else if(glfwGetKey(window,k) == GLFW_RELEASE) // key released
        {
            key[k] = false;
            oldContext[k] = false;
        }
    }
    return;
}

Bool Hakurei::KeyHandler::pressed(Sint32 k)
{
    return key[k];
}

void Hakurei::KeyHandler::resetKeyState()
{
    for(int i=0; i<GLFW_KEYS; i++)
        key[i] = false;
}


