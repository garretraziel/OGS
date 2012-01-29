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

void pozdrav(OGS_PSCREEN, void *);
void pozdrav2(OGS_PSCREEN, void *);
void pozdrav3(OGS_PSCREEN, void *);
void pozdrav4(OGS_PSCREEN, void *);
void pridej_tlacitko(OGS_PSCREEN, void *);

int main(int argc, char *argv[])
{
    int mode = OGS_WINDOWED; // should be fullscreen
    int width = 1024;
    int height = 768;
    int colors = 16;
    
    OGS_PSCREEN screen = ogs_init(mode, width, height, colors);
    
    int arg = 5;
    int arg2 = 6;

    OGS_RES souradnice = {.width = 0, .height = 0};
    
    // code:
    
    OGS_PWINDOW_S window = ogs_create_window(100, 100, 900, 600, OGS_REL, OGS_WINDOWED);
    ogs_add_button_to_window(window, 50, 50, 200, 80, "Hello, world", pozdrav, &arg, 1);
    ogs_add_button_to_window(window, 50, 100, 200, 130, "Herp derp", pozdrav2, NULL, 1);
    ogs_add_button_to_window(window, 300, 50, 450, 80, "Hello, world2", pozdrav3, &arg2, 1);
    ogs_add_button_to_window(window, 300, 100, 450, 130, "Herp derp2", pozdrav4, NULL, 1);
    ogs_add_button_to_window(window, 550, 50, 700, 80, "Hello, world3", pozdrav3, &arg2, 1);
    ogs_add_button_to_window(window, 550, 100, 700, 130, "Herp derp3", pridej_tlacitko, &souradnice, 1);

    ogs_add_button_to_window(window, 70, 150, 220, 180, "Hello, world4", pozdrav, &arg, 1);
    ogs_add_button_to_window(window, 240, 150, 390, 180, "Herp derp5", pozdrav2, NULL, 1);
    ogs_add_button_to_window(window, 410, 150, 560, 180, "Hello, world25", pozdrav3, &arg2, 1);
    ogs_add_button_to_window(window, 580, 150, 730, 180, "Herp derp25", pozdrav4, NULL, 1);
    ogs_add_button_to_window(window, 50, 200, 200, 230, "Hello, world35", pozdrav3, &arg2, 1);
    ogs_add_button_to_window(window, 300, 200, 450, 230, "Herp derp35", pridej_tlacitko, &souradnice, 1);
    
    //ogs_add_picture_to_window(window, 50, 200, 550, 500, "sekera.png");
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

void pozdrav(OGS_PSCREEN screen, void *prvek)
{
    printf("Ahoj: %d...\n", *((int *) prvek));
}

void pozdrav2(OGS_PSCREEN screen, void *prvek)
{
    printf("Nazdar...\n");
}

void pozdrav3(OGS_PSCREEN screen, void *prvek)
{
    printf("Herp: %d\n", *((int *) prvek));
}

void pozdrav4(OGS_PSCREEN screen, void *prvek)
{
    printf("Derp\n");
}

void pridej_tlacitko(OGS_PSCREEN screen, void *prvek)
{
    int x = ((OGS_RES *) prvek) -> width;
    int y = ((OGS_RES *) prvek) -> height;
    ogs_add_button_to_window(screen -> list -> top -> item, x, y, x+150, y+30, "dalsi", pozdrav2, NULL, 1);
    ogs_redraw(screen);
    ((OGS_RES *) prvek) -> height += 50;
}
