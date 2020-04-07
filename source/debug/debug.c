// ***************************************************************************
// debug
// ***************************************************************************

#include "debug.h"

// ---------------------------------------------------------------------------
// all functions are for debugging purposes only
// ---------------------------------------------------------------------------

#ifndef NDEBUG

// ---------------------------------------------------------------------------

#include <vectrex.h>
#include "../utils/controller.h"
#include "../utils/utils.h"
#include "../utils/print.h"

// ---------------------------------------------------------------------------

void _f_debug(char* text, unsigned int type, void (*f_print)(void*), void* p_value, char* file, unsigned int length, unsigned long int line)
{
	char* p = file + length;
	length = 0;
	while ((*(--p) != '\\') &&  (p != file))
	{
		++length;
	}

	volatile char vfile[length--];
	unsigned int i;
	for (i = 0; i < length; ++i)
	{
		char c = *(++p);
		if ((c >= 'a') && (c <= 'z')) c -= ('a' - 'A');
		vfile[i] = c;
	}
	vfile[length] = '\x80';

	do
	{
		sync();
		Intensity_5F();
		print_string( 90, -120, text);
		print_string( 50, -120, "FILE:\x80");
		print_string( 30, -120, (char*) &vfile[0]);
		print_string(  0, -120, "LINE:\x80");
		print_long_unsigned_int(-20, -120, line);
		if (f_print)
		{
			print_string(-50, -120, "VALUE:\x80");
			switch (type)
			{
				case 0: (*((void (*)(int, int, unsigned int))(f_print)))(-70, -120, *((unsigned int*)(p_value))); break;
				case 1: (*((void (*)(int, int, signed int))(f_print)))(-70, -120, *((signed int*)(p_value))); break;
				case 2: (*((void (*)(int, int, long unsigned int))(f_print)))(-70, -120, *((long unsigned int*)(p_value))); break;
				case 3: (*((void (*)(int, int, long signed int))(f_print)))(-70, -120, *((long signed int*)(p_value))); break;
				default: break;
			}
		}
		check_buttons();
	}
	while (!button_1_1_pressed());
}

// ---------------------------------------------------------------------------

#endif

// ***************************************************************************
// end of file
// ***************************************************************************
