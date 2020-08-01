// ***************************************************************************
// random - simple pseudo random number generator (rng)
// ***************************************************************************

#include <vectrex.h>
#include "random.h"

// ---------------------------------------------------------------------------

struct rng_t random = { .a = 0, .b = 0, .c = 0, .x = 0 };

// ---------------------------------------------------------------------------
 
void init_random_generator(unsigned int seed_1,unsigned int seed_2, unsigned int seed_3)
{
	//XOR new entropy into key state
	random.a = 0 ^ seed_1;
	random.b = 0 ^ seed_2;
	random.c = 0 ^ seed_3;

	random.x = 1;
	random.a = (random.a ^ random.c ^ random.x);
	random.b = (random.b + random.a);
	random.c = ((random.c + (random.b >> 1)) ^ random.a);
}

// ---------------------------------------------------------------------------

unsigned int get_random(void)
{
	random.x++;               								//x is incremented every round and is not affected by any other variable
	random.a = (random.a ^ random.c ^ random.x);			//note the mix of addition and XOR
	random.b = (random.b + random.a);         				//and the use of very few instructions
	random.c = ((random.c + (random.b >> 1)) ^ random.a);	//the right shift is to ensure that high-order bits from b can affect  
	return random.c;          								//low order bits of other variables
}

// ***************************************************************************
// end of file
// ***************************************************************************
