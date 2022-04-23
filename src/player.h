#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "gln.h"
#include "entity/entity.h"

#define PLAYER_TEXTURE "../assets/Player_2.png"

// Animator constants
#define IDLE_SPEED 50.0f
#define WALK_SPEED 10.0f

#define IDLE_UP   "idle_up"
#define IDLE_DOWN "idle_down"
#define WALK_DOWN "walk_down"
#define WALK_UP   "walk_up"

#define SPRITE_WIDTH  2.0f
#define SPRITE_HEIGHT 5.0F

// Rotation constants
#define ROT_SPEED     0.15f
#define MAX_LEFT_ROT  2.8f
#define MAX_RIGHT_ROT 0.0f

Entity* player_new(GLNWindow* window, GLNRenderer* renderer);
void	player_init_frames(Entity* player);
void    player_update_animation(Entity* player);
void    player_update_movement(Entity* player);
void    player_render(Entity* player);

#endif
