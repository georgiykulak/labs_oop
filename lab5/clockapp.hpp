#include <iostream>
#include "watch.hpp"

namespace app
{
        bool watch      = false;
        bool timer      = false;
        bool stopwatch  = false;
        bool worldwatch = false;
        bool pomadoro   = false;
}

#if defined(DEF_WATCH)
        app::watch      = true;
#endif

#if defined(DEF_TIMER)
        app::timer      = true;
#endif

#if defined(DEF_STOPWATCH)
        app::stopwatch  = true;
#endif

#if defined(DEF_WORLDWATCH)
        app::worldwatch = true;
#endif

#if defined(DEF_POMADORO)
        app::pomadoro   = true;
#endif
