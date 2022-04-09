#include "player.h"

Player* player_new(GLNWindow* window, vec3f position)
{
	vec2f size  = { 16.0f, 16.0f };
	vec4f color = {1.0f, 1.0f, 1.0f, 1.0f};

	Player* player = malloc(sizeof(Player));
	player->position = position;
	player->cam_pos.x = player->position.x / (ZOOM_WIDTH / 2);
	player->cam_pos.y = player->position.y / (ZOOM_HEIGHT / 2);
	player->cam_pos.z = 0;

	// Player default constants
	player->size = size;
	player->color = color;
	player->texture = gln_load_texture(window, PLAYER_TEXTURE);
	player->speed = 3.0f;

	player->move_left = player->move_right = player->move_up = player->move_down = false;
	return player;
}

void player_clean(Player* player)
{
	free(player);
}

void player_event(Player* player, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a:
				player->move_left = true;
				break;
			case SDLK_d:
				player->move_right = true;
				break;
			case SDLK_w:
				player->move_up = true;
				break;
			case SDLK_s:
				player->move_down = true;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a:
				player->move_left = false;
				break;
			case SDLK_d:
				player->move_right = false;
				break;
			case SDLK_w:
				player->move_up = false;
				break;
			case SDLK_s:
				player->move_down = false;
				break;
		}
	}
}

void player_render(Player* player, GLNRenderer* renderer)
{
	// Updating movement
	if (player->move_left)
	{
		player->position.x -= player->speed;
	}
	if (player->move_right)
	{
		player->position.x += player->speed;
	}
	if (player->move_up)
	{
		player->position.y -= player->speed;
	}
	if (player->move_down)
	{
		player->position.y += player->speed;
	}

	// Temporaray texture coords
	vec4f tex = {0.0f, 0.0f, 1.0f/6.0f, 1.0f};

	// Calculating the position for camera to follow (Opengl cords)
	player->cam_pos.x = player->position.x / (ZOOM_WIDTH / 2);
	player->cam_pos.y = -player->position.y / (ZOOM_HEIGHT / 2);
	player->cam_pos.z = 0.0f;

	// Rendering the quad
	Quad* quad = gln_create_quad(renderer, player->position, player->size, player->color, tex, player->texture.id);
	gln_push_quad(renderer, quad);
	gln_destroy_quad(quad);
}
