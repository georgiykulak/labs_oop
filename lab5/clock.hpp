#pragma once

class Clock {
        public:
        ~Clock();
        Clock();
        Clock(Clock const&);
        Clock& operator= (Clock const&);
};
