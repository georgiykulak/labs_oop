#pragma once

#include "chessfigure.hpp"

struct Officer : virtual public ChessFigure {
        public:
        virtual ~Officer() {}
        
        Officer(uint8_t const& x = 3,
                uint8_t const& y = 1)
        {
                if ( inField(x, y) ) {
                        setPos(x, y);
                }
                else    setPos(3, 1);
        }

        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x != getX()  &&
                       y != getY()  &&
                       std::abs((int)x - (int)getX()) ==
                       std::abs((int)y - (int)getY());
        }

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return inField(x, y) &&
                       _cross(x, y);
        }
};
