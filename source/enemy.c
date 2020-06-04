// ***************************************************************************
// enemy
// ***************************************************************************

#include <vectrex.h>
#include "utils/vector.h"
#include "enemy.h"
#include "player.h"

// ---------------------------------------------------------------------------
// SPEEDS
#undef MOVE_SPEED
#define MOVE_SPEED 0x7f // 127

#undef DRAW_SPEED
#define DRAW_SPEED 0x22 // 34


// Scaling Factor
#undef SF
#define SF 8

// ---------------------------------------------------------------------------

// JUMP
const struct packet_t enemy_figure[] =
{
	{DRAW, {  0 * SF,  2 * SF}},
	{DRAW, {  4 * SF,  0 * SF}},
	{DRAW, {  0 * SF, -4 * SF}},
	{DRAW, { -4 * SF,  0 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{STOP, { 0, 0}},
};

// ---------------------------------------------------------------------------

struct enemy_t enemies[] =
{
	{ .time = 0, .angle = 0, .status = INACTIVE },
	{ .time = 0, .angle = 0, .status = INACTIVE },
};

// ---------------------------------------------------------------------------

void draw_enemy(struct enemy_t* enemy)
{
	if (enemy->status == ACTIVE)
	{
		// Rotate enemy
		struct packet_t rotated_enemy[sizeof(enemy_figure) / sizeof(struct packet_t)];
		Rot_VL_Mode((unsigned int)(enemy->angle), &enemy_figure, &rotated_enemy);
		
		Reset0Ref();                    // reset beam to center of screen
		dp_VIA_t1_cnt_lo = MOVE_SPEED;  // set scaling factor for positioning
		Moveto_d(enemy->positions[enemy->time].y, enemy->positions[enemy->time].x);   // move beam to object coordinates
		dp_VIA_t1_cnt_lo = DRAW_SPEED;  // set scalinf factor for drawing
		Draw_VLp(&rotated_enemy);     // draw vector list
	}
}

// ---------------------------------------------------------------------------

void init_enemies(int angle, const struct position_t* positions )
{
	for (unsigned int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i].positions = positions;
		enemies[i].angle     = angle;
	
		enemies[i].time      = 0;
		enemies[i].status    = ACTIVE;
	}
}

void handle_enemies(void)
{
	for (unsigned int i = 0; i < MAX_ENEMIES; ++i)
	{
		draw_enemy(&enemies[i]);
		
		if (enemies[i].status == ACTIVE)
		{
			if (enemies[i].time < ENEMY_POSITIONS_COUNT)
			{
				enemies[i].time++;
			}
			else
			{
				#if 0
				enemies[i].time = 0;
				#else
				enemies[i].status = INACTIVE;
				#endif
			}
		}
	}
}
