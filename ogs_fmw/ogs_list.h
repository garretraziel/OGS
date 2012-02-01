#ifndef __OGS_LIST_H__
#define __OGS_LIST_H__

#include <stdio.h>
#include <math.h>
#include "ogs_defines.h"
#include "ogs_objects.h"

int ogs_list_init(OGS_PLIST list);

int ogs_list_add(OGS_PLIST list, int type, void *item);

int ogs_list_destroy(OGS_PLIST list);

#endif
