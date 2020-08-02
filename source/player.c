#include "utils/vector.h"
#include "utils/controller.h"
#include "player.h"
#include "level.h"
#include "enemy.h"
#include "terrain.h"

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

// Figure MIDDLE
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

// Figure BACK
const struct packet_t cyclist_back[] =
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
	{DRAW, {  8 * SF, -4 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{DRAW, {  4 * SF,  0 * SF}},
	{DRAW, {  0 * SF, -4 * SF}},
	{DRAW, { -4 * SF,  0 * SF}},
	{DRAW, {  0 * SF,  2 * SF}},
	{MOVE, { -2 * SF,  1 * SF}},
	{DRAW, { -7 * SF, 10 * SF}},
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
	// FIGURE    ,    YX    , Angle
	{cyclist_back, {{0x0000}, 1}},
	{cyclist_back, {{0x0000}, 2}},
	{cyclist_back, {{0x0000}, 3}},
	{cyclist_back, {{0x0000}, 4}},
	{cyclist_back, {{0x0000}, 5}},
	{cyclist_back, {{0x0000}, 5}},
	{cyclist_back, {{0x0000}, 5}},
	{cyclist_back, {{0x0000}, 5}},
	{cyclist_back, {{0x0200}, 5}},
	{cyclist, {{0x0400}, 5}},
	{cyclist, {{0x0600}, 4}},
	{cyclist, {{0x0800}, 3}},
	{cyclist, {{0x0a00}, 2}},
	{cyclist, {{0x0c00}, 1}},
	{cyclist, {{0x0e00}, 0}},
	{cyclist, {{0x1000},-1}},
	{cyclist, {{0x1100},-2}},
	{cyclist, {{0x1100},-3}},
	{cyclist, {{0x1000},-3}},
	{cyclist, {{0x0e00},-2}},
	{cyclist, {{0x0c00},-2}},
	{cyclist, {{0x0a00},-2}},
	{cyclist, {{0x0800},-1}},
	{cyclist, {{0x0600},-1}},
	{cyclist, {{0x0400},-1}},
	{cyclist, {{0x0200},-0}},
	{cyclist, {{0x0000},-0}},
};

// ---------------------------------------------------------------------------

// Player
struct player_t player =
{
	.status = DEAD,
	.action = 0,
	.action_counter = 0,
	.offset = {
		{
			.yx = 0,
		},
		.angle = 0
	},
	.location = {
		{
			.yx = 0,
		},
		.angle = 0
	},
	.figure = cyclist
};

// ---------------------------------------------------------------------------
static void default_action(void)
{
}

static void jump_action(void)
{
	if (player.action_counter > (int)(sizeof(jump) / sizeof(struct action_t)) - 1)
	{
		player.action = default_action;
	}
	else
	{
		player.offset = jump[player.action_counter].offset;
		player.figure = jump[player.action_counter].figure;
		player.action_counter++;
	}
}

// ---------------------------------------------------------------------------
static void move_player(void)
{
	player.location.y = get_bike_pos_y();
	player.location.x = get_bike_pos_x();
	player.location.angle = get_bike_pos_angle();
	
	check_buttons();
	
	/* STATE CHECK */
	if (button_1_4_pressed() && player.action == default_action)
	{
		player.action = jump_action;
		player.action_counter = 0;
		player_jumped();
	}
	
	/* ACTION */
	(*player.action)();
}

static void draw_player(void)
{
	// Rotate bike
	struct packet_t rotated_cyclist[sizeof(cyclist) / sizeof(struct packet_t)];
	Rot_VL_Mode((unsigned int)(player.location.angle + player.offset.angle), (void*)player.figure, &rotated_cyclist);
	
	Reset0Ref();                    // reset beam to center of screen
	dp_VIA_t1_cnt_lo = MOVE_SPEED;  // set scaling factor for positioning
	Moveto_d(player.location.y + player.offset.y, player.location.x + player.offset.x);   // move beam to object coordinates
	dp_VIA_t1_cnt_lo = DRAW_SPEED;  // set scalinf factor for drawing
	Draw_VLp(&rotated_cyclist);     // draw vector list
}

// ---------------------------------------------------------------------------

void init_player(void)
{
	player.status = ALIVE;
	player.action = default_action;
	player.figure = cyclist;
	player.action_counter = 0;
	player.offset.yx = 0;
	player.offset.angle = 0;
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
