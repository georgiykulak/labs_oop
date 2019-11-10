#include <iostream>
#include "watch.hpp"

namespace app
{
        bool watch_exist()
        {
                #if defined(DEF_WATCH)
                        return true;
                #else
                        return false;
                #endif
        }

        bool timer_exist()
        {
                #if defined(DEF_TIMER)
                        return true;
                #else
                        return false;
                #endif
        }

        bool stopwatch_exist()
        {
                #if defined(DEF_STOPWATCH)
                        return true;
                #else
                        return false;
                #endif
        }
        
        bool worldwatch_exist()
        {
                #if defined(DEF_WORLDWATCH)
                        return true;
                #else
                        return false;
                #endif
        }
        
        bool pomadoro_exist()
        {
                #if defined(DEF_POMADORO)
                        return true;
                #else
                        return false;
                #endif
        }
}
