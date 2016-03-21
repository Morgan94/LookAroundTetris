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
        double mouseX;
        double mouseY;
        // automatically updated
        Vec3f direction;
        Vec3f rightvector;
        Vec3f upvector;

        OpenCamera();
        void moveCameraFromInputs();
    };
}

#endif



