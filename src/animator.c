#include "animator.h"

Animator* animator_new(char* frame, float speed)
{
	Animator* animator = malloc(sizeof(Animator));
	animator->database = dict_new();
	animator->idx = 0.0f;
	animator->speed = speed;
	strcpy(animator->curr_frame, frame);
	return animator;
}

void animator_clean(Animator* animator)
{
	// TODO: Here might be memory leak of the list stored in database be aware.
	dict_clean(animator->database);
}

void animator_insert(Animator* animator, char* frame_name, List* tex_cords)
{
	dict_insert(animator->database, (void*) frame_name, (void*) tex_cords, sizeof(char) * strlen(frame_name), tex_cords->size * tex_cords->size); 
}

void animator_change_frame(Animator* animator, char* frame)
{
	strcpy(animator->curr_frame, frame);
	animator->idx = 0.0f;
}

vec4f* animator_get_frame(Animator* animator)
{
	List* list = dict_get(animator->database, (void*) animator->curr_frame, sizeof(char) * strlen(animator->curr_frame));
	vec4f* cords = list_get(list, (int)round(animator->idx));

	animator->idx += 1.0f / animator->speed;
	if ((int)round(animator->idx) >= list->len)
		animator->idx = 0.0f;

	return cords;
}
