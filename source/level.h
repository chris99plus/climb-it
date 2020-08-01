// ***************************************************************************
// level
// ***************************************************************************
#include "utils/vector.h"

#pragma once

#undef ENEMIES_PER_LEVEL
#define ENEMIES_PER_LEVEL 10

// ---------------------------------------------------------------------------

enum level_status_t
{
	LEVEL_PLAY,
	LEVEL_LOST,
	LEVEL_WON,
};

// ---------------------------------------------------------------------------

struct level_t
{
	enum level_status_t status;
	unsigned int score;
	char print_score[5];
	unsigned int enemies_left;
};

// ---------------------------------------------------------------------------

extern struct level_t current_level;

// ---------------------------------------------------------------------------

void level_init(void);
void level_play(void);
void increment_score(void);

inline void enemy_mastered(void)
{
	current_level.score++;
	current_level.enemies_left--;
	increment_score();
}

// ***************************************************************************
// end of file
// ***************************************************************************
