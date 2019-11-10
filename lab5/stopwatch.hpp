#pragma once

class StopWatch {
        public:
        ~StopWatch();
        StopWatch();
        StopWatch(StopWatch const&);
        StopWatch& operator= (StopWatch const&);
};
