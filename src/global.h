#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "gln.h"

#define MAX_QUADS 1000
static vec4f background = { 0.0f, 0.0f, 0.0f, 1.0f };

// Constant window variables
#define WIN_TITLE  "game"
#define WIN_WIDTH  800
#define WIN_HEIGHT 600

// Shaders
#define VERT_SHADER "../shader/shader.vert"
#define FRAG_SHADER "../shader/shader.frag"

// Paths
#define TILES "../assets/tiles.png"

#endif
