#ifndef __HAKUREI_FRAMEWORK__KEYHANDLER__
#define __HAKUREI_FRAMEWORK__KEYHANDLER__

#include "all.h"

namespace Hakurei
{
    class KeyHandler
    {
    public:
        Bool key[GLFW_KEYS];
        Bool keyRepeat;

        KeyHandler(Bool _keyRepeat = false);
        void enableKeyRepeat();
        void disableKeyRepeat();
        void update();
        Bool pressed(Sint32 k);
        void resetKeyState();
    };
}

#endif



