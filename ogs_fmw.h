#ifndef __OGS_FMW_H__
#define __OGS_FMW_H__

#include <stdio.h>
#include <stdlib.h>

#include "ogs_defines.h"
#include "ogs_draw.h"
#include "ogs_list.h"
#include "ogs_objects.h"

OGS_PSCREEN ogs_init(int mode, OGS_RES resolution, int colors);

OGS_PWINDOW_S ogs_create_window(int x1, int y1, int x2, int y2, int pos_type);

int ogs_add_window(OGS_PWINDOW_S window, OGS_PSCREEN screen);

#endif
