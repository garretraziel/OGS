#include "ogs_input.h"
#include <SDL/SDL.h>

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
                if (window -> list -> act -> next == NULL) window -> list -> act = window -> list -> top;
                else window -> list -> act = window -> list -> act -> next;
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
