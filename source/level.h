// ***************************************************************************
// level
// ***************************************************************************
#include "utils/vector.h"

#pragma once

// ---------------------------------------------------------------------------

enum level_status_t
{
	LEVEL_PLAY,
	LEVEL_LOST,
	LEVEL_WON,
};

// ---------------------------------------------------------------------------

struct terrain_t
{
	int start_y;
	int start_x;
	
	int vector_y;
	int vector_x;
};

struct level_t
{
	enum level_status_t status;
	struct terrain_t terrain;
	unsigned int slope_index;
	unsigned int difficulty_counter;
};

// ---------------------------------------------------------------------------

extern struct level_t current_level;

// ---------------------------------------------------------------------------

void level_init(void);
void level_play(void);

// ***************************************************************************
// end of file
// ***************************************************************************
