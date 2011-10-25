#include "ogs_list.h"

int ogs_list_init()
{
  return 0;
}

int ogs_list_destroy(OGS_LIST_PITEM item)
{
  while (item != NULL) {
    OGS_LIST_PITEM temp = item;
    item = item -> next;

    if (ogs_delete_object(temp -> item, temp -> type) != 0) {
      fprintf(stderr, "Error while deleting.\n");
      // nothing more...
    }
    
    free(temp);
  }

  return 0;
}
