#include "gln.h"
#include "game.h"

int main(int argc, char** argv)
{
	Game* game = game_new();
	game_init(game);
	game_run(game);
	game_exit(game);
	return 0;
}

