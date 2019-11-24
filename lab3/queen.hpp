#pragma once

#include "castle.hpp"
#include "officer.hpp"

struct Queen : public Castle, public Officer {
        public:
        virtual ~Queen() {}
        
        Queen(uint8_t const& x = 5,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(5, 1);
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                      (_cross(x, y)  ||
                       _straight(x, y));
        }
};
