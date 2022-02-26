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

void map_render(Map* map, GLNRenderer* renderer)
{
	vec3f pos1 = { 100.0f, 100.0f, 0.0f };
	vec3f pos2 = { 250.0f, 100.0f, 0.0f };
	vec3f pos3 = { 400.0f, 100.0f, 0.0f };
	vec2f size = { 100.0f , 100.0f };
	vec4f color = { 1.0f, 1.0f, 1.0f, 1.0f };

	vec4f* gt = dict_get(map->tex_dict, (void*)GRASS);
	Quad* grass = gln_create_quad(renderer, pos1, size, color, *gt, map->texture.id);

	vec4f* pt = dict_get(map->tex_dict, (void*)PATH);
	Quad* path = gln_create_quad(renderer, pos2, size, color, *pt, map->texture.id);

	vec4f* wt = dict_get(map->tex_dict, (void*)WATER);
	Quad* water = gln_create_quad(renderer, pos3, size, color, *wt, map->texture.id);

	gln_push_quad(renderer, grass);
	gln_push_quad(renderer, path);
	gln_push_quad(renderer, water);
}	
