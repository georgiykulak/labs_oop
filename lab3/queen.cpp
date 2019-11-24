#include "queen.hpp"

Queen::Queen(uint8_t const& x,
             uint8_t const& y)
{
		if ( inField(x, y) )
				setPos(x, y);
		else
				setPos(5, 1);
}

bool Queen::check(
		uint8_t const& x,
		uint8_t const& y)
        const
{
		return inField(x, y) &&
			   (_cross(x, y) || _straight(x, y));
}
