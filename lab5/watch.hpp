#pragma once

#define DEF_WATCH

class Watch {
        public:
        ~Watch();
        Watch();
        Watch(Watch const&);
        Watch& operator= (Watch const&);
};
