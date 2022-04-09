#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gln.h"
#include "global.h"

typedef struct 
{
	vec3f position;
	vec3f cam_pos; 
	vec2f size;
	vec4f color;
	float speed;
	GLNTexture texture;

	bool move_left, move_right, move_up, move_down;
} Player;

Player* player_new(GLNWindow* window, vec3f position);
void player_clean(Player* player);
void player_event(Player* player, SDL_Event event); 
void player_render(Player* player, GLNRenderer* renderer);

#endif
