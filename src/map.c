#include "map.h"

Room* room_new()
{
	
}

Map* map_new()
{
	Map* map = malloc(sizeof(Map));
	return map;
}

void map_destroy(Map* map)
{
	for (int i = 0; i < map->room_cnt; i++)
	{
		// TODO: destroy rooms here
	}
	free(map);
}
