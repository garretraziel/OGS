#ifndef __OGS_DRAW_H__
#define __OGS_DRAW_H__

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include "ogs_defines.h"

int ogs_draw_element(OGS_PSCREEN screen,  int type, void *element, int active, OGS_RES offset);

int ogs_redraw(OGS_PSCREEN screen);

int ogs_redraw_element(OGS_PSCREEN screen, OGS_LIST_PITEM item, int active);

#endif
