#include "pawn.hpp"

Pawn::Pawn(uint8_t const& x,
           uint8_t const& y)
{
		if ( inField(x, y) )
				setPos(x, y);
		else
				setPos(1, 2);
}

bool Pawn::_special(
		uint8_t const& x,
		uint8_t const& y)
        const
{
		return ((getY() == 2 && 4 == y) ||
                (getY() == 7 && 5 == y)) &&
                 getX() == x;
}
