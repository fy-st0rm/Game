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
	vec3f pos;
	vec2f size;
	int   type;
} Tile;

typedef struct
{
	GLNTexture texture;
	Dict* tex_dict;
	int tex_cnt;

	Tile** tile_map;
	int    map_sz;
	char*  raw_map;
} Map;

Map* map_new(GLNWindow* window);
void load_map(Map* map, char* file);
void load_tiles(Map* map);
void map_render(Map* map, GLNRenderer* renderer, vec2f* mouse_pos);
void map_destroy(Map* map);

#endif 
