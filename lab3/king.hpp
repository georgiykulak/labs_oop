#pragma once

#include "queen.hpp"

struct King : public Queen {
        public:
        virtual ~King() {}
        
        King(uint8_t const& x = 4,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(4, 1);
        }
        
        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return (getX() + 1 == x ||
                        getX() - 1 == x) &&
                       (getY() == y)     ||
                       (getY() + 1 == y ||
                        getY() - 1 == y) &&
                       (getX() == x);
        }

        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX()  &&
                       y != getY()  &&
                       std::abs((int)x - (int)getX())
                       == 1 &&
                       std::abs((int)y - (int)getY())
                       == 1;
        }

        virtual bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return  getY() == y        &&
                        getX() == 4        &&
                       (x == 1 || x == 16) &&
                       (y == 1 || y == 16);
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y)   &&
                      (_cross(x, y)    ||
                       _straight(x, y) ||
                       _special(x, y)  );
        }
};
