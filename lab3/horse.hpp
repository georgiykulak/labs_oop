#pragma once

#include "officer.hpp"

struct Horse : public Officer {
        public:
        ~Horse() {}
        
        Horse(uint8_t const& x = 2,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(2, 1);
        }

        bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX() &&
                       y != getY() &&
                       //horizontal comparing
                      (getX() + 2 == x &&
                       getY() + 1 == y) ||
                      (getX() + 2 == x &&
                       getY() - 1 == y) ||
                      (getX() - 2 == x &&
                       getY() + 1 == y) ||
                      (getX() - 2 == x &&
                       getY() - 1 == y) ||
                       //vertical comparing
                      (getY() + 2 == y &&
                       getX() + 1 == x) ||
                      (getY() + 2 == y &&
                       getX() - 1 == x) ||
                      (getY() - 2 == y &&
                       getX() + 1 == x) ||
                      (getY() - 2 == y &&
                       getX() - 1 == x);
        }
};
