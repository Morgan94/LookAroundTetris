#include "Hakurei_KeyHandler.h"


Hakurei::KeyHandler::KeyHandler(Bool _keyRepeat)
{
    NO_PERMISSION
    for(int i=0; i<GLFW_KEYS; i++)
        key[i] = false;
    keyRepeat = _keyRepeat;
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, GL_TRUE);
}

void Hakurei::KeyHandler::enableKeyRepeat()
{
    keyRepeat = true;
}

void Hakurei::KeyHandler::disableKeyRepeat()
{
    keyRepeat = false;
}

void Hakurei::KeyHandler::update()
{
    static Bool oldContext[GLFW_KEYS]; // used only when keyRepeat is disabled
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
            if(!keyRepeat && oldContext[k])
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


