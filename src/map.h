#ifndef _MAP_H_
#define _MAP_H_

#include "gln.h"

typedef struct
{
	vec3f pos;
	vec2f size;
	int   type;
} Tile;

typedef struct
{
	void* left;
	void* right;
	void* up;
	void* down;

	// Map
	Tile** tile_map;
	int    map_sz;
	char*  raw_map;
} Room;

Room* room_new();

typedef struct
{
	Room** rooms;
	int room_cnt;
} Map;

Map* map_new();
void map_destroy(Map* map);

#endif
