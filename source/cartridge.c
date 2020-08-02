// ***************************************************************************
// vectrex cartridge init block - edit to set game title
// ***************************************************************************

#include <vectrex.h>
#include "cartridge.h"

// ---------------------------------------------------------------------------

const struct cartridge_t game_header __attribute__((section(".cartridge"), used)) = 
{
	.copyright 		= "g GCE 2020\x80",	// required, do not change!
	.music 			= &Vec_Music_1,		// this is the Vectrex startup tune 
	.title_height 	= -8,
	.title_width 	= 80,
	.title_y 		= 10,
	.title_x 		= -60,
	.title 			= "CLIMB IT\x80" 	// note that \x00 is automatically appended!
};

// ***************************************************************************
// end of file
// ***************************************************************************
