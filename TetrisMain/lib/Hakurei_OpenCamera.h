#ifndef __HAKUREI_FRAMEWORK__OPENCAMERA__
#define __HAKUREI_FRAMEWORK__OPENCAMERA__

#include "all.h"

namespace Hakurei
{
    class OpenCamera
    {
    public:
        Vec3f position;
        float FoV; // radians
        float angleH; // radians
        float angleV; // radians
        float camSpeed;
        float angleSpeed;
        Bool rotateCameraAroundCenter;
        Vec3f cameraTarget;
        // automatically updated
        Vec3f direction;
        Vec3f rightvector;
        Vec3f upvector;
        // callbacks
        CallbackMap callbacks;


        OpenCamera(Bool defaultCallbacks = false, Bool _rotateCameraAroundCenter = false, Vec3f _cameraTarget = Vec3f(0,0,0));
        void blockCamera();
        void unblockCamera();
        void computeCameraMark();
        void moveCameraFromInputs();
    };
}

// Key callbacks
void RotateUp(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void RotateDown(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void RotateLeft(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void RotateRight(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveForward(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveBackward(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveRight(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveLeft(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveUp(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void MoveDown(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);

#endif



