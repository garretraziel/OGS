#ifndef __OGS_OGJECTS_H__
#define __OGS_OGJECTS_H__

#include <stdlib.h>
#include "ogs_defines.h"

int ogs_init_object(int type, void *pboject);

int ogs_delete_object(int type, void *pobject); // take care of deletion of object itself

int ogs_execute_object(int type, void *pobject); // take care of execution of several objects

#endif
