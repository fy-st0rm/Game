#include "game.h"

Game* game_new()
{
	Game* game = (Game*) malloc(sizeof(Game));
	game->window = gln_create_window(WIN_TITLE, WIN_WIDTH, WIN_HEIGHT);
	game->renderer = gln_create_renderer(MAX_QUADS);
	game->shader = gln_load_shader(VERT_SHADER, FRAG_SHADER);

	vec3f pos = { 0.0f, 0.0f, 0.0f };

	// Creating camera
	game->cam_pos = malloc(sizeof(vec3f));
	memcpy(game->cam_pos, &pos, sizeof(pos));
	game->camera = ortho_cam_new(pos, 0.0f, ZOOM_WIDTH, ZOOM_HEIGHT, 0.0f, 1000.0f, -100.0f);

	// Creating player
	game->player = player_new(game->window, pos);

	// Allocating mouse position
	game->mouse_pos = malloc(sizeof(vec2f));
	memcpy(game->mouse_pos, &pos, sizeof(pos));

	// Creating map
	game->map = map_new(game->window);
	load_map(game->map, "test.txt");
	load_tiles(game->map);

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
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game->running = false;
		}
		player_event(game->player, event);
	}
}

void game_calc_mouse_pos(Game* game)
{
	int x, y, fx, fy, cam_x, cam_y;
	SDL_GetMouseState(&x, &y);

	// Getting the mouse position of the zoomed surface
	int ratio_x = WIN_WIDTH / ZOOM_WIDTH;
	int ratio_y = WIN_HEIGHT / ZOOM_HEIGHT;
	x /= ratio_x;
	y /= ratio_y;
	
	// Converting the opengl camera position to the pixel position 
	cam_x = (int)(game->camera->pos->x * ZOOM_WIDTH / 2);
	cam_y = (int)(game->camera->pos->y * ZOOM_HEIGHT / 2);

	// Calculating the final mouse position with the camera's position offset and dividing by tiles size to get mouse position in grid
	game->mouse_pos->x = (int)((x + cam_x) / (TILE_W));
	game->mouse_pos->y = (int)((y - cam_y) / (TILE_H));
}

void game_run(Game* game)
{
	// Frame stuff
	int fps = 60;
	int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;

	while (game->running)
	{
		frame_start = SDL_GetTicks();

		gln_clear_window(game->window, background);
		game_event(game);

		// Updating camera
		vec2f offset = {1, -1};

		glUseProgram(game->shader);
		ortho_cam_follow(game->camera, game->player->cam_pos, offset);
		ortho_cam_update(game->camera);
		ortho_cam_update_shader(game->camera, game->shader);

		// Calculating mouse position
		game_calc_mouse_pos(game);

		// Rendering
		gln_render_begin(game->renderer);
		map_render(game->map, game->renderer, game->mouse_pos);
		player_render(game->player, game->renderer);
		gln_render_end(game->renderer);

		// Caping the frame
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
		{
			SDL_Delay(frame_delay - frame_time);		
		}

		// Updating window
		gln_update_window(game->window);
	}
}

void game_exit(Game* game)
{
	free(game->mouse_pos);
	free(game->cam_pos);

	player_clean(game->player);
	map_destroy(game->map);
	ortho_cam_destroy(game->camera);
	gln_destroy_renderer(game->renderer);
	gln_destroy_window(game->window);

	free(game);
}
