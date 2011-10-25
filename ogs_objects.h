#ifndef __OGS_OGJECTS_H__
#define __OGS_OGJECTS_H__

#include <stdlib.h>
#include "ogs_defines.h"

int ogs_add_object(void *pobject, int type, OGS_SCREEN screen);

int ogs_delete_object(void *pobject, int type);

#endif
