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
	{ .offset = {{ .yx = 0, }, .angle = 0}, .location = {{ .yx = 0, }, .angle = 0}, .anim_steps = {{ .yx = 0, }, .angle = 0} },
	{ .offset = {{ .yx = 0, }, .angle = 0}, .location = {{ .yx = 0, }, .angle = 0}, .anim_steps = {{ .yx = 0, }, .angle = 0} },
};

// ---------------------------------------------------------------------------

void adjust_slope_for_enemies()
{
	
}


void move_enemy(struct enemy_t* enemy)
{
	if (player.speed)
	{
		enemy->location.y += enemy->anim_steps.y;
		enemy->location.x += enemy->anim_steps.x;
	}
}

void draw_enemy(struct enemy_t* enemy)
{
	// Rotate enemy
	struct packet_t rotated_enemy[sizeof(enemy_figure) / sizeof(struct packet_t)];
	Rot_VL_Mode((unsigned int)(enemy->location.angle + enemy->offset.angle), &enemy_figure, &rotated_enemy);
	
	Reset0Ref();                    // reset beam to center of screen
	dp_VIA_t1_cnt_lo = MOVE_SPEED;  // set scaling factor for positioning
	Moveto_d(enemy->location.y + enemy->offset.y, enemy->location.x + enemy->offset.x);   // move beam to object coordinates
	dp_VIA_t1_cnt_lo = DRAW_SPEED;  // set scalinf factor for drawing
	Draw_VLp(&rotated_enemy);     // draw vector list
}

// ---------------------------------------------------------------------------

void init_enemies(int startY, int startX, int stepY, int stepX, int angle)
{
	for (unsigned int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i].anim_steps.y     = stepY;
		enemies[i].anim_steps.x     = stepX;
		
		enemies[i].anim_steps.angle = angle; // Maby this line is unnecessary
		
		enemies[i].location.y       = startY;
		enemies[i].location.x       = startX;
		enemies[i].location.angle   = angle;
	}
}

void handle_enemies(void)
{
	for (unsigned int i = 0; i < MAX_ENEMIES; ++i)
	{
		move_enemy(&enemies[i]);
		draw_enemy(&enemies[i]);
	}
}
