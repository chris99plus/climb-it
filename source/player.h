// ***************************************************************************
// player
// ***************************************************************************

#pragma once
#include <vectrex.h>
#include "type.h"

// ---------------------------------------------------------------------------

enum player_status_t
{
	DEAD,
	ALIVE,
};

// ---------------------------------------------------------------------------

struct action_t
{
	const struct packet_t *figure;
	struct offset_t offset;
};

// ---------------------------------------------------------------------------

struct player_t
{
	enum player_status_t status;	// player status
	
	/* Current action */
	void (*action)(void);           // player action handler
	int action_counter;             // action coutner
	
	/* Player position & status */
	const struct packet_t* figure;  // Shape of the current figure
	struct offset_t offset;         // current player offset to base position
	struct offset_t loaction;		// current static position and rotation
	int speed;                      // player speed
};

// ---------------------------------------------------------------------------

extern struct player_t player;

// ---------------------------------------------------------------------------

void init_player(void);
void handle_player(void);

// ***************************************************************************
// end of file
// ***************************************************************************
