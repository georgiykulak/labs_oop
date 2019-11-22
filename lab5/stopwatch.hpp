#pragma once

#define DEF_STOPWATCH

class StopWatch {
        public:
        ~StopWatch();
        StopWatch();
        StopWatch(StopWatch const&);
        StopWatch& operator= (StopWatch const&);
};
