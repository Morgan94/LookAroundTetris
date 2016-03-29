#include "Hakurei_OpenCamera.h"

Hakurei::OpenCamera::OpenCamera(Bool defaultCallbacks, Bool _rotateCameraAroundCenter, Vec3f _cameraTarget)
{
    NO_PERMISSION
    position = Vec3f(0,6,-24);
    FoV = PI / 4.0f;
    angleV = 0;
    angleH = 0;
    camSpeed = 3.0f;
    angleSpeed = 1.5f;
    rotateCameraAroundCenter = _rotateCameraAroundCenter;
    cameraTarget = _cameraTarget;
    callbacks.clear();
    if(defaultCallbacks)
    {
        callbacks[GLFW_KEY_UP] = &RotateUp;
        callbacks[GLFW_KEY_DOWN] = &RotateDown;
        callbacks[GLFW_KEY_LEFT] = &RotateLeft;
        callbacks[GLFW_KEY_RIGHT] = &RotateRight;
        callbacks[GLFW_KEY_W] = &MoveForward;
        callbacks[GLFW_KEY_S] = &MoveBackward;
        callbacks[GLFW_KEY_A] = &MoveLeft;
        callbacks[GLFW_KEY_D] = &MoveRight;
        callbacks[GLFW_KEY_Q] = &MoveUp;
        callbacks[GLFW_KEY_Z] = &MoveDown;
    }
}


// Default Key Callbacks //

void RotateUp(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->angleV -= deltaTime * camera->angleSpeed;
    *rotated = true;
}

void RotateDown(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->angleV += deltaTime * camera->angleSpeed;
    *rotated = true;
}

void RotateLeft(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->angleH -= deltaTime * camera->angleSpeed;
    *rotated = true;
}

void RotateRight(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->angleH += deltaTime * camera->angleSpeed;
    *rotated = true;
}

void MoveForward(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position += camera->direction * deltaTime * camera->camSpeed;
}

void MoveBackward(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position -= camera->direction * deltaTime * camera->camSpeed;
}

void MoveRight(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position += camera->rightvector * deltaTime * camera->camSpeed;
}

void MoveLeft(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position -= camera->rightvector * deltaTime * camera->camSpeed;
}

void MoveUp(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position += camera->upvector * deltaTime * camera->camSpeed;
}

void MoveDown(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->position -= camera->upvector * deltaTime * camera->camSpeed;
}

// ------------------------ //




void Hakurei::OpenCamera::computeCameraMark()
{
    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = Vec3f(  cos(angleV) * sin(angleH),
                        sin(angleV),
                        cos(angleV) * cos(angleH));
    // Right vector
    rightvector = Vec3f(sin(angleH - PI/2.0f),
                        0,
                        cos(angleH - PI/2.0f));
    // Up vector
    upvector = glm::cross(rightvector, direction);
}



void Hakurei::OpenCamera::moveCameraFromInputs()
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);

    Bool rotated = false;
    Vec3f oldDirection = direction;



    typedef CallbackMap::iterator it_kcb;
    for(it_kcb iterator = callbacks.begin(); iterator != callbacks.end(); iterator++)
    {
        if(KEY_PRESSED(iterator->first))
        {
            if(iterator->second != NULL)
            {
                (*iterator->second)(this, deltaTime, &rotated);
                computeCameraMark();
            }
        }
    }
    computeCameraMark(); // must be called at least once


    if(rotated) // move camera around target position (origin for the moment)
    {
        Vec3f distCamCenter = position - cameraTarget;
        double distance = sqrt(distCamCenter[0] * distCamCenter[0] + distCamCenter[1] * distCamCenter[1] + distCamCenter[2] * distCamCenter[2]);
        position += Vec3f(oldDirection - direction) * (float)(distance);
    }
    lastTime = currentTime;
}
