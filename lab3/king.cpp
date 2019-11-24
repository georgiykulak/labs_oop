#include "king.hpp"

King::King(uint8_t const& x,
           uint8_t const& y)
{
		if ( inField(x, y) )
        		setPos(x, y);
		else
				setPos(4, 1);
}

bool King::_straight(
		uint8_t const& x,
		uint8_t const& y)
		const
{
		return (getX() + 1 == x || getX() - 1 == x) &&
               (getY() == y)
				||
               (getY() + 1 == y || getY() - 1 == y) &&
               (getX() == x);
}

bool King::_cross(
		uint8_t const& x,
        uint8_t const& y)
        const
{
		return x != getX() && y != getY() &&
			   std::abs((int)x - (int)getX()) == 1 &&
			   std::abs((int)y - (int)getY()) == 1;
}

bool King::_special(
		uint8_t const& x,
        uint8_t const& y)
        const
{
		return getY() == y && getX() == 4 &&
              (x == 1 || x == 16) && (y == 1 || y == 16);
}

bool King::check(
		uint8_t const& x,
        uint8_t const& y)
		const
{
		return inField(x, y)   &&
              (_cross(x, y)    ||
               _straight(x, y) ||
               _special(x, y)  );
}
