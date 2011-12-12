#include "ogs_input.h"
#include <SDL/SDL.h>

int ogs_i_goto_left(OGS_PSCREEN window);
int ogs_i_goto_right(OGS_PSCREEN window);
int ogs_i_goto_down(OGS_PSCREEN window);
int ogs_i_goto_up(OGS_PSCREEN window);
int ogs_i_do_action(OGS_PSCREEN window);

int ogs_i_handle_input(OGS_PSCREEN window)
{
    SDL_Event event;

    int lastevent = OGS_NOEVENT;

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            return OGS_QUIT;
        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                lastevent = OGS_KEYRIGHT;
                ogs_i_goto_right(window);
                break;
            case SDLK_LEFT:
                lastevent = OGS_KEYLEFT;
                ogs_i_goto_left(window);
                break;
            case SDLK_RETURN:
                lastevent = OGS_ENTER;
                ogs_i_do_action(window);
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }
    
    return lastevent;
}

int ogs_i_goto_left(OGS_PSCREEN window)
{
    return 0;
}

int ogs_i_goto_right(OGS_PSCREEN window)
{
    return 0;
}

int ogs_i_goto_down(OGS_PSCREEN window)
{
    return 0;
}

int ogs_i_goto_up(OGS_PSCREEN window)
{
    return 0;
}

int ogs_i_do_action(OGS_PSCREEN window)
{
    return 0;
}
