#pragma once

#include "officer.hpp"

struct Horse : public Officer {
        public:
        ~Horse() {}
        
        Horse(uint8_t const& x = 2,
              uint8_t const& y = 1);

        bool _cross(
                uint8_t const& x,
                uint8_t const& y)
                const;
};
