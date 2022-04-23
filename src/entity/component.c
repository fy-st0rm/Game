#include "component.h"

/*
 * Entity Render Component
 */

RenderComponentStruct* render_component(GLNRenderer* renderer, vec4f color, vec4f tex_cord, GLNTexture texture)
{
	RenderComponentStruct* component = malloc(sizeof(RenderComponentStruct));
	component->renderer = renderer;
	component->color = color;
	component->tex_cord = tex_cord;
	component->texture = texture;
	return component;
}

/*
 * Entity Controller Component
 */

ControllerComponentStruct* controller_component(float speed)
{
	ControllerComponentStruct* component = malloc(sizeof(ControllerComponentStruct));
	component->speed = speed;
	component->move_up = false;
	component->move_down = false;
	component->move_left = false;
	component->move_right = false;
	return component;
}

/*
 * Animation Component
 */

AnimationComponentStruct* animation_component(char* def_frame, float speed)
{
	AnimationComponentStruct* component = malloc(sizeof(AnimationComponentStruct));
	component->database = dict_new();
	strcpy(component->curr_frame, def_frame);
	component->idx = 0.0f;
	component->speed = speed;
	return component;
}

void animation_add_frame(AnimationComponentStruct* animation, char* frame_name, List* tex_cords)
{
	dict_insert(animation->database, (void*) frame_name, (void*) tex_cords, sizeof(char) * strlen(frame_name), tex_cords->size * tex_cords->size); 
}

void animation_change_frame(AnimationComponentStruct* animation, char* frame)
{
	if (strcmp(animation->curr_frame, frame)) 
	{
		strcpy(animation->curr_frame, frame);
		animation->idx = 0.0f;
	}
}

vec4f* animation_get_frame(AnimationComponentStruct* animation)
{
	List* list = dict_get(animation->database, (void*) animation->curr_frame, sizeof(char) * strlen(animation->curr_frame));
	vec4f* cords = list_get(list, (int)round(animation->idx));

	animation->idx += 1.0f / animation->speed;
	if ((int)round(animation->idx) >= list->len)
		animation->idx = 0.0f;

	return cords;
}


