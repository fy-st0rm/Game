#ifndef _GAME_H_
#define _GAME_H_

#include "gln.h"
#include "global.h"
#include "map.h"
#include <stdbool.h>

typedef struct
{
	GLNWindow*   window;
	GLNRenderer* renderer;
	unsigned int shader;

	// Camera
	Ortho_camera* camera;

	// Map
	Map* map;

	// Flags
	bool running;
} Game;

Game* game_new();
void  game_init(Game* game);
void  game_event(Game* game);
void  game_run(Game* game);
void  game_exit(Game* game);

#endif
