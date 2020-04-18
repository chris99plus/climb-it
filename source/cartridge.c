// ***************************************************************************
// vectrex cartridge init block - edit to set game title
// ***************************************************************************

#include <vectrex.h>
#include "cartridge.h"

// ---------------------------------------------------------------------------

const struct cartridge_t game_header __attribute__((section(".cartridge"), used)) = 
{
	.copyright 		= "g GCE 2019\x80",	// required, do not change!
	.music 			= &Vec_Music_1,		// this is the Vectrex startup tune 
	.title_height 	= -8,
	.title_width 	= 80,
	.title_y 		= 24,
	.title_x 		= -86,
	.title 			= "GAME TEMPLATE\x80" 	// note that \x00 is automatically appended!
};

// ***************************************************************************
// end of file
// ***************************************************************************