#include "ogs_input.h"
#include <SDL/SDL.h>

int ogs_i_goto_left(OGS_PSCREEN screen);
int ogs_i_goto_right(OGS_PSCREEN screen);
int ogs_i_goto_down(OGS_PSCREEN screen);
int ogs_i_goto_up(OGS_PSCREEN screen);
int ogs_i_do_action(OGS_PSCREEN screen);
int ogs_i_do_window_action(OGS_PWINDOW_S window, OGS_PSCREEN screen);

int ogs_handle_input(OGS_PSCREEN window)
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
            case SDLK_ESCAPE:
                return OGS_QUIT;
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

int ogs_i_goto_left(OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_goto_right(OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_goto_down(OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_goto_up(OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_do_action(OGS_PSCREEN screen)
{
    if (screen -> list -> act == NULL) return 0;
    switch(screen -> list -> act -> type) {
    case OGS_WINDOW: {
        OGS_PWINDOW_S window = (OGS_PWINDOW_S) screen -> list -> act -> item;
        ogs_i_do_window_action(window, screen);
        break;
    }
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = (OGS_PBUTTON_S) screen -> list -> act -> item;
        if (button -> enabled) {
            button -> clicked = 1;
            ogs_redraw(screen);
            (button -> function_execute)();
            button -> clicked = 0;
            ogs_redraw(screen);
        }
        break;
    }
    default:
        break;
    }
    return 0;
}

int ogs_i_do_window_action(OGS_PWINDOW_S window, OGS_PSCREEN screen)
{
    if (window -> items -> act == NULL) return 0;
    switch(window -> items -> act -> type) {
    case OGS_WINDOW: {
        OGS_PWINDOW_S window_new = (OGS_PWINDOW_S) window -> items -> act -> item;
        ogs_i_do_window_action(window_new, screen);
        break;
    }
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = (OGS_PBUTTON_S) window -> items -> act -> item;
        if (button -> enabled) {
            button -> clicked = 1;
            ogs_redraw(screen);
            (button -> function_execute)();
            SDL_Delay(100);
            button -> clicked = 0;
            ogs_redraw(screen);
        }
        break;
    }
    default:
        break;
    }
    return 0;
}
