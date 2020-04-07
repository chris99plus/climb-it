// ***************************************************************************
// vector
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------
// data structure describing a single vector

struct vector_t
{
	int y;		// y coordinate byte
	int x;		// x coordinate byte
};

// ---------------------------------------------------------------------------
// vector drawing modes for packet style vector lists

enum mode_t
{
	MOVE = 0,
	STOP = 1,
	DRAW = 255
};

// ---------------------------------------------------------------------------
// data structure describing a single extended vector

struct packet_t
{
	enum mode_t mode;			// drawing mode
	struct vector_t vector;		// relative vector;
};

// ***************************************************************************
// end of file
// ***************************************************************************
