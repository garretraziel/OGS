// main file with main function

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "ogs/ogs_fmw.h"

enum MODES {
    PRINTHELP, NORMAL
};

typedef struct {
    int mode;
    int fullscreen;
    int res_x;
    int res_y;
    //...
} ARGS;

void pozdrav(void);

int main(int argc, char *argv[])
{
    int mode = OGS_WINDOWED; // should be fullscreen
    int width = 800;
    int height = 600;
    int colors = 16;
    
    OGS_PSCREEN screen = ogs_init(mode, width, height, colors);
    
    
    
    // code:
    
    OGS_PWINDOW_S window = ogs_create_window(0, 0, 700, 500, OGS_REL, OGS_WINDOWED);
    ogs_add_button_to_window(window, 50, 50, 200, 80, "Hello, world", pozdrav, 1);
    ogs_add_picture_to_window(window, 100, 100, 100, 100, "sekera.png");
    ogs_add_window(window, screen);
      
    int cont = OGS_NOEVENT;
    while (cont != OGS_QUIT) {
        cont = ogs_handle_input(screen);
    /*     //poresit input a reakce na nej... */
        ogs_redraw(screen);
    }
    
    ogs_redraw(screen);
    
    //fgetc(stdin);
    
    ogs_delete_screen(screen);
    
    return 0;
}

void pozdrav(void)
{
    printf("Ahoj...\n");
}
