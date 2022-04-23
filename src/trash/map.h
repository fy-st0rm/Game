#ifndef _MAP_H_
#define _MAP_H_

#include "gln.h"
#include "global.h"

#define TILES "../assets/Sprite_1.png"
#define TILE_W 16
#define TILE_H 16
#define TILE_X_CNT 6
#define TILE_Y_CNT 6

static int NONE = 0;
static int GRASS = 1;
static int PATH = 2;
static int WATER = 3;

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
void map_load_textures(Map* map);
void load_map(Map* map, char* file);
void load_tiles(Map* map);
void map_render(Map* map, GLNRenderer* renderer, vec2f* mouse_pos);
void map_destroy(Map* map);

#endif 
