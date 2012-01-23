#include "ogs_input.h"
#include "ogs_draw.h"
#include <SDL/SDL.h>

#define ogs_i_goto(screen, where)                                       \
    do {                                                                \
        OGS_RES offset = {.width = 0, .height = 0};                     \
        if (screen -> list -> act == NULL) break;                       \
        OGS_LIST_PITEM actitem = screen -> list -> act;                 \
        OGS_LIST_PITEM old_actitem = NULL;                              \
        while (actitem != NULL && actitem -> type == OGS_WINDOW) {      \
            old_actitem = actitem;                                      \
            offset.width += ((OGS_PWINDOW_S) actitem -> item) -> position.width; \
            offset.height += ((OGS_PWINDOW_S) actitem -> item) -> position.height; \
            actitem = ((OGS_PWINDOW_S) actitem -> item) -> items -> act; \
        }                                                               \
        if (actitem == NULL) break;                                     \
        if (old_actitem != NULL) {                                      \
            if (actitem -> where != NULL) {                             \
                ogs_redraw_element(screen, actitem, 0, offset);         \
                ogs_redraw_element(screen, actitem -> where, 1, offset); \
                ((OGS_PWINDOW_S) old_actitem -> item) -> items -> act = actitem -> where; \
            }                                                           \
        } else {                                                        \
            if (actitem -> where != NULL) {                             \
                ogs_redraw_element(screen, actitem, 0, offset);         \
                ogs_redraw_element(screen, actitem -> where, 1, offset); \
                screen -> list -> act = actitem -> where;               \
            }                                                           \
        }                                                               \
    } while (0)

int ogs_i_do_action(OGS_PSCREEN screen);

int ogs_handle_input(OGS_PSCREEN window)
{   
    SDL_Event event;

    SDL_Delay(10);

    int lastevent = OGS_NOEVENT;

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
            case SDLK_DOWN:
                lastevent = OGS_KEYDOWN;
                ogs_i_goto(window, down);
                break;
            case SDLK_UP:
                lastevent = OGS_KEYUP;
                ogs_i_goto(window, up);
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
        case SDL_JOYBUTTONDOWN: {
            if (event.jbutton.button == 1) {
                lastevent = OGS_ENTER;
                ogs_i_do_action(window);
            }
            break;
        }
        case SDL_JOYHATMOTION: {
            if (event.jhat.value & SDL_HAT_UP) {
                lastevent = OGS_KEYUP;
                ogs_i_goto(window, up);
            }
            if (event.jhat.value & SDL_HAT_DOWN) {
                lastevent = OGS_KEYDOWN;
                ogs_i_goto(window, down);
            }
            if (event.jhat.value & SDL_HAT_LEFT) {
                lastevent = OGS_KEYLEFT;
                ogs_i_goto(window, left);
            }
            if (event.jhat.value & SDL_HAT_RIGHT) {
                lastevent = OGS_KEYRIGHT;
                ogs_i_goto(window, right);
            }
            break;
        }
        case SDL_JOYAXISMOTION: {
            if (event.jaxis.axis % 2 == 0) {
                if (event.jaxis.value < -30000) {
                    lastevent = OGS_KEYLEFT;
                    ogs_i_goto(window, left);
                } else if (event.jaxis.value > 30000) {
                    lastevent = OGS_KEYRIGHT;
                    ogs_i_goto(window, right);
                }
            } else {
                if (event.jaxis.value < -30000) {
                    lastevent = OGS_KEYUP;
                    ogs_i_goto(window, up);
                } else if (event.jaxis.value > 30000) {
                    lastevent = OGS_KEYDOWN;
                    ogs_i_goto(window, down);
                }
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
    OGS_RES offset = {.width = 0, .height = 0};
    while (item != NULL && item -> type == OGS_WINDOW) {
        offset.width = ((OGS_PWINDOW_S) item -> item) -> position.width;
        offset.height = ((OGS_PWINDOW_S) item -> item) -> position.height;
        item = ((OGS_PWINDOW_S) item -> item) -> items -> act;
    }
    if (item == NULL) return 0;
    switch(item -> type) {
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = (OGS_PBUTTON_S) item -> item;
        if (button -> enabled) {
            button -> clicked = 1;
            ogs_redraw_element(screen, item, 1, offset);
            (button -> function_execute)(screen, button -> arg);
            SDL_Delay(100);
            button -> clicked = 0;
            ogs_redraw_element(screen, item, 1, offset);
        }
        break;
    }
    default:
        break;
    }
    return 0;
}
