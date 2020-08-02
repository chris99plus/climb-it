// ***************************************************************************
// enemy
// ***************************************************************************

#pragma once
#include "type.h"

// ---------------------------------------------------------------------------
 
#define ENEMY_POSITIONS_COUNT 32 	// numbers of positions on the screen
#define ENEMY_MIN_JUMP 11			// minimum time the player has to jump
#define ENEMY_MAX_JUMP 20			// maximum time the player has to jump

// ---------------------------------------------------------------------------

enum status_t
{
	ACTIVE, INACTIVE, FINISHED
};

// ---------------------------------------------------------------------------

struct enemy_t
{
	enum status_t status;
	unsigned int time;
	unsigned int cooldown;
	int jumped_over;
};

// ---------------------------------------------------------------------------

extern struct enemy_t enemy;

// ---------------------------------------------------------------------------

void init_enemies(void);
void handle_enemies(void);
void player_jumped(void);
int player_failed(void);

// ***************************************************************************
// end of file
// ***************************************************************************
