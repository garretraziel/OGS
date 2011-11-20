#include "ogs_list.h"

int ogs_list_init(OGS_PLIST list)
{
    list -> top = list -> bot = list -> act = NULL;
    
    return 0;
}

int ogs_list_add(OGS_PLIST list, int type, void *item)
{
    OGS_LIST_PITEM temp = malloc(sizeof(struct OGS_LIST_ITEM));

    if (temp == NULL) return OGS_NOMEM_ERROR;

    temp -> type = type;
    temp -> item = item;
    temp -> next = NULL;

    if (list -> bot != NULL) list -> bot -> next = temp;

    if (list -> top == NULL) list -> top = list -> bot = temp;
    else list -> bot = temp;
}

int ogs_list_destroy(OGS_PLIST list)
{
    while (list -> top != NULL) {
	OGS_LIST_PITEM temp = list -> top;
	list -> top = list -> top -> next;
	
	if (ogs_delete_object(temp -> item, temp -> type) != 0) {
	    fprintf(stderr, "Error while deleting.\n");
	    // nothing more...
	}
	
	free(temp);
    }
    
    return 0;
}

