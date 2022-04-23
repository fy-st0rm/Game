#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gln.h"
#include "global.h"
#include "animator.h"

#define PLAYER_TEXTURE "../assets/Player_2.png"

// Animator constants
#define IDLE_SPEED 50.0f
#define WALK_SPEED 10.0f

#define IDLE_UP   "idle_up"
#define IDLE_DOWN "idle_down"
#define WALK_DOWN "walk_down"
#define WALK_UP   "walk_up"

// Rotation constants
#define ROT_SPEED     0.15f
#define MAX_LEFT_ROT  2.8f
#define MAX_RIGHT_ROT 0.0f

#define SPRITE_WIDTH  2.0f
#define SPRITE_HEIGHT 5.0F


typedef struct 
{
	vec3f position;
	vec3f cam_pos; 
	vec2f size;
	vec4f color;
	float speed;
	GLNTexture texture;

	Animator* animator;

	bool move_left, move_right, move_up, move_down;
	bool turn_left, turn_right;
	bool face_up, face_down;

	float theta;
} Player;

// Init functions
Player* player_new(GLNWindow* window, vec3f position);
void player_clean(Player* player);
void player_init_frames(Player* player);

// Player movements
void player_move_left(Player* player);
void player_move_right(Player* player);
void player_move_up(Player* player);
void player_move_down(Player* player);
void player_idle(Player* player);
void player_handle_movement(Player* player);

// Main loops
void player_event(Player* player, SDL_Event event); 
void player_render(Player* player, GLNRenderer* renderer);

#endif
