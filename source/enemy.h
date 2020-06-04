// ***************************************************************************
// enemy
// ***************************************************************************

#pragma once
#include "type.h"

// ---------------------------------------------------------------------------

#define MAX_ENEMIES 2
#define ENEMY_POSITIONS_COUNT 32

// ---------------------------------------------------------------------------

enum status_t
{
	ACTIVE, INACTIVE, FINISHED
};

// ---------------------------------------------------------------------------

struct enemy_t
{
	int angle;
	const struct position_t* positions;
	enum status_t status;
	int min_jump_point;
	int max_jump_point;
	int time;
	int jumped_over;
};

// ---------------------------------------------------------------------------

extern struct enemy_t enemies[MAX_ENEMIES];

// ---------------------------------------------------------------------------

void init_enemies(int angle, const struct position_t* positions, int min_jump_point, int max_jump_point); // min and max jump points based on enemy.time
void handle_enemies(void);
void player_jumped(void);
int player_failed(void);

// ***************************************************************************
// end of file
// ***************************************************************************
