// ***************************************************************************
// terrain
// ***************************************************************************
#include "type.h"

#pragma once

#undef TERRAIN_COUNTS
#define TERRAIN_COUNTS 6 

#undef DIFFICULTY_LEVELS
#define DIFFICULTY_LEVELS TERRAIN_COUNTS

#undef TERRAIN_ENEMY_POSITION_COUNT
#define TERRAIN_ENEMY_POSITION_COUNT 32


struct terrain_t
{
	int start_y;
	int start_x;
	
	int vector_y;
	int vector_x;
};

/* */
extern unsigned int slope_index;
extern const int terrain_lookup[TERRAIN_COUNTS][7];
extern const struct position_t enemy_positions_lookup[TERRAIN_COUNTS][TERRAIN_ENEMY_POSITION_COUNT];

/* Terrain control functions */
void init_terrain(void);
void handle_terrain(void);

inline void next_slope(void)
{
	if ( slope_index < TERRAIN_COUNTS - 1) slope_index++;
}

inline unsigned int get_difficulty(void)
{
	return slope_index;
}

/* Terrain informations */
inline int get_bike_pos_y(void)
{
	return terrain_lookup[slope_index][4]; 
}

inline int get_bike_pos_x(void)
{
	return terrain_lookup[slope_index][5]; 
}

inline int get_bike_pos_angle(void)
{
	return terrain_lookup[slope_index][6]; 
}

inline struct position_t get_enemy_pos(unsigned int index)
{
	return enemy_positions_lookup[slope_index][index];
}

inline int get_enemy_angle(void)
{
	return terrain_lookup[slope_index][6];
}


