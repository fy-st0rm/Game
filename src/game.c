#include "game.h"

Game* game_new()
{
	Game* game = (Game*) malloc(sizeof(Game));
	game->window = gln_create_window(WIN_TITLE, WIN_WIDTH, WIN_HEIGHT);
	game->renderer = gln_create_renderer(MAX_QUADS);
	game->shader = gln_load_shader(VERT_SHADER, FRAG_SHADER);

	// Creating camera
	vec3f pos = { 0.0f, 0.0f, 0.0f };
	game->camera = ortho_cam_new(pos, 0.0f, WIN_WIDTH, WIN_HEIGHT, 0.0f, 1000.0f, -1.0f);

	// Creating map
	game->map = map_new(game->window);

	game->running = true;

	return game;
}

void game_init(Game* game)
{
	gln_init_renderer(game->renderer);

	// Creating samplers
	int samplers[game->renderer->max_texture];
	for (int i = 0; i < game->renderer->max_texture; i++)
		samplers[i] = i;

	// Providing samplers to the shader
	glUseProgram(game->shader);
	int loc = glGetUniformLocation(game->shader, "textures");
	if (loc == -1)
	{
		fprintf(stderr, "[Error]: Cannot find uniform `textures` in the shader.\n");
		exit(1);
	}
	GLCall(glUniform1iv(loc, game->renderer->max_texture, samplers));
	
	// Setting up gl view port
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
}

void game_event(Game* game)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game->running = false;
		}
	}
}

void game_run(Game* game)
{
	while (game->running)
	{
		gln_clear_window(game->window, background);
		game_event(game);

		glUseProgram(game->shader);
		ortho_cam_update(game->camera, game->shader);

		// Rendering
		gln_render_begin(game->renderer);
		map_render(game->map, game->renderer);
		gln_render_end(game->renderer);

		gln_update_window(game->window);
	}
}

void game_exit(Game* game)
{
	gln_destroy_renderer(game->renderer);
	gln_destroy_window(game->window);
	free(game);
}
