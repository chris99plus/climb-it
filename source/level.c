// ***************************************************************************
// level
// ***************************************************************************

#include <vectrex.h>
#include "utils/utils.h"
#include "game.h"
#include "level.h"
#include "player.h"
#include "enemy.h"

// ---------------------------------------------------------------------------

#undef TERRAIN_SLOPE_LOOKUP_COUNT
#define TERRAIN_SLOPE_LOOKUP_COUNT 5

const int terrain_slope_lookup[TERRAIN_SLOPE_LOOKUP_COUNT][7] = 
{
	// start  ,   vector, player
	//  y,   x,   y,   x,   y,   x, angle
	{ -57, -70,   0, 127, -54, -13,   0},
	{ -57, -70,  29, 127, -40, -13,   2},
	{ -57, -70,  65, 127, -26, -13,   5},
	{ -73, -62,  88, 100, -26, -13,   7},
	{ -83, -49, 127,  88, -26, -13,  10}
};

// ---------------------------------------------------------------------------

struct level_t current_level =
{
	.status = LEVEL_LOST,
	.terrain = {
		.start_y = -57,
		.start_x = -70,
		.vector_y = 65,
		.vector_x = 127
	},
	
	.slope_index = 0,
	.difficulty_counter = 0
};

// ---------------------------------------------------------------------------

void adjust_slope(void)
{
	current_level.terrain.start_y  = terrain_slope_lookup[current_level.slope_index][0];
	current_level.terrain.start_x  = terrain_slope_lookup[current_level.slope_index][1];
	current_level.terrain.vector_y = terrain_slope_lookup[current_level.slope_index][2];
	current_level.terrain.vector_x = terrain_slope_lookup[current_level.slope_index][3];
	player.loaction.y              = terrain_slope_lookup[current_level.slope_index][4];
	player.loaction.x              = terrain_slope_lookup[current_level.slope_index][5];
	player.loaction.angle          = terrain_slope_lookup[current_level.slope_index][6];
}

// ---------------------------------------------------------------------------

void draw_terrain(void)
{
	Reset0Ref();					// reset beam to center of screen
	dp_VIA_t1_cnt_lo = 0x7f;	    // set scaling factor for positioning
	Moveto_d(current_level.terrain.start_y, current_level.terrain.start_x);            // move beam to object coordinates
	dp_VIA_t1_cnt_lo = 0x50;		// set scalinf factor for drawing
	Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
	Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
}

// ---------------------------------------------------------------------------

void level_init()
{
	// Adjust parameters of level and player
	adjust_slope();
	
	// Initializes the player
	init_enemies();
	init_player();
	
	current_level.status = LEVEL_PLAY;
}	

// ---------------------------------------------------------------------------

void level_play(void)
{
	while(current_level.status == LEVEL_PLAY)
	{
		// game loop header start - do not change
		DP_to_C8();
		Explosion_Snd(current_explosion);
		Init_Music_chk(current_music);
		Wait_Recal();
		Do_Sound();
		Intensity_5F();
		// game loop header end

		// frame start: this is where the action happens...
		draw_terrain();
		handle_enemies();
		handle_player();
		// TODO
		
		/* TESTING OF THE SLOPE */
		if (current_level.difficulty_counter > 150) 
		{
			current_level.slope_index = (current_level.slope_index + 1) % TERRAIN_SLOPE_LOOKUP_COUNT;
			adjust_slope();
			current_level.difficulty_counter = 0;
		}
		else
		{
			current_level.difficulty_counter++;
		}
		// end of frame
	}
}	

// ***************************************************************************
// end of file
// ***************************************************************************
