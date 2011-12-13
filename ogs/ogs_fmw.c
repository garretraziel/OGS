#include "ogs_fmw.h"
#include <SDL/SDL_image.h>

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

OGS_PSCREEN ogs_init(int mode, int width, int height, int colors)
{
    OGS_PSCREEN oscreen = malloc(sizeof(struct OGS_SCREEN));
    OGS_RES resolution = {.width = width, .height = height};
    
    if (oscreen == NULL) {
        return NULL;
    }
    
    if (ogs_i_init_sdl(mode, resolution, colors) != OGS_OK) {
        // not good arguments
        oscreen -> screen = NULL;
        return oscreen;
    }

    int imgload = IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    if ((imgload & (IMG_INIT_JPG|IMG_INIT_PNG)) != (IMG_INIT_JPG|IMG_INIT_PNG)) {
        fprintf(stderr,"error: nemuzu nacist podporu obrazku\n");
        return NULL;
    }

    atexit(IMG_Quit);
    
    int type = mode == OGS_FULLSCREEN? SDL_FULLSCREEN : SDL_HWSURFACE;
    
    oscreen -> screen = SDL_SetVideoMode(resolution.width, resolution.height, colors, type | SDL_DOUBLEBUF);
    
    oscreen -> list = malloc(sizeof(struct OGS_LIST));
    
    oscreen -> resolution = resolution;
    
    if (oscreen == NULL) return NULL;
    ogs_list_init(oscreen -> list);
    
    return oscreen;
}

OGS_PWINDOW_S ogs_create_window(int x1, int y1, int x2, int y2, int pos_type, int fullscreen)
{
    OGS_PWINDOW_S window = malloc(sizeof(struct OGS_WINDOW_S));
    
    if (window == NULL) {
        fprintf(stderr,"Error: not enough memory.\n");
        return NULL;
    }
    
    window -> position.width = x1;
    window -> position.height = y1;
    window -> size.width = x2 - x1; //TODO: toto nejde lip?
    window -> size.height = y2 - y1;
    window -> pos_type = pos_type;
    window -> fullscreen = fullscreen;
    
    window -> items = malloc(sizeof(struct OGS_LIST));
    
    if (window -> items == NULL) {
        fprintf(stderr, "Error: not enough memory.\n");
        free(window);
        return NULL;
    }
    
    ogs_list_init(window -> items);
    
    return window;
}

int ogs_add_window(OGS_PWINDOW_S window, OGS_PSCREEN screen)
{
    if (ogs_list_add(screen -> list, OGS_WINDOW, (void *) window) != OGS_OK) {
        return OGS_NOMEM_ERROR;
    }
    
    //TODO: neni tady potreba resit jeste neco?
    
    return OGS_OK;
}

int ogs_delete_screen(OGS_PSCREEN screen)
{
    ogs_list_destroy(screen -> list);

    SDL_FreeSurface(screen -> screen);
    
    free(screen);
    
    //TODO:...
    
    return OGS_OK;
}

int ogs_add_button_to_window(OGS_PWINDOW_S window, int x1, int y1, int x2, int y2, char *caption, void (*callfunction)(void), int enabled)
{
    OGS_PBUTTON_S button = malloc(sizeof(struct OGS_BUTTON_S));
    
    if (button == NULL) return OGS_NOMEM_ERROR;
    button -> position.width = x1;
    button -> position.height = y1;
    
    button -> size.width = x2-x1;
    button -> size.height = y2-y1;
    button -> enabled = enabled;
    button -> caption = caption;
    button -> clicked = 0;

    button -> function_execute = callfunction;
    
    return ogs_list_add(window -> items, OGS_BUTTON, (void*) button);
}

int ogs_add_picture_to_window(OGS_PWINDOW_S window, int x1, int y1, int x2, int y2, char *filename)
{
    OGS_PPICTURE_S picture = malloc(sizeof(struct OGS_PICTURE_S));
    if (picture == NULL) return OGS_NOMEM_ERROR;

    picture -> image = IMG_Load(filename); //TODO: resit velikost, zmenseni a tak
    picture -> position.width = x1;
    picture -> position.height = y1;
    picture -> size.width = x2-x1;
    picture -> size.height = y2-y1;

    if (picture -> image == NULL) return OGS_FILE_ERROR;
    
    return ogs_list_add(window -> items, OGS_PICTURE, (void *) picture);
}

int ogs_handle_input(OGS_PSCREEN screen)
{
    return ogs_i_handle_input(screen);
}
