#include "Hakurei_OpenCamera.h"

Hakurei::OpenCamera::OpenCamera()
{
    NO_PERMISSION
    position = Vec3f(0,0,5);
    FoV = PI / 4.0f;
    angleV = PI;
    angleH = 0;
    camSpeed = 3.0f;
    angleSpeed = 1.5f;
    mouseX = SCREEN_W/2;
    mouseY = SCREEN_H/2;
    glfwSetCursorPos(glfwGetCurrentContext(), mouseX, mouseY);

}

void Hakurei::OpenCamera::moveCameraFromInputs()
{
    GLFWwindow* window = glfwGetCurrentContext();
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);

    // Get mouse position
    glfwGetCursorPos(window, &mouseX, &mouseY);

    Bool rotated = false;
    Vec3f oldDirection = direction;

    // Rotate up
    if(KEY_PRESSED(GLFW_KEY_UP))
    {
        angleV += deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate down
    if(KEY_PRESSED(GLFW_KEY_DOWN))
    {
        angleV -= deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate left
    if(KEY_PRESSED(GLFW_KEY_LEFT))
    {
        angleH += deltaTime * angleSpeed;
        rotated = true;
    }

    // Rotate right
    if(KEY_PRESSED(GLFW_KEY_RIGHT))
    {
        angleH -= deltaTime * angleSpeed;
        rotated = true;
    }

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

    // Move forward ^
    if(KEY_PRESSED(GLFW_KEY_W))
    {
        position += direction * deltaTime * camSpeed;
    }

    // Move backward v
    if(KEY_PRESSED(GLFW_KEY_S))
    {
        position -= direction * deltaTime * camSpeed;
    }

    // Move right >
    if(KEY_PRESSED(GLFW_KEY_D))
    {
        position += rightvector * deltaTime * camSpeed;
    }

    // Move left <
    if(KEY_PRESSED(GLFW_KEY_A))
    {
        position -= rightvector * deltaTime * camSpeed;
    }

    // Move up ^
    if(KEY_PRESSED(GLFW_KEY_Q))
    {
        position += upvector * deltaTime * camSpeed;
    }

    // Move down v
    if(KEY_PRESSED(GLFW_KEY_Z))
    {
        position -= upvector * deltaTime * camSpeed;
    }

    if(rotated) // move camera around target position
    {
        position += Vec3f(oldDirection - direction) * 5.0f;
    }
    lastTime = currentTime;
}
