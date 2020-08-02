// ***************************************************************************
// enemy
// ***************************************************************************

#include <vectrex.h>
#include "utils/vector.h"
#include "enemy.h"
#include "player.h"
#include "terrain.h"
#include "random.h"
#include "level.h"

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

struct enemy_t enemy =
{
	.time = 0,
	.status = INACTIVE, 
	.jumped_over = 0 
};

// ---------------------------------------------------------------------------

void draw_enemy()
{
	// Rotate enemy
	struct packet_t rotated_enemy[sizeof(enemy_figure) / sizeof(struct packet_t)];
	Rot_VL_Mode((unsigned int)(get_enemy_angle()), &enemy_figure, &rotated_enemy);
	
	Reset0Ref();                    // reset beam to center of screen
	dp_VIA_t1_cnt_lo = MOVE_SPEED;  // set scaling factor for positioning
	Moveto_d(get_enemy_pos(enemy.time).y, get_enemy_pos(enemy.time).x);   // move beam to object coordinates
	dp_VIA_t1_cnt_lo = DRAW_SPEED;  // set scalinf factor for drawing
	Draw_VLp(&rotated_enemy);     // draw vector list
}

// ---------------------------------------------------------------------------

void reset_enemy()
{
	enemy.time        = 0;
	enemy.status      = INACTIVE;
	
	enemy.jumped_over = 0;
	
	// random cooldown gets less when difficulty increases
	enemy.cooldown    = ((DIFFICULTY_LEVELS - get_difficulty()) >> 1) * (get_random() << 1);
}

void init_enemies()
{
	init_random_generator(VIA_t2_hi,~VIA_t2_hi,VIA_t2_hi << 4);
	reset_enemy();
}

void handle_enemies(void)
{
	if (enemy.status == ACTIVE)
	{
		draw_enemy();
		
		if (enemy.time < ENEMY_POSITIONS_COUNT)
		{
			enemy.time++;
		}
		else
		{
			enemy.status = FINISHED;
		}
	} 
	else if (enemy.status == FINISHED)
	{
		if (enemy.jumped_over) enemy_mastered();
		reset_enemy();
	}
	else
	{
		if (enemy.cooldown == 0) enemy.status = ACTIVE;
		else enemy.cooldown--;
	}
}

void player_jumped(void)
{
	if (enemy.status == ACTIVE && enemy.time > ENEMY_MIN_JUMP && enemy.time < ENEMY_MAX_JUMP)
	{
		enemy.jumped_over = 1;
	}
}

int player_failed(void)
{
	if (!enemy.jumped_over && enemy.status == FINISHED)
	{
		return 1;
	}
	
	return 0;
}
