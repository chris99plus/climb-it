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

const int terrain_slope_lookup[TERRAIN_SLOPE_LOOKUP_COUNT][12] = 
{
	// start    , vector    , player           , enemies
	//   y,    x,    y,    x,    y,    x, angle, start.y, start.x, step.y, step.x, angle, 
	{  -57,  -70,    0,  127,  -54,  -13,     0,     -57,      87,      0,     -4,     0},
	{  -57,  -70,   29,  127,  -40,  -13,     2,     -21,      87,     -1,     -5,     2},
	{  -57,  -70,   65,  127,  -26,  -13,     5,      23,      87,     -3,     -6,     5},
	{  -73,  -62,   88,  100,  -26,  -13,     7,      35,      60,     -5,     -6,     7},
	{  -83,  -49,  127,   88,  -26,  -13,    10,      76,      60,     -9,     -6,    10},
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

static void adjust_slope(void)
{
	const int* p = terrain_slope_lookup[current_level.slope_index];
	current_level.terrain.start_y  = p[0];
	current_level.terrain.start_x  = p[1];
	current_level.terrain.vector_y = p[2];
	current_level.terrain.vector_x = p[3];
	
	player.loaction.y              = p[4];
	player.loaction.x              = p[5];
	player.loaction.angle          = p[6];
	
	init_enemies(p[7], p[8], p[9], p[10], p[11]);
}

// ---------------------------------------------------------------------------

static void draw_terrain(void)
{
	Reset0Ref();					// reset beam to center of screen
	dp_VIA_t1_cnt_lo = 0x7f;	    // set scaling factor for positioning
	Moveto_d(current_level.terrain.start_y, current_level.terrain.start_x);            // move beam to object coordinates
	dp_VIA_t1_cnt_lo = 0x50;		// set scalinf factor for drawing (80d)
	Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
	Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
	//Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
}

// ---------------------------------------------------------------------------

void level_init()
{
	// Adjust parameters of level and player
	adjust_slope();
	
	// Initializes the player
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
