// ***************************************************************************
// print
// ***************************************************************************

#include "print.h"

// ---------------------------------------------------------------------------
// these print functions all have non-optimal efficiency
// an should mainly be used for debugging purposes only
// ---------------------------------------------------------------------------

#ifndef NPRINT
#include <vectrex.h>
#include "../utils/utils.h"

// ---------------------------------------------------------------------------
// print a c string (with \0 at the end) at absolute coordinates (y, x)

void print_string(int y, int x, char* text)
{
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) text);
}

// ---------------------------------------------------------------------------
// print decimal unsigned int value at absolute coordinates (y, x)

void print_unsigned_int(int y, int x, unsigned int z)
{
	volatile char message[4];
	message[3] = '\x80';
	unsigned int i = 2;
	do
	{
		message[i--] = (char) ('0' + z % 10);
		z = z / 10;
	}
	while (i != 255);	
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) &message[0]);
}

// ---------------------------------------------------------------------------
// print decimal int value at absolute coordinates (y, x)

void print_signed_int(int y, int x, int z)
{
	volatile char message[5];
	message[0] = (z < 0) ? (char) 0x2d : (char) 0x2b;
	message[4] = '\x80';
	unsigned int i = 3;
	unsigned int u = (z < 0) ? (255u - (((unsigned int) z) - 1u)) : (unsigned int) z;
	do
	{
		message[i--] = (char) ('0' + u % 10);
		u = u / 10;
	}
	while (i > 0);	
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) &message[0]);
}

// ---------------------------------------------------------------------------
// print decimal unsigned long int value at absolute coordinates (y, x)

void print_long_unsigned_int(int y, int x, unsigned long int z)
{
	volatile char message[6];
	message[5] = '\x80';
	unsigned int i = 4;
	do
	{
		message[i--] = (char) ('0' + (z % 10));
		z = z / 10;
	}
	while (i != 255);	
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) &message[0]);
}

// ---------------------------------------------------------------------------
// print decimal unsigned long int value at absolute coordinates (y, x)

void print_long_signed_int(int y, int x, signed long int z)
{
	volatile char message[7];
	message[0] = (z < 0) ? (char) 0x2d : (char) 0x2b;
	message[6] = '\x80';
	unsigned int i = 5;
	long unsigned int u = (z < 0) ? (65535u - (((long unsigned int) z) - 1u)) : (long unsigned int) z;
	do
	{
		message[i--] = (char) ('0' + (u % 10));
		u = u / 10;
	}
	while (i > 0);	
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) &message[0]);
}

// ---------------------------------------------------------------------------
// print binary unsigned int value at absolute coordinates (y, x)

void print_binary(int y, int x, unsigned int z)
{
	volatile char message[9];
	message[8] = '\x80';
	unsigned int i = 7;
	do
	{
		message[i--] = (char) ('0' + (z & 1));
		z >>= 1; 
	}
	while (i != 255);	
	position_beam_s(y, x, 0x7F);
	Print_Str((void*) &message[0]);
}

// ---------------------------------------------------------------------------

#endif

// ***************************************************************************
// end of file
// ***************************************************************************
