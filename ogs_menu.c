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
  int mode = OGS_WINDOWED;
  OGS_RES resolution;
  resolution.width = 1024;
  resolution.height = 768;
  int colors = 16;
  
  OGS_SCREEN screen = ogs_init(mode, resolution, colors);

  fgetc(stdin);
  return 0;
}
