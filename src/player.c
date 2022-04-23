#include "player.h"

Entity* player_new(GLNWindow* window, GLNRenderer* renderer)
{
	// Variables for the construction of entity
	vec3f pos = { 0.0f, 0.0f, 0.0f };
	vec2f size  = { 16.0f, 16.0f };
	float speed = 3.0f;

	vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f tex_cord = { 0.0f, 0.0f, 1.0f / 2.0f, 1.0f / 5.0f};
	GLNTexture texture = gln_load_texture(window, PLAYER_TEXTURE);

	// Construction of player entity
	Entity* player = entity_new(pos, size, 0.0f, 0.0f);
	entity_add_component(player, RENDER_COMPONENT, render_component(renderer, color, tex_cord, texture), sizeof(RenderComponentStruct));
	entity_add_component(player, CONTROLLER_COMPONENT, controller_component(speed), sizeof(ControllerComponentStruct));
	entity_add_component(player, ANIMATION_COMPONENT, animation_component(IDLE_DOWN, IDLE_SPEED), sizeof(AnimationComponentStruct));

	player_init_frames(player);
	return player;
}

void player_init_frames(Entity* player)
{
	AnimationComponentStruct* animation = entity_get_component(player, ANIMATION_COMPONENT);

	// TODO: Lists are now freed here make sure to free it
	// IDLE SPRITE CORDS
	vec4f idle_down_1 = {0.0f / SPRITE_WIDTH, 0.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f idle_down_2 = {1.0f / SPRITE_WIDTH, 0.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f idle_up_1   = {0.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f idle_up_2   = {1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};

	List* list_1 = list_new();
	list_append(list_1, (void*) &idle_down_1, sizeof(idle_down_1));
	list_append(list_1, (void*) &idle_down_2, sizeof(idle_down_2));
	animation_add_frame(animation, IDLE_DOWN, list_1);

	List* list_2 = list_new();
	list_append(list_2, (void*) &idle_up_1, sizeof(idle_up_1));
	list_append(list_2, (void*) &idle_up_2, sizeof(idle_up_2));
	animation_add_frame(animation, IDLE_UP, list_2);

	// Walk sprite coords
	vec4f walk_down_1 = {0.0f / SPRITE_WIDTH, 0.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_down_2 = {0.0f / SPRITE_WIDTH, 2.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_down_3 = {1.0f / SPRITE_WIDTH, 2.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_down_4 = {0.0f / SPRITE_WIDTH, 3.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};

	vec4f walk_up_1 = {0.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_up_2 = {1.0f / SPRITE_WIDTH, 3.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_up_3 = {0.0f / SPRITE_WIDTH, 4.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};
	vec4f walk_up_4 = {1.0f / SPRITE_WIDTH, 4.0f / SPRITE_HEIGHT, 1.0f / SPRITE_WIDTH, 1.0f / SPRITE_HEIGHT};

	List* list_3 = list_new();
	list_append(list_3, (void*) &walk_down_1, sizeof(walk_down_1));
	list_append(list_3, (void*) &walk_down_2, sizeof(walk_down_2));
	list_append(list_3, (void*) &walk_down_3, sizeof(walk_down_3));
	list_append(list_3, (void*) &walk_down_4, sizeof(walk_down_4));
	animation_add_frame(animation, WALK_DOWN, list_3);

	List* list_4 = list_new();
	list_append(list_4, (void*) &walk_up_1, sizeof(walk_up_1));
	list_append(list_4, (void*) &walk_up_2, sizeof(walk_up_2));
	list_append(list_4, (void*) &walk_up_3, sizeof(walk_up_3));
	list_append(list_4, (void*) &walk_up_4, sizeof(walk_up_4));
	animation_add_frame(animation, WALK_UP, list_4);
}

void player_update_animation(Entity* player)
{
	// Animations
	AnimationComponentStruct* animation = entity_get_component(player, ANIMATION_COMPONENT);
	RenderComponentStruct*    ren_comp  = entity_get_component(player, RENDER_COMPONENT);
	ControllerComponentStruct* con_comp = entity_get_component(player, CONTROLLER_COMPONENT);

	vec4f* tex = animation_get_frame(animation);
	ren_comp->tex_cord = *tex;

	if (con_comp->move_left || con_comp->move_right)
	{
		animation->speed = WALK_SPEED;
		if (player->face_down)
			animation_change_frame(animation, WALK_DOWN);
		else if (player->face_up)
			animation_change_frame(animation, WALK_UP);
	}
	if (con_comp->move_up)
	{
		animation->speed = WALK_SPEED;
		animation_change_frame(animation, WALK_UP);
	}
	if (con_comp->move_down)
	{
		animation->speed = WALK_SPEED;
		animation_change_frame(animation, WALK_DOWN);
	}
	if (!con_comp->move_left && !con_comp->move_right && !con_comp->move_up && !con_comp->move_down)
	{
		animation->speed = IDLE_SPEED;
		if (player->face_up)
			animation_change_frame(animation, IDLE_UP);
		else if (player->face_down)
			animation_change_frame(animation, IDLE_DOWN);
	}
}

void player_update_movement(Entity* player)
{
	// Managing the angle of rotation
	if (player->turn_left)
	{
		if (player->rot_ang < MAX_LEFT_ROT)
			player->rot_ang += ROT_SPEED;
		else
			player->turn_left = false;
	}
	if (player->turn_right)
	{
		if (player->rot_ang > MAX_RIGHT_ROT)
			player->rot_ang -= ROT_SPEED;
		else
			player->turn_right = false;
	}

	//if (!player->turn_left && !player->turn_right)
	entity_controller_movement(player);
}

void player_render(Entity* player)
{
	player_update_animation(player);
	player_update_movement(player);
	entity_render(player);
}
