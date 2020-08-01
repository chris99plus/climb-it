// ***************************************************************************
// random - simple pseudo random number generator (rng)
// ***************************************************************************

#pragma once

// ---------------------------------------------------------------------------

struct rng_t
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int x;
};

// ---------------------------------------------------------------------------

extern struct rng_t random;

// ---------------------------------------------------------------------------

void init_random_generator(unsigned int seed_1,unsigned int seed_2, unsigned int seed_3);
unsigned int get_random(void);

// ***************************************************************************
// end of file
// ***************************************************************************
