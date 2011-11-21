#include "ogs_objects.h"

int ogs_init_object(int type, void *pboject)
{
    // take care of specific initialization types
    return 0;
}

int ogs_delete_object(int type, void *pobject)
{
    // take care of deletion for each object
    //TODO: podle type spravne mazat...
    switch(type) {
    case OGS_WINDOW: {
	free((OGS_PWINDOW_S) pobject);
	break;
    }
    case OGS_BUTTON: {
	free((OGS_PBUTTON_S) pobject);
	break;
    }
    case OGS_INPUTF: {
	free((OGS_PINPUTF_S) pobject);
	break;
    }
    case OGS_INFO: {
	free((OGS_PINFO_S) pobject);
	break;
    }
    case OGS_TEXTARRAY: {
	free((OGS_PTEXTARRAY_S) pobject);
	break;
    }
    case OGS_PICTURE: {
	free((OGS_PPICTURE_S) pobject);
	break;
    }
    }
    return 0;
}

int ogs_execute_object(int type, void *pobject)
{
    // execute function for that object
    return 0;
}
