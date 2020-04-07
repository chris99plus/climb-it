// ***************************************************************************
// collision
// ***************************************************************************

#include <vectrex.h>

// ---------------------------------------------------------------------------
// symmetric collision check (bounding box)

int check_collision(int y0, int x0, int y1, int x1, unsigned int ry, unsigned int rx)
{
	unsigned int hits = 0;
	if (y0 < y1)
	{
		if (((unsigned int)(y1 - y0)) <= ry)
		{
			++hits;
		}
	}
	else
	{
		if (((unsigned int)(y0 - y1)) <= ry)
		{
			++hits;
		}
	}
	if (x0 < x1)
	{
		if (((unsigned int)(x1 - x0)) <= rx)
		{
			++hits;
		}
	}
	else
	{
		if (((unsigned int)(x0 - x1)) <= rx)
		{
			++hits;
		}
	}
	return (hits == 2);
}

// ***************************************************************************
// end of file
// ***************************************************************************
