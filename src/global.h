#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "gln.h"

#define MAX_QUADS 1000
static vec4f background = { 0.5f, 0.5f, 0.5f, 1.0f };

#define CAM_SPEED 0.1f
#define SCALE     3.0f
 
// Constant window variables
#define WIN_TITLE   "game"
#define WIN_WIDTH   800
#define WIN_HEIGHT  600
#define ZOOM_WIDTH  (int)(WIN_WIDTH / SCALE)
#define ZOOM_HEIGHT (int)(WIN_HEIGHT / SCALE) 

// Shaders
#define VERT_SHADER "../shader/shader.vert"
#define FRAG_SHADER "../shader/shader.frag"

#endif
