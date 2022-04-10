#include "map.h"

Map* map_new(GLNWindow* window)
{
	Map* map = malloc(sizeof(Map));
	map->texture = gln_load_texture(window, TILES);
	map->tex_cnt = TILE_CNT;
	map->map_sz = 0;
	map->tex_dict = dict_new();

	vec4f grass = { 0.0f / 2.0f, 0.0f / 2.0f, 1.0 / 2.0f, 1.0 / map->tex_cnt};
	vec4f path  = { 1.0f / 2.0f, 0.0f / 2.0f, 1.0 / 2.0f, 1.0 / map->tex_cnt};
	vec4f water = { 0.0f / 2.0f, 2.0f / 2.0f, 1.0 / 2.0f, 1.0 / map->tex_cnt};

	dict_insert(map->tex_dict, (void*) &GRASS, (void*) &grass, sizeof(GRASS), sizeof(grass));
	dict_insert(map->tex_dict, (void*) &PATH , (void*) &path , sizeof(PATH),  sizeof(path));
	dict_insert(map->tex_dict, (void*) &WATER, (void*) &water, sizeof(WATER), sizeof(water));

	return map;
}

void load_texture(Map* map)
{
}

void load_map(Map* map, char* file)
{
	map->raw_map = load_file(file);
}

void load_tiles(Map* map)
{
	// Generating tile map buffer
	map->tile_map = malloc(strlen(map->raw_map) * 2 * sizeof(Tile));

	// Generating tiles
	vec2f size = { TILE_W, TILE_H };
	
	float x = 0.0f, y = 0.0f;

	for (int i = 0; i < strlen(map->raw_map); i++)
	{
		vec3f pos = { x, y, 0.0f };
		x++;

		char id = map->raw_map[i];

		switch (id)
		{
			case '1': 
			{
				Tile* new_tile = malloc(sizeof(Tile));
				new_tile->pos  = pos;
				new_tile->size = size;
				new_tile->type = GRASS;
				map->tile_map[map->map_sz++] = new_tile;
				break;
			}
			case '2':
			{
				Tile* new_tile = malloc(sizeof(Tile));
				new_tile->pos  = pos;
				new_tile->size = size;
				new_tile->type = PATH;
				map->tile_map[map->map_sz++] = new_tile;
				break;
			}
			case '3':
			{
				Tile* new_tile = malloc(sizeof(Tile));
				new_tile->pos  = pos;
				new_tile->size = size;
				new_tile->type = WATER;
				map->tile_map[map->map_sz++] = new_tile;
				break;
			}
			case '0':
				break;
			case '\n':
				y++;
				x = 0.0f;
				break;
			default:
				fprintf(stderr, "[Error]: Unknown tile id `%c`\n", id);
				exit(1);
				break;
		}
	}
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
