#include "entity.h"

Entity* entity_new(vec3f pos, vec2f size, float vel_x, float vel_y)
{
	Entity* entity = malloc(sizeof(Entity));
	entity->pos = pos;
	entity->size = size;
	entity->vel_x = vel_x;
	entity->vel_y = vel_y;
	entity->rot_ang = 0.0f;

	entity->turn_left = false;
	entity->turn_right = false;
	entity->face_down = true;
	entity->face_up = false;

	entity->components = dict_new();
	return entity;
}

void entity_destroy(Entity* entity)
{
	dict_clean(entity->components);
	free(entity);
}

void entity_add_component(Entity* entity, char* name, void* component, size_t comp_size)
{
	dict_insert(entity->components, (void*)name, component, sizeof(char) * strlen(name), comp_size); 
}

void* entity_get_component(Entity* entity, char* name)
{
	return dict_get(entity->components, (void*)name, sizeof(char) * strlen(name));
}

vec3f entity_get_gl_pos(Entity* entity, int screen_width, int screen_height)
{
	vec3f pos = {
		entity->pos.x / (screen_width / 2),
	   -entity->pos.y / (screen_height / 2),
		0.0f
	};
	return pos;
}

// Component based entity functions
void entity_render(Entity* entity)
{
	vec3f pos = { 0.0f, 0.0f, 0.0f }; // Position is added to zero for the rotation of the entity along the origin
 
	RenderComponentStruct* ren_comp = dict_get(entity->components, RENDER_COMPONENT, sizeof(char) * strlen(RENDER_COMPONENT));
	Quad* quad = gln_create_quad(ren_comp->renderer, pos, entity->size, ren_comp->color, ren_comp->tex_cord, ren_comp->texture.id);

	// Multiplying the quad with rotation matrix 
	mat4f yrot = {0};
	rotation_y(&yrot, entity->rot_ang);
	mat4f_quad_mul(yrot, quad);

	// Shifting the quad to its original position
	for (int i = 0; i < 4; i++)
	{
		quad->v[i].pos.x += entity->pos.x;
		quad->v[i].pos.y += entity->pos.y;
	}

	gln_push_quad(ren_comp->renderer, quad);
	gln_destroy_quad(quad);
}

void entity_controller_event(Entity* entity, SDL_Event event)
{
	ControllerComponentStruct* con_comp = dict_get(entity->components, CONTROLLER_COMPONENT, sizeof(char) * strlen(CONTROLLER_COMPONENT));

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a:
				con_comp->move_left = true;
				entity->turn_left = true;
				entity->turn_right = false;
				break;
			case SDLK_d:
				con_comp->move_right = true;
				entity->turn_left = false;
				entity->turn_right = true;
				break;
			case SDLK_w:
				con_comp->move_up = true;
				entity->face_up = true;
				entity->face_down = false;
				break;
			case SDLK_s:
				con_comp->move_down = true;
				entity->face_up = false;
				entity->face_down = true;
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_a:
				con_comp->move_left = false;
				break;
			case SDLK_d:
				con_comp->move_right = false;
				break;
			case SDLK_w:
				con_comp->move_up = false;
				break;
			case SDLK_s:
				con_comp->move_down = false;
				break;
		}
	}
}

void entity_controller_movement(Entity* entity)
{
	ControllerComponentStruct* con_comp = dict_get(entity->components, CONTROLLER_COMPONENT, sizeof(char) * strlen(CONTROLLER_COMPONENT));
	
	if (con_comp->move_left)
	{
		entity->pos.x -= con_comp->speed;
	}
	if (con_comp->move_right)
	{
		entity->pos.x += con_comp->speed;
	}
	if (con_comp->move_up)
	{
		entity->pos.y -= con_comp->speed;
	}
	if (con_comp->move_down)
	{
		entity->pos.y += con_comp->speed;
	}
}
