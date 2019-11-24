#pragma once

#include "queen.hpp"

struct King : public Queen {
        public:
        virtual ~King() {}
        
        King(uint8_t const& x = 4,
             uint8_t const& y = 1);
        
        bool _straight(
                uint8_t const& x,
                uint8_t const& y)
                const;

        bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const;

        virtual bool _special(
                uint8_t const& x,
                uint8_t const& y)
                const;

        bool check(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
