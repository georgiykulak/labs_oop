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

        virtual void setPos(
                uint8_t const& x,
                uint8_t const& y)
        {
                if ( !inField(x, y) ) {
                        return;
                }
        
                this->x = x;
                this->y = y;
        }
    
        bool inField(
                uint8_t const& x,
                uint8_t const& y)
                const
        {
                return x > 0 && x < 9 && y > 0 && y < 9;
        }

        std::string getPos() const
        {
                if ( !inField(x, y) ) {
                        return "error: \
                                wrong coordinates";
                }

                std::string str;
                str += '<';
                str += 'A' - 1 + x;
                str += '0' + y;
                str += '>';

                return str;
        }
        
        private:
        uint8_t x;
        uint8_t y;
};
