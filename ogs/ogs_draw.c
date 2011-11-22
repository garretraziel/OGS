#include "ogs_draw.h"

int ogs_i_draw_window(OGS_PWINDOW_S window, OGS_PSCREEN screen);

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen);

int ogs_i_draw_inputf(OGS_PINPUTF_S inputf, OGS_PSCREEN screen);

int ogs_i_draw_info(OGS_PINFO_S info, OGS_PSCREEN screen);

int ogs_i_draw_textarray(OGS_PTEXTARRAY_S textarray, OGS_PSCREEN screen);

int ogs_i_draw_picture(OGS_PPICTURE_S picture, OGS_PSCREEN screen);

int ogs_draw_element(OGS_PSCREEN screen, int type, void *element)
{
    switch(type) {
    case OGS_WINDOW: {
    	// postarat se o vykresleni vsech vnitrnich prvku
    	OGS_PWINDOW_S window = (OGS_PWINDOW_S) element;
    	ogs_i_draw_window(window, screen);

	OGS_LIST_PITEM item = window -> items -> top;
	while (item != NULL) {
	    ogs_draw_element(screen, item -> type, item -> item);
	    item = item -> next;
	}
	
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
    if (window -> fullscreen) {
	boxColor(screen -> screen, 0, 0, screen -> resolution.width, screen -> resolution.height,\
		 DARKBLUE);
    } else {
	boxColor(screen -> screen, window -> position.width, window -> position.height,	\
		 window -> position.width + window -> size.width, window -> position.height + \
		 window -> size.height, DARKBLUE);
	rectangleColor(screen -> screen, window -> position.width+2, window -> position.height +2,	\
		 window -> position.width + window -> size.width - 2, window -> position.height + \
		 window -> size.height - 2, WHITE);
    }
    
    return 0;
}

int ogs_i_draw_button(OGS_PBUTTON_S button, OGS_PSCREEN screen)
{
    roundedBoxColor(screen -> screen, button->position.width-3, button->position.height-3, \
		    button -> position.width + button -> size.width + 3, \
		    button -> position.height + button -> size.height + 3, 2, 0xffffffCC); //TODO: asi ne pomoci alfakanalu
    if (button -> enabled) {
	roundedBoxColor(screen -> screen, button->position.width, button->position.height, \
		 button -> position.width + button -> size.width,	\
			button -> position.height + button -> size.height, 2, WHITE);
	//TODO: jen pokus, udělat jinak
    }
    stringColor(screen -> screen, button -> position.width + 10,	\
		button -> position.height + button -> size.height/2,	\
		button -> caption, 0x000000ff);
    //SDL_UpdateRect(screen ->  screen, 0, 0, 0, 0);
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

int ogs_redraw(OGS_PSCREEN screen)
{
    OGS_LIST_PITEM item = screen -> list -> top;

    while (item != NULL) {
	ogs_draw_element(screen, item -> type, item -> item);
	item = item -> next;
    }
    
    SDL_UpdateRect(screen -> screen, 0, 0, 0, 0);
    
    return 0;
}