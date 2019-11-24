#include "chessfigure.hpp"

void ChessFigure::setPos( //remove virtual if not important
		uint8_t const& x,
		uint8_t const& y)
{
		if ( !inField(x, y) ) {
				return;
		}
        
		this->x = x;
		this->y = y;
}

bool ChessFigure::inField(
		uint8_t const& x,
		uint8_t const& y)
		const
{
		return x > 0 && x < 9 && y > 0 && y < 9;
}

std::string ChessFigure::getPos() const
{
        if ( !inField(x, y) ) {
                return "error: wrong coordinates";
        }

        std::string str;
        str += '<';
        str += 'A' - 1 + x;
        str += '0' + y;
        str += '>';

        return str;
}
