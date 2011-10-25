#ifndef __OGS_FMW_H__
#define __OGS_FMW_H__

#include <stdio.h>
#include <stdlib.h>

#include "ogs_defines.h"
#include "ogs_draw.h"
#include "ogs_list.h"
#include "ogs_objects.h"

OGS_SCREEN ogs_init(int mode, OGS_RES resolution, int colors);
int ogs_create_window(OGS_SCREEN screen, OGS_RES position, OGS_RES size, int type);

#endif
