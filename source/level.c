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
#define TERRAIN_SLOPE_LOOKUP_COUNT 6

/* Created by calculate-level.py script */
const int terrain_slope_lookup[TERRAIN_SLOPE_LOOKUP_COUNT][7] = 
{
	// | start | vector| player| player/enemy |
	// | y | x | y | x | y | x | angle        |
	{-20,-110,0,120,-18,-90,0},
	{-31,-110,12,119,-27,-90,1},
	{-43,-110,24,120,-37,-90,2},
	{-56,-110,36,120,-48,-90,3},
	{-69,-110,49,119,-59,-90,4},
	{-84,-110,64,120,-71,-90,5},
};

/* Created by calculate-level.py script */
const struct position_t enemy_position_lookup[TERRAIN_SLOPE_LOOKUP_COUNT][ENEMY_POSITIONS_COUNT] =
{
	{{-20,117},{-20,110},{-20,103},{-20,96},{-20,89},{-20,82},{-20,74},{-20,67},{-20,60},{-20,53},{-20,46},{-20,39},{-20,32},{-20,25},{-20,18},{-20,11},{-20,4},{-20,-3},{-20,-11},{-20,-18},{-20,-25},{-20,-32},{-20,-39},{-20,-46},{-20,-53},{-20,-60},{-20,-67},{-20,-74},{-20,-81},{-20,-89},{-20,-96},{-20,-103}},
	{{-10,115},{-11,108},{-12,101},{-12,94},{-13,87},{-14,80},{-14,73},{-15,66},{-16,59},{-16,52},{-17,45},{-18,38},{-18,31},{-19,24},{-20,17},{-20,10},{-20,3},{-21,-4},{-22,-11},{-22,-19},{-23,-26},{-24,-33},{-24,-40},{-25,-47},{-26,-54},{-26,-61},{-27,-68},{-28,-75},{-29,-82},{-29,-89},{-30,-96},{-31,-103}},
	{{1,117},{-1,110},{-2,103},{-3,96},{-5,89},{-6,82},{-8,74},{-9,67},{-11,60},{-12,53},{-13,46},{-15,39},{-16,32},{-18,25},{-19,18},{-20,11},{-21,4},{-22,-3},{-24,-11},{-25,-18},{-26,-25},{-28,-32},{-29,-39},{-31,-46},{-32,-53},{-33,-60},{-35,-67},{-36,-74},{-38,-81},{-39,-89},{-41,-96},{-42,-103}},
	{{12,117},{10,110},{8,103},{6,96},{3,89},{1,82},{-1,74},{-3,67},{-5,60},{-7,53},{-10,46},{-12,39},{-14,32},{-16,25},{-18,18},{-20,11},{-21,4},{-23,-3},{-26,-11},{-28,-18},{-30,-25},{-32,-32},{-34,-39},{-36,-46},{-39,-53},{-41,-60},{-43,-67},{-45,-74},{-47,-81},{-50,-89},{-52,-96},{-54,-103}},
	{{23,115},{20,108},{17,101},{14,94},{11,87},{8,80},{6,73},{3,66},{0,59},{-3,52},{-6,45},{-9,38},{-12,31},{-15,24},{-18,17},{-20,10},{-22,3},{-25,-4},{-28,-11},{-32,-19},{-34,-26},{-37,-33},{-40,-40},{-43,-47},{-46,-54},{-49,-61},{-52,-68},{-55,-75},{-58,-82},{-61,-89},{-63,-96},{-66,-103}},
	{{37,117},{33,110},{29,103},{25,96},{22,89},{18,82},{14,74},{10,67},{6,60},{2,53},{-1,46},{-5,39},{-9,32},{-12,25},{-16,18},{-20,11},{-23,4},{-26,-3},{-31,-11},{-34,-18},{-38,-25},{-42,-32},{-46,-39},{-49,-46},{-53,-53},{-57,-60},{-61,-67},{-64,-74},{-68,-81},{-72,-89},{-76,-96},{-80,-103}},
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
	
	init_enemies(p[6], enemy_position_lookup[current_level.slope_index], 11, 20);
}

// ---------------------------------------------------------------------------

static void draw_terrain(void)
{
	Reset0Ref();					// reset beam to center of screen
	dp_VIA_t1_cnt_lo = 0x7f;	    // set scaling factor for positioning
	Moveto_d(current_level.terrain.start_y, current_level.terrain.start_x);            // move beam to object coordinates
	dp_VIA_t1_cnt_lo = 0xf0;		// set scalinf factor for drawing (80d, 0x50)
	Intensity_7F();
	Draw_Line_d(current_level.terrain.vector_y, current_level.terrain.vector_x);
	Intensity_5F();
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
		
		#if 1
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
		
		#else
		#endif
		
		if (player_failed()) player.status = DEAD;
		
		// end of frame
	}
}	

// ***************************************************************************
// end of file
// ***************************************************************************
