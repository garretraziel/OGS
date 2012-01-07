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

void pozdrav(void *);
void pozdrav2(void *);
void pozdrav3(void *);
void pozdrav4(void *);

int main(int argc, char *argv[])
{
    int mode = OGS_WINDOWED; // should be fullscreen
    int width = 800;
    int height = 600;
    int colors = 16;
    
    OGS_PSCREEN screen = ogs_init(mode, width, height, colors);
    
    int arg = 5;
    int arg2 = 6;
    
    // code:
    
    OGS_PWINDOW_S window = ogs_create_window(0, 0, 700, 500, OGS_REL, OGS_WINDOWED);
    ogs_add_button_to_window(window, 50, 50, 200, 80, "Hello, world", pozdrav, &arg, 1);
    ogs_add_button_to_window(window, 50, 100, 200, 130, "Herp derp", pozdrav2, NULL, 1);
    ogs_add_button_to_window(window, 300, 50, 450, 80, "Hello, world2", pozdrav3, &arg2, 1);
    ogs_add_button_to_window(window, 300, 100, 450, 130, "Herp derp2", pozdrav4, NULL, 1);
    ogs_add_picture_to_window(window, 50, 200, 550, 500, "sekera.png");
    ogs_add_window(window, screen);
      
    int cont = OGS_NOEVENT;
    ogs_redraw(screen);
    
    while (cont != OGS_QUIT) {
        cont = ogs_handle_input(screen);
    /*     //poresit input a reakce na nej... */
    }
    
    
    //fgetc(stdin);
    
    ogs_delete_screen(screen);
    
    return 0;
}

void pozdrav(void *prvek)
{
    printf("Ahoj: %d...\n", *((int *) prvek));
}

void pozdrav2(void *prvek)
{
    printf("Nazdar...\n");
}

void pozdrav3(void *prvek)
{
    printf("Herp: %d\n", *((int *) prvek));
}

void pozdrav4(void *prvek)
{
    printf("Derp\n");
}
