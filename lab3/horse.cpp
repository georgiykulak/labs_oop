#include "horse.hpp"

Horse::Horse(uint8_t const& x,
			 uint8_t const& y)
{
		if ( inField(x, y) )
				setPos(x, y);
		else
				setPos(2, 1);
}

bool Horse::_cross(
		uint8_t const& x,
        uint8_t const& y)
		const
{
		return getX() != x &&
               getY() != y &&
               //horizontal comparing
              (getX() + 2 == x &&
               getY() + 1 == y) ||
              (getX() + 2 == x &&
               getY() - 1 == y) ||
              (getX() - 2 == x &&
               getY() + 1 == y) ||
              (getX() - 2 == x &&
               getY() - 1 == y) ||
               //vertical comparing
              (getY() + 2 == y &&
               getX() + 1 == x) ||
              (getY() + 2 == y &&
               getX() - 1 == x) ||
              (getY() - 2 == y &&
               getX() + 1 == x) ||
              (getY() - 2 == y &&
               getX() - 1 == x);
}
