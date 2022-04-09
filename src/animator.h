#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "gln.h"

typedef struct
{
	Dict* database;
	char curr_frame[256];
	float idx;
	float speed;
} Animator;

Animator* animator_new(char* frame, float speed);
void animator_clean(Animator* animator);
void animator_change_frame(Animator* animator, char* frame);
void animator_insert(Animator* animator, char* frame_name, List* tex_cords);
vec4f* animator_get_frame(Animator* animator);

#endif
