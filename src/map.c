#include "map.h"

//TODO: Load Game Map 
//TODO: Isometric rendering

Map* map_new(GLNWindow* window)
{
	Map* map = malloc(sizeof(Map));
	map->texture = gln_load_texture(window, TILES);
	map->tex_cnt = 3;
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

	// Generating tile map buffer
	map->tile_map = malloc(strlen(map->raw_map) * 2 * sizeof(Tile));

	// Creating tiles
	for (int i = 0; i < strlen(map->raw_map); i++)
	{
		Tile* new_tile = malloc(sizeof(Tile));
		char id = map->raw_map[i];

		switch (id)
		{
			case '1':
				new_tile->type = GRASS;
				break;
			case '2':
				new_tile->type = PATH;
				break;
			case '3':
				new_tile->type = WATER;
				break;
			case '\n':
				new_tile->type = NONE;
				break;
			default:
				fprintf(stderr, "[Error]: Unknown tile id `%c`\n", id);
				exit(1);
				break;
		}
		map->tile_map[i] = new_tile;
	}
}

void map_render(Map* map, GLNRenderer* renderer)
{
	vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec2f  size = { 31.0f, 31.0f };

	float in_x = 100.0f, in_y = 100.0f;
	float x = in_x, y = in_y;
	float w = 0, h = in_y; 

	for (int i = 0; i < strlen(map->raw_map); i++)
	{
		Tile* tile = map->tile_map[i];
		if (tile->type)
		{
			vec4f* tex 	= dict_get(map->tex_dict, tile->type);
			vec3f  pos 	= { x, y, 0.0f };
		
			// Enlarging the vertices
			mat4f enlarge = {0};
			mat4f_enlarge(&enlarge, 2.0f);

			Quad* quad = gln_create_quad(renderer, pos, size, color, *tex, map->texture.id);
			mat4f_quad_mul(enlarge, quad);
			gln_push_quad(renderer, quad);
			gln_destroy_quad(quad);

			x -= 15.0f;
			y += 7.0f;
		}
		else 
		{
			x = in_x + w + 15.0f;
			y = h + 7.0f;
			w += 15.0f;
			h += 7.5f;
		}
	}
}	
