/**
 * @file set.c
 * @author Juan Ibáñez
 * @brief It implements the functionallity of the sets of ids
 * @version 0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Struct that stores the information of a Set: an array of the ids of the objects inside of it and the number of said ids
 * @author Juan Ibáñez
 * 
 */
struct _Set {
  Id ids[SET_MX_CAP];     /*!< Array of ids */
  int n_ids;              /*!< Number of ids in the array*/
};

/*Creates a new set of ids initialazing its members*/
Set *set_create() {
  Set *set = NULL;
  int i;

  if (!(set = (Set *)malloc(sizeof(Set)))) return NULL;

  set->n_ids = 0;
  for (i = 0; i < SET_MX_CAP; i++) {
    set->ids[i] = NO_ID;
  }

  return set;
}

/*Destroys a set freeing all allocated memory*/
Status set_destroy(Set *set) {
  if (!set) return ERROR;

  free(set);
  set = NULL;
  return OK;
}

/*Adds a new id to the last position of a set*/
Status set_add(Set *set, Id id) {
  if (!set || id == NO_ID) return ERROR;
  if(set_is_full(set) == TRUE) return ERROR;

  set->ids[set->n_ids] = id;
  set->n_ids++;

  return OK;
}

/*Removes an id from a set*/
Status set_remove(Set *set, Id id) {
  int i, j;

  if (!set || id == NO_ID) return ERROR;

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      /*We have to move each element one position to the left*/
      for(j=i; j<(set->n_ids - 1); j++){
        set->ids[j] = set->ids[j+1];
      }
      set->n_ids--;
      set->ids[set->n_ids] = NO_ID;

      return OK;
    }
  }

  return ERROR;
}

/*Gets the number of ids in a set */
int set_get_num_ids(Set *set) {
  if (!set) return -1;

  return set->n_ids;
}

/*Gets the id in the given position*/
Id set_get_id_at_pos(Set *set, int pos) {
  if (!set) return NO_ID;
  if (pos < 0 || pos > set->n_ids) return NO_ID;

  return set->ids[pos];
}

/*Checks if an id is in a set or not*/
Bool set_find(Set *set, Id id) {
  int i;

  if (!set || id == NO_ID) return FALSE;

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) return TRUE;
  }

  return FALSE;
}

/*Checks if a set is full or not*/
Bool set_is_full(Set *set) {
  if (!set) return TRUE;

  if (set->n_ids >= SET_MX_CAP) return TRUE;

  return FALSE;
}

/*Prints all information about a set*/
Status set_print(Set *set) {
  int i;
  if (!set) return ERROR;

  fprintf(stdout, "\n\n-------------\n\n");
  fprintf(stdout, "=> Set n_ids: %d\n", set->n_ids);

  for (i = 0; i < set->n_ids; i++) {
    fprintf(stdout, "=> Set id[%d]: %d\n", i, (int)set->ids[i]);
  }
  return OK;
}
