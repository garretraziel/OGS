#include "ogs_list.h"

#define ogs_item_x(list_item) (((OGS_PGENERIC_ITEM_S) list_item -> item) -> position.width)
#define ogs_item_y(list_item) (((OGS_PGENERIC_ITEM_S) list_item -> item) -> position.height)

void ogs_i_recount_positions(OGS_PLIST list);

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

    temp -> up = temp -> down = temp -> left = temp -> right = NULL;

    if (list -> act == NULL) list -> act = temp;

    if (list -> bot != NULL) list -> bot -> next = temp;

    if (list -> top == NULL) list -> top = list -> bot = temp;
    else list -> bot = temp;

    ogs_i_recount_positions(list);

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

void ogs_i_recount_positions(OGS_PLIST list)
{
    if (list == NULL) return;
    OGS_LIST_PITEM temp = list -> top;
    while (temp != NULL) {
        /* v podstate: projede nejdriv direct dolu, stejna souradnice, pokud tam neco bude, da to do prvek->down (nejblizsi) */
        /* pote projede od x od leva doprava, pokud je y mensi jak objektu, spocita vzdalenost (pythagoras), pokud je */
        /* nejblizsi, nastavi jako down */
        /* pote se to stejne udela i pro levo, pravo a nahoru */

        OGS_LIST_PITEM temp2 = list -> top;
        int last_distance = 0;
        while (temp2 != NULL) {
            if (ogs_item_y(temp2) > ogs_item_y(temp))
                if (ogs_item_x(temp2) == ogs_item_x(temp))
                    if (last_distance > (ogs_item_x(temp2) - ogs_item_x(temp)) || last_distance == 0) {
                        temp -> down = temp2;
                        last_distance = ogs_item_x(temp2) - ogs_item_x(temp);
                    }
            temp2 = temp2 -> next;
        }
        temp = temp -> next;
    }
}

