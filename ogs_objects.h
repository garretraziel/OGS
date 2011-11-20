#ifndef __OGS_OGJECTS_H__
#define __OGS_OGJECTS_H__

#include <stdlib.h>
#include "ogs_defines.h"

int ogs_init_object(void *pboject, int type);

int ogs_delete_object(void *pobject, int type); // take care of deletion of object itself

#endif
