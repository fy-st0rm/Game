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
	player->turn_left = player->turn_right = false;
	player->theta = 0.0f;
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
				player->turn_left = true;
				player->turn_right = false;
				break;
			case SDLK_d:
				player->move_right = true;
				player->turn_right = true;
				player->turn_left = false;
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

void player_handle_movement(Player* player)
{
	// Managing the angle of rotation
	if (player->turn_left)
	{
		if (player->theta < MAX_LEFT_ROT)
			player->theta += ROT_SPEED;
		else
			player->turn_left = false;
	}
	if (player->turn_right)
	{
		if (player->theta > MAX_RIGHT_ROT)
			player->theta -= ROT_SPEED;
		else
			player->turn_right = false;
	}

	// Updating movement
	if (!player->turn_left && !player->turn_right)
	{
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
	}
}

void player_render(Player* player, GLNRenderer* renderer)
{
	// Temporaray texture coords
	vec4f tex = {0.0f, 0.0f, 1.0f, 1.0f};

	// Calculating the position for camera to follow (Opengl cords)
	player->cam_pos.x = player->position.x / (ZOOM_WIDTH / 2);
	player->cam_pos.y = -player->position.y / (ZOOM_HEIGHT / 2);
	player->cam_pos.z = 0.0f;

	// Passing the origin for the rotation as rotation occurs with origin
	vec3f pos = {0.0f, 0.0f, 0.0f};
	Quad* quad = gln_create_quad(renderer, pos, player->size, player->color, tex, player->texture.id);

	// Multiplying the quad with rotation matrix 
	mat4f yrot = {0};
	rotation_y(&yrot, player->theta);
	mat4f_quad_mul(yrot, quad);

	// Shifting the quad to its original position
	for (int i = 0; i < 4; i++)
	{
		quad->v[i].pos.x += player->position.x;
		quad->v[i].pos.y += player->position.y;
	}

	// Handling movement
	player_handle_movement(player);
	
	gln_push_quad(renderer, quad);
	gln_destroy_quad(quad);
}
