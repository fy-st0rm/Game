#ifndef _GAME_H_
#define _GAME_H_

#include "gln.h"
#include "global.h"
#include "map.h"
#include "player.h"
#include <stdbool.h>

typedef struct
{
	GLNWindow*   window;
	GLNRenderer* renderer;
	SDL_Event    event;
	unsigned int shader;

	// Entities
	Entity* player;

	// Camera
	vec3f* cam_pos;
	Ortho_camera* camera;

	// Mouse
	vec2f* mouse_pos;

	// Map
	Map* map;

	// Flags
	bool running;
} Game;

Game* game_new();
void  game_init(Game* game);
void  game_calc_mouse_pos(Game* game);
void  game_event(Game* game);
void  game_run(Game* game);
void  game_exit(Game* game);

#endif
