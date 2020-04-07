// ***************************************************************************
// print
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------
// use macro below to enable / disable the compilation of print functions
// ---------------------------------------------------------------------------

//#define NPRINT

// ---------------------------------------------------------------------------
// these print functions all have non-optimal efficiency
// an should mainly be used for debugging purposes only
// ---------------------------------------------------------------------------

#ifndef NPRINT
void print_string(int y, int x, char* text);
void print_unsigned_int(int y, int x, unsigned int z);
void print_signed_int(int y, int x, int z);
void print_long_unsigned_int(int y, int x, long unsigned int z);
void print_long_signed_int(int y, int x, long signed int z);
void print_binary(int y, int x, unsigned int z);
#endif

// ***************************************************************************
// end of file
// ***************************************************************************
