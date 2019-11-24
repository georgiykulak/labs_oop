#include "officer.hpp"

Officer::Officer(uint8_t const& x,
				 uint8_t const& y)
{
		if ( inField(x, y) )
				setPos(x, y);
		else
				setPos(3, 1);
}

bool Officer::_cross(
		uint8_t const& x,
		uint8_t const& y)
		const
{
		return x != getX()  &&
               y != getY()  &&
               std::abs((int)x - (int)getX()) ==
               std::abs((int)y - (int)getY());
}

bool Officer::check(
		uint8_t const& x,
        uint8_t const& y)
		const
{
		return inField(x, y) && _cross(x, y);
}
