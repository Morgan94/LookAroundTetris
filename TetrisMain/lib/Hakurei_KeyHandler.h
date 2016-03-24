#ifndef __HAKUREI_FRAMEWORK__KEYHANDLER__
#define __HAKUREI_FRAMEWORK__KEYHANDLER__

#include "all.h"

namespace Hakurei
{
    class KeyHandler
    {
    public:
        Bool key[GLFW_KEYS];
        Bool keyRepeat[GLFW_KEYS];

        KeyHandler(Bool _keyRepeat = false);
        void enableKeyRepeat(Sint32 key = -1);
        void disableKeyRepeat(Sint32 key = -1);
        void update();
        Bool pressed(Sint32 k);
        void resetKeyState();
    };
}

#endif



