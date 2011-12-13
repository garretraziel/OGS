#include "ogs_input.h"
#include "ogs_draw.h"
#include <SDL/SDL.h>

#define ogs_i_goto(screen, where)                                       \
    do {                                                                \
        if (screen -> list -> act == NULL) break;                       \
        OGS_LIST_PITEM actitem = screen -> list -> act;                 \
        OGS_LIST_PITEM old_actitem = NULL;                              \
        while (actitem != NULL && actitem -> type == OGS_WINDOW) {      \
            old_actitem = actitem;                                      \
            actitem = ((OGS_PWINDOW_S) actitem -> item) -> items -> act; \
        }                                                               \
        if (actitem == NULL) break;                                     \
        if (old_actitem != NULL) {                                      \
            if (actitem -> where != NULL)                               \
                ((OGS_PWINDOW_S) old_actitem -> item) -> items -> act = actitem -> where; \
        } else {                                                        \
            if (actitem -> where != NULL) screen -> list -> act = actitem -> where; \
        }                                                               \
    } while (0)

int ogs_i_do_action(OGS_PSCREEN screen);

int ogs_handle_input(OGS_PSCREEN window)
{
    SDL_Event event;

    int lastevent = OGS_NOEVENT;

    SDL_Delay(10);

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            return OGS_QUIT;
        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                lastevent = OGS_KEYRIGHT;
                ogs_i_goto(window, right);
                break;
            case SDLK_LEFT:
                lastevent = OGS_KEYLEFT;
                ogs_i_goto(window, left);
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

int ogs_i_do_action(OGS_PSCREEN screen)
{
    if (screen -> list -> act == NULL) return 0;
    OGS_LIST_PITEM item = screen -> list -> act;
    while (item != NULL && item -> type == OGS_WINDOW)
        item = ((OGS_PWINDOW_S) item -> item) -> items -> act;
    if (item == NULL) return 0;
    switch(item -> type) {
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = (OGS_PBUTTON_S) item -> item;
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
