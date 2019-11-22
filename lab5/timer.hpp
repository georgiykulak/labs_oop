#pragma once

#define DEF_TIMER

class Timer {
        public:
        ~Timer();
        Timer();
        Timer(Timer const&);
        Timer& operator= (Timer const&);
};
