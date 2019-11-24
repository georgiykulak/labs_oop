#pragma once

#include <iostream>

struct ChessFigure {
        public:
        virtual ~ChessFigure() {}
        
        virtual bool check(
                uint8_t const&,
                uint8_t const&)
                const = 0;

        uint8_t getX() const { return x; }
        
        uint8_t getY() const { return y; }

        void setPos(
                uint8_t const& x,
                uint8_t const& y);
    
        bool inField(
                uint8_t const& x,
                uint8_t const& y)
                const;

        std::string getPos() const;
        
        private:
        uint8_t x;
        uint8_t y;
};
