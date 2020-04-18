// ***************************************************************************
// level
// ***************************************************************************

#include <vectrex.h>
#include "utils/utils.h"
#include "game.h"
#include "level.h"
#include "player.h"

// ---------------------------------------------------------------------------

struct level_t current_level =
{
	.status = LEVEL_LOST,
	.terrain = {
		.vectors = {
			{MOVE, {    0, -128}},
			{DRAW, {  127,  127}},
			{DRAW, {  127,  127}},
			{DRAW, {  127,  127}},
			{DRAW, {  127,  127}},
			{DRAW, {  127,  127}},
			{STOP, { 0, 0}},
		},
		.y = -100,
	}
};

// ---------------------------------------------------------------------------

void draw_terrain(void)
{
	Reset0Ref();					// reset beam to center of screen
	dp_VIA_t1_cnt_lo = 0x7f;	    // set scaling factor for positioning
	Moveto_d(-100, -50);            // move beam to object coordinates
	dp_VIA_t1_cnt_lo = 0x22;		// set scalinf factor for drawing
	Draw_VLp(&current_level.terrain.vectors);		        // draw vector list
}

// ---------------------------------------------------------------------------

void level_init()
{
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
		handle_player();
		// TODO
		// end of frame
	}
}	

// ***************************************************************************
// end of file
// ***************************************************************************
