#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "component.h"

typedef struct
{
	// Positional components
	vec3f pos;
	vec2f size;
	float vel_x;
	float vel_y;
	float rot_ang;

	// Movement flags
	bool turn_left, turn_right, face_up, face_down;

	Dict* components;
} Entity;

Entity* entity_new(vec3f pos, vec2f size, float vel_x, float vel_y);
void	entity_destroy(Entity* entity);
void    entity_add_component(Entity* entity, char* name, void* component, size_t comp_size);
void*   entity_get_component(Entity* entity, char* name);
vec3f   entity_get_gl_pos(Entity* entity, int screen_width, int screen_height);

// Special functions for the components
void	entity_render(Entity* entity);
void    entity_controller_event(Entity* entity, SDL_Event event);
void    entity_controller_movement(Entity* entity);

#endif
