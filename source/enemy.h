// ***************************************************************************
// enemy
// ***************************************************************************

#pragma once
#include "type.h"

// ---------------------------------------------------------------------------
 
#define ENEMY_POSITIONS_COUNT 32
#define ENEMY_MIN_JUMP 11
#define ENEMY_MAX_JUMP 20

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
