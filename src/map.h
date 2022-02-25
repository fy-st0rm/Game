#ifndef _MAP_H_
#define _MAP_H_

#include "gln.h"
#include "global.h"

enum tile_types
{
	GRASS,
	PATH,
	WATER
};

typedef struct
{
	int type;
} Tiles;

typedef struct
{
	GLNTexture texture;
	Dict* tex_dict;
	int tex_cnt;
	Tiles* map[100];
} Map;

Map* map_new(GLNWindow* window);
void map_render(Map* map, GLNRenderer* renderer);

#endif 
