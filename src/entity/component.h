#ifndef _COMPONENT_H_
#define _COMPONENT_H_

//NOTE: These components can cause memory leaks so be carefull

#include "gln.h"

// Components names
#define RENDER_COMPONENT "<render_component>"
#define CONTROLLER_COMPONENT "<controller_component>"
#define ANIMATION_COMPONENT "<animation_component>"


/*
 * Entity Render Component:
 * - Deals with the rendering of the entities
 */

typedef struct
{
	GLNRenderer* renderer;
	vec4f color;
	vec4f tex_cord;
	GLNTexture texture;
} RenderComponentStruct;

RenderComponentStruct* render_component(GLNRenderer* renderer, vec4f color, vec4f tex_cord, GLNTexture texture);

/*
 * Entity Controller Component:
 * - Adds TOPDOWN player controller to the entity
 */

typedef struct
{
	float speed;
	bool move_up, move_down, move_left, move_right;
} ControllerComponentStruct;

ControllerComponentStruct* controller_component(float speed);

/*
 * Entity Animation Component:
 * - Adds animation to the entity
 */

typedef struct
{
	Dict* database;
	char curr_frame[256];
	float idx;
	float speed;
} AnimationComponentStruct;

AnimationComponentStruct* animation_component(char* def_frame, float speed);
void animation_add_frame(AnimationComponentStruct* animation, char* frame_name, List* tex_cords);
void animation_change_frame(AnimationComponentStruct* animation, char* frame);
vec4f* animation_get_frame(AnimationComponentStruct* animation);


#endif
