#ifndef _MAP_H_
#define _MAP_H_

#include "gln.h"
#include "global.h"

enum tile_types
{
	NONE,
	GRASS,
	PATH ,
	WATER
};

typedef struct
{
	int type;
} Tile;

typedef struct
{
	GLNTexture texture;
	Dict* tex_dict;
	int tex_cnt;

	Tile** tile_map;
	char*  raw_map;
} Map;

Map* map_new(GLNWindow* window);
void load_map(Map* map, char* file);
void map_render(Map* map, GLNRenderer* renderer);

#endif 
