// ***************************************************************************
// player
// ***************************************************************************

#pragma once
#include <vectrex.h>

// ---------------------------------------------------------------------------

enum player_status_t
{
	DEAD,
	ALIVE,
};

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

enum player_figure
{
	MIDDLE,
};

struct action_t
{
	enum player_figure figure;
	struct offset_t offset;
};

// ---------------------------------------------------------------------------

enum player_action_t
{
	DEFAULT,
	JUMP,
};

// ---------------------------------------------------------------------------

struct player_t
{
	enum player_status_t status;	// player status
	enum player_action_t action;    // player action
	int action_counter;             // action coutner
	struct offset_t offset;         // player offset to base position
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
