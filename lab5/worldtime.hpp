#pragma once

#define DEF_WORLDWATCH

class WorldWatch {
        public:
        ~WorldWatch();
        WorldWatch();
        WorldWatch(WorldWatch const&);
        WorldWatch& operator= (WorldWatch const&);
};
