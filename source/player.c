#include "utils/vector.h"
#include "utils/controller.h"
#include "player.h"
#include "level.h"

#include "debug/assert.h"

// ---------------------------------------------------------------------------
// SPEEDS
#undef MOVE_SPEED
#define MOVE_SPEED 0x7f // 127

#undef DRAW_SPEED
#define DRAW_SPEED 0x22 // 34

// Scaling Factor
#undef SF
#define SF 8

// Player Positions
#undef PLAYER_POS_Y
#define PLAYER_POS_Y -26 //= (-12 * SF / MOVE_SPEED * DRAW_SPEED)

#undef PLAYER_POS_X
#define PLAYER_POS_X -13 //= (-6 * SF / MOVE_SPEED * DRAW_SPEED)

#undef PLAYER_ANGLE
#define PLAYER_ANGLE 8   //=> 0 -> 0°; 16 -> -90°; 32 -> 180°; 48 -> 90°; 64 -> 360°

// ---------------------------------------------------------------------------

// Player
struct player_t player =
{
	.status = DEAD,
	.action = DEFAULT,
	.action_counter = 0,
	.offset = {
		{
			.yx = 0,
		},
		.angle = 0
	}
};

// Figure
const struct packet_t cyclist[] =
{
	{MOVE, { 12 * SF,  6 * SF}}, // bike original (-2|-4)
	{DRAW, { -9 * SF,  3 * SF}},
	{DRAW, {  0 * SF, -6 * SF}},
	{DRAW, {  6 * SF,  4 * SF}},
	{DRAW, {  0 * SF,  8 * SF}},
	{DRAW, { -6 * SF, -6 * SF}},
	{MOVE, {  0 * SF,  8 * SF}},
	{DRAW, {  9 * SF, -3 * SF}},
	{DRAW, {  0 * SF, -1 * SF}},
	{MOVE, {  0 * SF, -6 * SF}},
	{DRAW, {  0 * SF, -2 * SF}},
	{MOVE, {  1 * SF,  1 * SF}}, // cyclist
	{DRAW, { -3 * SF,  5 * SF}},
	{DRAW, { -7 * SF, -2 * SF}},
	{MOVE, { 10 * SF, -3 * SF}},
	{DRAW, {  9 * SF,  3 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{DRAW, {  4 * SF,  0 * SF}},
	{DRAW, {  0 * SF, -4 * SF}},
	{DRAW, { -4 * SF,  0 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{MOVE, { -3 * SF, -1 * SF}},
	{DRAW, { -7 * SF,  5 * SF}},
	{MOVE, { -5 * SF,  5 * SF}}, // wheel front
	{DRAW, { -1 * SF,  2 * SF}},
	{DRAW, { -2 * SF,  1 * SF}},
	{DRAW, { -2 * SF,  0 * SF}},
	{DRAW, { -2 * SF, -1 * SF}},
	{DRAW, { -1 * SF, -2 * SF}},
	{DRAW, {  0 * SF, -2 * SF}},
	{DRAW, {  1 * SF, -2 * SF}},
	{DRAW, {  2 * SF, -1 * SF}},
	{DRAW, {  2 * SF,  0 * SF}},
	{DRAW, {  2 * SF,  1 * SF}},
	{DRAW, {  1 * SF,  2 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{MOVE, { -4 * SF, -1 * SF}},
	{MOVE, {  4 * SF,-13 * SF}}, // wheel back
	{DRAW, { -1 * SF,  2 * SF}},
	{DRAW, { -2 * SF,  1 * SF}},
	{DRAW, { -2 * SF,  0 * SF}},
	{DRAW, { -2 * SF, -1 * SF}},
	{DRAW, { -1 * SF, -2 * SF}},
	{DRAW, {  0 * SF, -2 * SF}},
	{DRAW, {  1 * SF, -2 * SF}},
	{DRAW, {  2 * SF, -1 * SF}},
	{DRAW, {  2 * SF,  0 * SF}},
	{DRAW, {  2 * SF,  1 * SF}},
	{DRAW, {  1 * SF,  2 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{STOP, { 0, 0}},
};

// JUMP
const struct action_t jump[] = {
	// FIGURE,   YX,   Angle
	{MIDDLE, {{0x0000}, 1}},
	{MIDDLE, {{0x0000}, 2}},
	{MIDDLE, {{0x0000}, 3}},
	{MIDDLE, {{0x0000}, 4}},
	{MIDDLE, {{0x0000}, 5}},
	{MIDDLE, {{0x0000}, 5}},
	{MIDDLE, {{0x0000}, 5}},
	{MIDDLE, {{0x0000}, 5}},
	{MIDDLE, {{0x0200}, 5}},
	{MIDDLE, {{0x0400}, 5}},
	{MIDDLE, {{0x0600}, 4}},
	{MIDDLE, {{0x0800}, 3}},
	{MIDDLE, {{0x0a00}, 2}},
	{MIDDLE, {{0x0c00}, 1}},
	{MIDDLE, {{0x0e00}, 0}},
	{MIDDLE, {{0x1000},-1}},
	{MIDDLE, {{0x1100},-2}},
	{MIDDLE, {{0x1100},-3}}, // old
	{MIDDLE, {{0x1000},-3}},
	{MIDDLE, {{0x0e00},-2}},
	{MIDDLE, {{0x0c00},-2}},
	{MIDDLE, {{0x0a00},-2}},
	{MIDDLE, {{0x0800},-1}},
	{MIDDLE, {{0x0600},-1}},
	{MIDDLE, {{0x0400},-1}},
	{MIDDLE, {{0x0200},-0}},
	{MIDDLE, {{0x0000},-0}},
};

// ---------------------------------------------------------------------------
void move_player(void)
{
	check_buttons();
	
	// Simulate Jump
	if (button_1_1_pressed() && player.action == DEFAULT)
	{
		player.action = JUMP;
		player.action_counter = 0;
	}
	
	// JUMP Action
	if (player.action == JUMP)
	{
		if (player.action_counter > (int)(sizeof(jump) / sizeof(struct action_t)) - 1)
		{
			player.action = DEFAULT;
		}
		else
		{
			player.offset = jump[player.action_counter].offset;
			player.action_counter++;
		}
	}
}

void draw_player(void)
{
	// Rotate bike
	struct packet_t rotated_cyclist[sizeof(cyclist) / sizeof(struct packet_t)];
	Rot_VL_Mode((unsigned int)(PLAYER_ANGLE + player.offset.angle), &cyclist, &rotated_cyclist);
	
	Reset0Ref();                    // reset beam to center of screen
	dp_VIA_t1_cnt_lo = MOVE_SPEED;  // set scaling factor for positioning
	Moveto_d(PLAYER_POS_Y + player.offset.y, PLAYER_POS_X + player.offset.x);   // move beam to object coordinates
	dp_VIA_t1_cnt_lo = DRAW_SPEED;  // set scalinf factor for drawing
	Draw_VLp(&rotated_cyclist);     // draw vector list
}

// ---------------------------------------------------------------------------

void init_player(void)
{
	player.status = ALIVE;
}

// ---------------------------------------------------------------------------

void handle_player(void)
{
	move_player();
	draw_player();

	if (player.status == DEAD)
	{
		current_level.status = LEVEL_LOST;
	}
}

// ***************************************************************************
// end of file
// ***************************************************************************