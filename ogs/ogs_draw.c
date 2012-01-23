#include "ogs_draw.h"

int ogs_i_draw_window(OGS_PWINDOW_S window, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_i_draw_inputf(OGS_PINPUTF_S inputf, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_i_draw_info(OGS_PINFO_S info, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_i_draw_textarray(OGS_PTEXTARRAY_S textarray, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_i_draw_picture(OGS_PPICTURE_S picture, OGS_PSCREEN screen, int active, OGS_RES offset);

int ogs_draw_element(OGS_PSCREEN screen, int type, void *element, int active, OGS_RES offset)
{
    switch(type) {
    case OGS_WINDOW: {
        // postarat se o vykresleni vsech vnitrnich prvku
        OGS_PWINDOW_S window = (OGS_PWINDOW_S) element;
        ogs_i_draw_window(window, screen, active, offset);
        
        OGS_LIST_PITEM item = window -> items -> top;
        while (item != NULL) {
            int active_w = 0;
            if (window -> items -> act == item) active_w = 1;
            OGS_RES newoffset = {.width = offset.width + window -> position.width, \
                                 .height = offset.height + window -> position.height};
            ogs_draw_element(screen, item -> type, item -> item, active_w, newoffset);
            item = item -> next;
        }
        
        break;
    }
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = (OGS_PBUTTON_S) element;
        ogs_i_draw_button(button, screen, active, offset);
        break;
    }
    case OGS_INPUTF: {
        OGS_PINPUTF_S inputfield = (OGS_PINPUTF_S) element;
        ogs_i_draw_inputf(inputfield, screen, active, offset);
        break;
    }
    case OGS_INFO: {
        OGS_PINFO_S info = (OGS_PINFO_S) element;
        ogs_i_draw_info(info, screen, active, offset);
        break;
    }
    case OGS_TEXTARRAY: {
        OGS_PTEXTARRAY_S textarray = (OGS_PTEXTARRAY_S) element;
        ogs_i_draw_textarray(textarray, screen, active, offset);
        break;
    }
    case OGS_PICTURE: {
        OGS_PPICTURE_S picture = (OGS_PPICTURE_S) element;
        ogs_i_draw_picture(picture, screen, active, offset);
        break;
    }
    default: {
        fprintf(stderr,"Error: unknown type for displaying, %d\n", type);
        break;
    }
    }
    
    return 0;
}

int ogs_i_draw_window(OGS_PWINDOW_S window, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    if (window -> fullscreen == OGS_FULLSCREEN) {
        boxColor(screen -> screen, 0, 0, screen -> resolution.width, screen -> resolution.height, \
                 WINDOW_C);
    } else {
        boxColor(screen -> screen, window -> position.width + offset.width, window -> position.height + offset.height, \
                 window -> position.width + window -> size.width + offset.width, window -> position.height + \
                 window -> size.height + offset.height, WINDOW_C);
        if (active) rectangleColor(screen -> screen, window -> position.width+2 + offset.width, window -> position.height \
                                   + 2 + offset.height, window -> position.width + window -> size.width - 2 + offset.width, \
                                   window -> position.height + offset.height + \
                                   window -> size.height - 2, WHITE);
    }
    
    return 0;
}

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    boxColor(screen -> screen, button->position.width-3+offset.width, button->position.height-3+offset.height, \
                    button -> position.width + button -> size.width + 3 + offset.width, \
                    button -> position.height + button -> size.height + 3 + offset.height, 0xaaaaaaff);
    if (button -> enabled) {
        boxColor(screen -> screen, button->position.width + offset.width, button->position.height + offset.height, \
                        button -> position.width + button -> size.width + offset.width, \
                        button -> position.height + button -> size.height + offset.height, WHITE);
        if (button -> clicked) boxColor(screen -> screen, button->position.width+2 + offset.width, button->position.height+2+offset.height, \
                                               button -> position.width + button -> size.width - 2 + offset.width, \
                                               button -> position.height + button -> size.height - 2 + offset.height, SILVER);
        //TODO: jen pokus, udělat jinak
    }
    stringColor(screen -> screen, button -> position.width + 10 + offset.width,        \
                button -> position.height + button -> size.height/2 + offset.height,    \
                button -> caption, 0x000000ff);
    if (active) rectangleColor(screen -> screen, button -> position.width + offset.width, button -> position.height + offset.height, \
                               button -> position.width + button -> size.width + offset.width, button -> position.height + \
                               button -> size.height + offset.height, LIGHTBLUE);
    return 0;
}

int ogs_i_draw_inputf(OGS_PINPUTF_S inputf, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    return 0;
}

int ogs_i_draw_info(OGS_PINFO_S info, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    return 0;
}

int ogs_i_draw_textarray(OGS_PTEXTARRAY_S textarray, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    return 0;
}

int ogs_i_draw_picture(OGS_PPICTURE_S picture, OGS_PSCREEN screen, int active, OGS_RES offset)
{
    SDL_Rect rcDest = {picture -> position.width + offset.width, picture -> position.height + offset.height, 0, 0}; //TODO: velikost!!
    //TODO: resit rozmery, vyrez vs. zmenseni a tak

    SDL_BlitSurface(picture -> image, NULL, screen -> screen, &rcDest);

    if (active) rectangleColor(screen -> screen, picture -> position.width+offset.width, picture -> position.height + offset.height, \
                               picture -> position.width + picture -> size.width - 1 + offset.width, picture -> position.height + \
                               picture -> size.height - 1 + offset.height, LIGHTBLUE);
    
    return 0;
}

int ogs_redraw(OGS_PSCREEN screen)
{
    OGS_LIST_PITEM item = screen -> list -> top;
    OGS_RES offset = {.width=0, .height=0}; // first offset is zero-zero, items are not inside any window
    
    while (item != NULL) {
        int act = 0;
        if (screen -> list -> act == item) act = 1;
        ogs_draw_element(screen, item -> type, item -> item, act, offset);
        item = item -> next;
    }
    
    SDL_UpdateRect(screen -> screen, 0, 0, 0, 0);
    
    return 0;
}

int ogs_redraw_element(OGS_PSCREEN screen, OGS_LIST_PITEM item, int active)
{
    ogs_draw_element(screen, item -> type, item -> item, active);
    int x1, x2, y1, y2;
    x1 = x2 = y1 = y2 = 0;
    switch (item -> type) {
    case OGS_WINDOW: {
        OGS_PWINDOW_S window = item -> item;
        x1 = window -> position.width;
        y1 = window -> position.height;
        x2 = window -> size.width;
        y2 = window -> size.height;
        break;
    }
    case OGS_BUTTON: {
        OGS_PBUTTON_S button = item -> item;
        x1 = button -> position.width - 3;
        y1 = button -> position.height - 3;
        x2 = button -> size.width + 3;
        y2 = button -> size.height + 3;
        break;
    }
    case OGS_INPUTF:
        break;
    case OGS_INFO:
        break;
    case OGS_TEXTARRAY:
        break;
    case OGS_PICTURE: {
        OGS_PPICTURE_S picture = item -> item;
        x1 = picture -> position.width;
        y1 = picture -> position.height;
        x2 = picture -> size.width;
        y2 = picture -> size.height;
        break;
    }
    default:
        break;
    }
    //SDL_Rect rect = {.x=0,.y=0,.w=800,.h=600};
    //SDL_FillRect(screen->screen,&rect, BLACK);
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    SDL_UpdateRect(screen -> screen, x1, y1, x2+1, y2+1);
    return 0;
}
