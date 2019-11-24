#include "castle.hpp"

Castle::Castle(uint8_t const& x,
			   uint8_t const& y)
{
		if ( inField(x, y) )
				setPos(x, y);
		else
				setPos(1, 1);
}

bool Castle::_straight(
		uint8_t const& x,
		uint8_t const& y)
		const
{
		return x == getX() && y != getY() ||
			   y == getY() && x != getX();
}

bool Castle::check(
		uint8_t const& x,
		uint8_t const& y)
		const
{
		return inField(x, y) && _straight(x, y);
}
