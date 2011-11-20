#include "ogs_fmw.h"

int ogs_i_init_sdl(int mode, OGS_RES resolution, int colors);

int ogs_i_resc_is_sane(int mode, OGS_RES resolution, int colors);

int ogs_i_init_sdl(int mode, OGS_RES resolution, int colors)
{
    if (!ogs_i_resc_is_sane(mode,resolution,colors)) {
	fprintf(stderr,"Unable to initialize, insane arguments.\n");
	return OGS_INIT_ERROR;
    }
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr,"Unable to initialize SDL: %s\n", SDL_GetError());
	return OGS_SDL_ERROR;
    }
    
    atexit(SDL_Quit);
    
    return OGS_OK;
}

int ogs_i_resc_is_sane(int mode, OGS_RES resolution, int colors)
{
    if (mode != OGS_FULLSCREEN && mode != OGS_WINDOWED)
	return -1;
    if (colors != 8 && colors != 16 && colors != 32)
	return -2;
    if (resolution.width < 320 || resolution.height < 240)
	return -3;
    return 1;
}

OGS_PSCREEN ogs_init(int mode, OGS_RES resolution, int colors)
{
    OGS_PSCREEN oscreen = malloc(sizeof(struct OGS_SCREEN));

    if (oscreen == NULL) {
	return NULL;
    }
    
    if (ogs_i_init_sdl(mode, resolution, colors) != OGS_OK) {
	// not good arguments
	oscreen -> screen = NULL;
	return oscreen;
    }
    
    int type = mode == OGS_FULLSCREEN? SDL_FULLSCREEN : SDL_HWSURFACE;
    
    oscreen -> screen = SDL_SetVideoMode(resolution.width, resolution.height, colors, type | SDL_DOUBLEBUF);
    
    oscreen -> list = malloc(sizeof(struct OGS_LIST));
    ogs_list_init(oscreen -> list);
    
    return oscreen;
}

OGS_PWINDOW_S ogs_create_window(int x1, int y1, int x2, int y2, int pos_type)
{
    return NULL;
}

int ogs_add_window(OGS_PWINDOW_S window, OGS_PSCREEN screen)
{
    if (ogs_list_add(screen -> list, OGS_WINDOW, (void *) window) != OGS_OK) {
	return OGS_NOMEM_ERROR;
    }

    //TODO: neni tady potreba resit jeste neco?
    
    return OGS_OK;
}
