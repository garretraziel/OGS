#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "ogs_fmw.h"

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

int main(int argc, char *argv[])
{
  int mode = OGS_WINDOWED; // should be fullscreen
  OGS_RES resolution;
  resolution.width = 800;
  resolution.height = 600;
  int colors = 16;
  
  OGS_SCREEN screen = ogs_init(mode, resolution, colors);

  // code:
  /*
    OGS_PWINDOW_S window = ogs_create_window(x, y, x2, y2, OGS_REL);
    ogs_add_button_to_window(window, x, y, x2, y2, "Hello, world", pozdrav, 1);
    ogs_add_picture_to_window(window, x, y, x2, y2, "picture.png");
    ogs_add_window(window, screen);

    int cont = 1;
    while (cont) {
    ogs_handle_input(screen);
    poresit input a reakce na nej...
    cont = ogs_was_quited(screen);
    ogs_redraw(screen);
    }

    ogs_delete_screen(screen);
  */

  fgetc(stdin);
  
  return 0;
}
