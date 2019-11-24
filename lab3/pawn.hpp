#pragma once

#include "king.hpp"

struct Pawn : public King {
        public:
        ~Pawn() {}
        
        Pawn(uint8_t const& x = 1,
             uint8_t const& y = 2);

        bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
