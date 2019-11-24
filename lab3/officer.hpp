#pragma once

#include "chessfigure.hpp"

struct Officer : virtual public ChessFigure {
        public:
        virtual ~Officer() {}
        
        Officer(uint8_t const& x = 3,
                uint8_t const& y = 1);

        virtual bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const;

        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
