#include "map.h"

// Procedure infinite map? Or a limited procedure map? IDK ;-;

Map* map_new(GLNWindow* window)
{
	Map* map = malloc(sizeof(Map));
	map->texture = gln_load_texture(window, TILES);
	map->tex_cnt = 3;
	map->map_sz = 0;
	map->tex_dict = dict_new();

	map_load_textures(map);
	return map;
}

void map_load_textures(Map* map)
{
	int idx = 0;
	for (float y = 0.0f; y < TILE_Y_CNT; y++)
	{
		for (float x = 0.0f; x < TILE_X_CNT; x++)
		{
			vec4f pos = {x / TILE_X_CNT, y / TILE_Y_CNT, 1.0f / TILE_X_CNT, 1.0f / TILE_Y_CNT};
			dict_insert(map->tex_dict, (void*) &idx, (void*) &pos, sizeof(idx), sizeof(pos));
			idx++;
		}
	}
}

void load_map(Map* map, char* file)
{
	map->raw_map = load_file(file);
}

void load_tiles(Map* map)
{
	// Generating tile map buffer
	map->tile_map = malloc(strlen(map->raw_map) * 2 * sizeof(Tile));

	// Copying to temp storage
	char temp_map[strlen(map->raw_map)];
	strcpy(temp_map, map->raw_map);

	// Generating tiles
	float x = 0.0f, y = 0.0f;
	vec2f size = { TILE_W, TILE_H };
	
	// Storing lines
	List* lines = list_new();
	char* line = strtok(temp_map, "\n");
	while (line != NULL)
	{
		list_append(lines, (void*) line, sizeof(char) * strlen(line));
		line = strtok(NULL, "\n");
	}

	// Converting digits to the corresponding tile
	for (int i = 0; i < lines->len; i++)
	{
		char* line = list_get(lines, i);
		char* digit = strtok(line, ",");
		while (digit != NULL)
		{
			vec3f pos = { x, y, 0.0f };
			x++;

			int idx = atoi(digit);
			Tile* new_tile = malloc(sizeof(Tile));
			new_tile->pos  = pos;
			new_tile->size = size;
			new_tile->type = idx;
			map->tile_map[map->map_sz++] = new_tile;

			digit = strtok(NULL, ",");
		}
		x = 0;
		y++;
	}

	list_clean(lines);
}

void map_render(Map* map, GLNRenderer* renderer, vec2f* mouse_pos)
{
	vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

	for (int i = 0; i < map->map_sz; i++)
	{
		Tile* tile = map->tile_map[i];
		vec4f* tex = dict_get(map->tex_dict, (void*) &tile->type, sizeof(tile->type));
		vec3f  pos = tile->pos;
		vec2f size = tile->size;
		pos.x *= size.x;
		pos.y *= size.y;

		Quad* quad = gln_create_quad(renderer, pos, size, color, *tex, map->texture.id);
		gln_push_quad(renderer, quad);
		gln_destroy_quad(quad);

		if ((int)mouse_pos->x == tile->pos.x && (int)mouse_pos->y == tile->pos.y)
		{
			vec4f t = {0, 0, 0, 0};
			vec4f c = {1.0f, 1.0f, 0.0f, 0.5f};
			Quad* quad = gln_create_quad(renderer, pos, size, c, t, 0);
			gln_push_quad(renderer, quad);
			gln_destroy_quad(quad);
		}
	}
}

void map_destroy(Map* map)
{
	for (int i = 0; i < map->map_sz; i++)
		free(map->tile_map[i]);
	free(map->tile_map);
	free(map->raw_map);
	dict_clean(map->tex_dict);
	free(map);
}
