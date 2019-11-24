#pragma once

#include "chessfigure.hpp"

struct Castle : virtual public ChessFigure {
        public:
        virtual ~Castle() {}
        
        Castle(uint8_t const& x = 1,
               uint8_t const& y = 1);

        virtual bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const;
        
        virtual bool check(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
