#include "map.h"

Map* map_new(GLNWindow* window)
{
	Map* map = malloc(sizeof(Map));
	map->texture = gln_load_texture(window, TILES);
	map->tex_cnt = 3;
	map->map_sz = 0;
	map->tex_dict = dict_new(map->tex_cnt);

	vec4f grass = { 0.0 / map->tex_cnt, 0.0, 1.0 / map->tex_cnt, 1.0 };
	vec4f path  = { 1.0 / map->tex_cnt, 0.0, 1.0 / map->tex_cnt, 1.0 };
	vec4f water = { 2.0 / map->tex_cnt, 0.0, 1.0 / map->tex_cnt, 1.0 };

	dict_insert(map->tex_dict, (void*) GRASS, (void*) &grass, sizeof(grass));
	dict_insert(map->tex_dict, (void*) PATH , (void*) &path , sizeof(path));
	dict_insert(map->tex_dict, (void*) WATER, (void*) &water, sizeof(water));

	return map;
}

void load_map(Map* map, char* file)
{
	char* temp_map = load_file(file);
	map->raw_map = calloc(strlen(temp_map), sizeof(char));

	// Copying the world map in a reversed order
	int offset = 0;
	char* line = strtok(temp_map, "\n");
	while (line != NULL)
	{
		strrev(line);
		strcpy(map->raw_map + offset, line);
		offset += strlen(line);
		strcpy(map->raw_map + offset++, "\n");
		line = strtok(NULL, "\n");
	}
	free(line);
	free(temp_map);
}

void load_tiles(Map* map)
{
	// Generating tile map buffer
	map->tile_map = malloc(strlen(map->raw_map) * 2 * sizeof(Tile));

	// Generating tiles
	vec2f size = { 31.0f, 31.0f };
	
	float x = 0.0f, y = 0.0f;
	float in_x = 0.0f, in_y = 0.0f;

	for (int i = 0; i < strlen(map->raw_map); i++)
	{
		vec3f  pos 	= { x, y, 0.0f };
		x--;
		y++;

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
				x = ++in_x;
				y = ++in_y;
				break;
			default:
				fprintf(stderr, "[Error]: Unknown tile id `%c`\n", id);
				exit(1);
				break;
		}
	}
}

void map_render(Map* map, GLNRenderer* renderer)
{
	vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

	for (int i = 0; i < map->map_sz; i++)
	{
		Tile* tile = map->tile_map[i];
		vec4f* tex = dict_get(map->tex_dict, tile->type);
		vec3f  pos = tile->pos;
		vec2f size = tile->size;
		pos.x *=  15.0f;
		pos.y *= 7.0f;

		// Enlarging the vertices
		mat4f enlarge = {0};
		mat4f_enlarge(&enlarge, 2.0f);

		Quad* quad = gln_create_quad(renderer, pos, size, color, *tex, map->texture.id);
		mat4f_quad_mul(enlarge, quad);
		gln_push_quad(renderer, quad);
		gln_destroy_quad(quad);
	}
}	
