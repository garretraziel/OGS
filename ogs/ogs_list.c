#include "ogs_list.h"

void ogs_i_find_positions(OGS_PLIST list, OGS_LIST_PITEM *item);

int ogs_list_init(OGS_PLIST list)
{
    list -> top = list -> bot = list -> act = NULL;
    
    return 0;
}

int ogs_list_add(OGS_PLIST list, int type, void *item)
{
    OGS_LIST_PITEM temp = malloc(sizeof(struct OGS_LIST_ITEM));

    if (temp == NULL) return OGS_NOMEM_ERROR;

    ogs_init_object(type, item);

    temp -> type = type;
    temp -> item = item;
    temp -> next = NULL;

    temp -> up = temp -> down = temp -> right = temp -> left = NULL;
    temp -> left = list -> act;

    ogs_i_find_positions(list, &temp);

    /*if (list -> act == NULL)*/ list -> act = temp;

    if (list -> bot != NULL) list -> bot -> next = temp;

    if (list -> top == NULL) list -> top = list -> bot = temp;
    else list -> bot = temp;

    return OGS_OK;
}

int ogs_list_destroy(OGS_PLIST list)
{
    while (list -> top != NULL) {
	OGS_LIST_PITEM temp = list -> top;
	list -> top = list -> top -> next;

	if (temp -> type == OGS_WINDOW) {
	    ogs_list_destroy(((OGS_PWINDOW_S) temp -> item) -> items);
	    //TODO: nemam toho mazat vic?
	}
	
	if (ogs_delete_object(temp -> type, temp -> item) != 0) {
	    fprintf(stderr, "Error while deleting.\n");
	    // nothing more...
	}
	
	free(temp);
    }

    free(list);
    
    return 0;
}

void ogs_i_find_positions(OGS_PLIST list, OGS_LIST_PITEM *item)
{

}
