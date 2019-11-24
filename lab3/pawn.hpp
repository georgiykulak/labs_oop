#pragma once

#include "king.hpp"

struct Pawn : public King {
        public:
        ~Pawn() {}
        
        Pawn(uint8_t const& x = 1,
                uint8_t const& y = 2)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(1, 2);
        }

        bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return ((2 == getY() && 4 == y) ||
                        (7 == getY() && 5 == y)) &&
                         x == getX();
        }
};
