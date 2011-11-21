#include "ogs_draw.h"

int ogs_i_draw_window(OGS_PWINDOW_S window, OGS_PSCREEN screen);

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen);

int ogs_i_draw_inputf(OGS_PINPUTF_S inputf, OGS_PSCREEN screen);

int ogs_i_draw_info(OGS_PINFO_S info, OGS_PSCREEN screen);

int ogs_i_draw_textarray(OGS_PTEXTARRAY_S textarray, OGS_PSCREEN screen);

int ogs_i_draw_picture(OGS_PPICTURE_S picture, OGS_PSCREEN screen);

int ogs_draw_element(void *element, int type, OGS_PSCREEN screen)
{
    switch(type) {
    case OGS_WINDOW: {
    	// postarat se o vykresleni vsech vnitrnich prvku
    	OGS_PWINDOW_S window = (OGS_PWINDOW_S) element;
    	ogs_i_draw_window(window, screen);
    	break;
    }
    case OGS_BUTTON: {
    	OGS_PBUTTON_S button = (OGS_PBUTTON_S) element;
    	ogs_i_draw_button(button, screen);
    	break;
    }
    case OGS_INPUTF: {
    	OGS_PINPUTF_S inputfield = (OGS_PINPUTF_S) element;
    	ogs_i_draw_inputf(inputfield, screen);
    	break;
    }
    case OGS_INFO: {
    	OGS_PINFO_S info = (OGS_PINFO_S) element;
    	ogs_i_draw_info(info, screen);
    	break;
    }
    case OGS_TEXTARRAY: {
    	OGS_PTEXTARRAY_S textarray = (OGS_PTEXTARRAY_S) element;
    	ogs_i_draw_textarray(textarray, screen);
    	break;
    }
    case OGS_PICTURE: {
    	OGS_PPICTURE_S picture = (OGS_PPICTURE_S) element;
    	ogs_i_draw_picture(picture, screen);
    	break;
    }
    default: {
    	fprintf(stderr,"Error: unknown type for displaying, %d\n", type);
    	break;
    }
    }
    
    return 0;
}

int ogs_i_draw_window(OGS_PWINDOW_S window, OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen)
{
    if (button -> enabled) {
	boxColor(screen -> screen, button->position.width, button->position.height, \
		       button -> position.width + button -> size.width,\
		       button -> position.height + button -> size.height, WHITE);
    } else {
    }
    SDL_UpdateRect(screen ->  screen, 0, 0, 0, 0);
    return 0;
}

int ogs_i_draw_inputf(OGS_PINPUTF_S inputf, OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_draw_info(OGS_PINFO_S info, OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_draw_textarray(OGS_PTEXTARRAY_S textarray, OGS_PSCREEN screen)
{
    return 0;
}

int ogs_i_draw_picture(OGS_PPICTURE_S picture, OGS_PSCREEN screen)
{
    return 0;
}
