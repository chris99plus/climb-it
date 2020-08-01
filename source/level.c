// ***************************************************************************
// level
// ***************************************************************************

#include <vectrex.h>
#include "utils/utils.h"
#include "utils/print.c"
#include "game.h"
#include "level.h"
#include "player.h"
#include "enemy.h"
#include "terrain.h"

// ---------------------------------------------------------------------------
// SPEEDS
#undef MOVE_SPEED
#define MOVE_SPEED 0x7f // 127

#undef DRAW_SPEED
#define DRAW_SPEED 0x22 // 34

// ---------------------------------------------------------------------------

struct level_t current_level =
{
	.status = LEVEL_LOST,
	.score = 0,
	.print_score = "0000\x80",
	.enemies_left = 0
};

void increment_score()
{	
	unsigned int carry = 0;
	
	current_level.print_score[3] += 5;
	if (current_level.print_score[3] > '9')
	{
		current_level.print_score[3] -= 10;
		carry = 1;
	}

	current_level.print_score[2] += carry;
	carry = 0;

	if (current_level.print_score[2] > '9')
	{
		current_level.print_score[2] -= 10;
		carry = 1;
	}
	
	current_level.print_score[1] += carry;
	carry = 0;

	if (current_level.print_score[1] > '9')
	{
		current_level.print_score[1] -= 10;
		carry = 1;
	}

	current_level.print_score[0] += carry;
}

// ---------------------------------------------------------------------------

void level_init()
{
	init_terrain();
	init_enemies();
	init_player();
	
	current_level.status = LEVEL_PLAY;
	current_level.score = 0;
	current_level.enemies_left = ENEMIES_PER_LEVEL;
	
	current_level.print_score[0] = '0';
	current_level.print_score[1] = '0';
	current_level.print_score[2] = '0';
	current_level.print_score[3] = '0';
	current_level.print_score[4] = '\x80';
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
		
		print_string(100, -100,current_level.print_score);
		// game loop header end

		// game loop logic + handles
		if (current_level.score == 255)
		{
			current_level.status = LEVEL_WON;
		}
		else
		{
			if (current_level.enemies_left == 0)
			{
				current_level.enemies_left = ENEMIES_PER_LEVEL;
				next_slope();
			}
			
			handle_terrain();
			handle_enemies();
			handle_player();
			
			// Collision detection
			if (player_failed()) player.status = DEAD;
		}		
		// game loop logic + handles end
	}
}	

// ***************************************************************************
// end of file
// ***************************************************************************
