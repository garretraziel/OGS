#include "ogs_objects.h"

int ogs_init_object(void *pboject, int type)
{
    // take care of specific initialization types
    return 0;
}

int ogs_delete_object(void *pobject, int type)
{
    // take care of deletion for each object
    return 0;
}

int ogs_execute_object(void *pobject, int type)
{
    // execute function for that object
    return 0;
}
