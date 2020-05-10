// ***************************************************************************
// type
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------

struct offset_t
{
	union
	{
	   long int yx;
	   struct
	   {
		   int y;					// y coordinate byte
		   int x;					// x coordinate byte
	   };
	};
	int angle;
};

// ---------------------------------------------------------------------------