#include "ogs_list.h"

#define ogs_item_abstract_x(list_item, what) (((OGS_PGENERIC_ITEM_S) list_item -> item) -> what.width)
#define ogs_item_abstract_y(list_item, what) (((OGS_PGENERIC_ITEM_S) list_item -> item) -> what.height)

#define ogs_item_x(list_item) ogs_item_abstract_x(list_item, position)
#define ogs_item_y(list_item) ogs_item_abstract_y(list_item, position)

#define ogs_item_x_lower(list_item) (ogs_item_x(list_item) + ogs_item_abstract_x(list_item, size))
#define ogs_item_y_lower(list_item) (ogs_item_y(list_item) + ogs_item_abstract_y(list_item, size))

#define ogs_item_center_x(list_item) (ogs_item_x(list_item) + (ogs_item_abstract_x(list_item, size) / 2))
#define ogs_item_center_y(list_item) (ogs_item_y(list_item) + (ogs_item_abstract_y(list_item, size) / 2))

typedef enum {UL, UR, LL, LR} OGS_CORNERS; // for identifying corners (upper/lower)-(left/right)

#define ogs_closest_corner(list_item, original_item) (                  \
                                                      (ogs_item_center_x(original_item) < ogs_item_x(list_item)) ? \
                                                      ((ogs_item_center_y(original_item) < ogs_item_y(list_item)) ? UL : LL) \
                                                      : ((ogs_item_center_y(original_item) < ogs_item_y(list_item)) ? UR : LR))

void ogs_i_recount_positions(OGS_PLIST list);
float ogs_distance(OGS_LIST_PITEM list_item, OGS_LIST_PITEM original_item);

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
        float last_distance = -1;
        while (temp2 != NULL) {
            if (temp2 == temp) {
                temp2 = temp2 -> next;
                continue;
            }
            if (ogs_item_y(temp2) > ogs_item_y(temp)) {
                int distance = ogs_distance(temp2, temp);
                if (distance < last_distance || last_distance == -1) {
                    last_distance = distance;
                    temp -> down = temp2;
                }
            }
            temp2 = temp2 -> next;
        }

        temp2 = list -> top;
        last_distance = -1;
        while (temp2 != NULL) {
            if (temp2 == temp) {
                temp2 = temp2 -> next;
                continue;
            }
            if (ogs_item_y(temp2) < ogs_item_y(temp)) {
                int distance = ogs_distance(temp2, temp);
                if (distance < last_distance || last_distance == -1) {
                    last_distance = distance;
                    temp -> up = temp2;
                }
            }
            temp2 = temp2 -> next;
        }

        temp2 = list -> top;
        last_distance = -1;
        while (temp2 != NULL) {
            if (temp2 == temp) {
                temp2 = temp2 -> next;
                continue;
            }
            if (ogs_item_x(temp2) < ogs_item_x(temp)) {
                int distance = ogs_distance(temp2, temp);
                if (distance < last_distance || last_distance == -1) {
                    last_distance = distance;
                    temp -> left = temp2;
                }
            }
            temp2 = temp2 -> next;
        }

        temp2 = list -> top;
        last_distance = -1;
        while (temp2 != NULL) {
            if (temp2 == temp) {
                temp2 = temp2 -> next;
                continue;
            }
            if (ogs_item_x(temp2) > ogs_item_x(temp)) {
                int distance = ogs_distance(temp2, temp);
                if (distance < last_distance || last_distance == -1) {
                    last_distance = distance;
                    temp -> right = temp2;
                }
            }
            temp2 = temp2 -> next;
        }
        
        temp = temp -> next;
    }
}

float ogs_distance(OGS_LIST_PITEM list_item, OGS_LIST_PITEM original_item) { 
    int nejblizsi = ogs_closest_corner(list_item, original_item);
    int temp = 0;
    int temp2 = 0;
    switch(nejblizsi) {
    case UL:
        temp = ogs_item_x(list_item) - ogs_item_center_x(original_item);
        temp2 = ogs_item_y(list_item) - ogs_item_center_y(original_item);
        break;
    case UR:
        temp = ogs_item_x_lower(list_item) - ogs_item_center_x(original_item);
        temp2 = ogs_item_y(list_item) - ogs_item_center_y(original_item);
        break;
    case LL:
        temp = ogs_item_x(list_item) - ogs_item_center_x(original_item);
        temp2 = ogs_item_y_lower(list_item) - ogs_item_center_y(original_item);
        break;
    case LR:
        temp = ogs_item_x_lower(list_item) - ogs_item_center_x(original_item);
        temp2 = ogs_item_y_lower(list_item) - ogs_item_center_y(original_item);
        break;
    }
    temp *= temp; temp2 *= temp2;
    return sqrt(temp + temp2);
}
