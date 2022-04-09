#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gln.h"
#include "global.h"

// Rotation constants
#define ROT_SPEED     0.15f
#define MAX_LEFT_ROT  2.8f
#define MAX_RIGHT_ROT 0.0f

typedef struct 
{
	vec3f position;
	vec3f cam_pos; 
	vec2f size;
	vec4f color;
	float speed;
	GLNTexture texture;

	bool move_left, move_right, move_up, move_down;
	bool turn_left, turn_right;

	float theta;
} Player;

Player* player_new(GLNWindow* window, vec3f position);
void player_clean(Player* player);
void player_handle_movement(Player* player);
void player_event(Player* player, SDL_Event event); 
void player_render(Player* player, GLNRenderer* renderer);

#endif
