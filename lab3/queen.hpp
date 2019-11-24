#pragma once

#include "castle.hpp"
#include "officer.hpp"

struct Queen : public Castle, public Officer {
        public:
        virtual ~Queen() {}
        
        Queen(uint8_t const& x = 5,
              uint8_t const& y = 1);

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
