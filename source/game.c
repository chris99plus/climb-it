// ***************************************************************************
// game
// ***************************************************************************

#include <vectrex.h>
#include "utils/controller.h"
#include "utils/print.h"
#include "utils/utils.h"
#include "game.h"
#include "level.h"

// ---------------------------------------------------------------------------

static inline __attribute__((always_inline))
void game_options(void)
{
	unsigned int delay = 255;

	do
	{
		Sync();
		Intensity_5F();
		print_string(0, -90, "START THE GAME\x80");
		print_string(-20, -70, "--> PRESS 4\x80");
		check_buttons();
	}
	while((--delay) && !button_1_4_pressed());
}

// ---------------------------------------------------------------------------

void game_init(void)
{
	// activate first joystick, switch off second joystick
	enable_controller_1_x();
	enable_controller_1_y();
	disable_controller_2_x();
	disable_controller_2_y();
}

// ---------------------------------------------------------------------------
// main game loop, this is where the action happens

void game_play(void)
{
	level_init();
	level_play();

	if (current_level.status == LEVEL_WON)
	{
		game_won();
	}
	else
	{
		game_over();
	}
}

// ---------------------------------------------------------------------------

void game_won(void)
{
	unsigned int delay = 255;

	do
	{
		Sync();
		Intensity_5F();
		print_string(0, -50, "YOU WON\x80");
		print_string(-20, -70, "SCORE:\x80");
		print_string(-20, 0, current_level.print_score);
		check_buttons();
	}
	while((--delay) && !button_1_4_pressed());
}

void game_over(void)
{
	unsigned int delay = 150;

	do
	{
		Sync();
		Intensity_5F();
		print_string(0, -64, "GAME OVER\x80");
		print_string(-20, -70, "SCORE:\x80");
		print_string(-20, 0, current_level.print_score);
		check_buttons();
	}
	while((--delay) && !button_1_4_pressed());
}

// ---------------------------------------------------------------------------

int game(void)
{
	game_options();

	if (button_1_4_held())
	{
		game_init();
		game_play();
		return 0;		// go to option screen, repeat cycle
	}
	else
	{
		return -1; 		// jump to title screen
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************
