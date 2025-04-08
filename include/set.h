/**
 * @file set.h
 * @author Juan Ibáñez
 * @brief It defines the way sets of ids work
 * @version 0
 * @date 2025-02-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief Maximum capacity/ammount of ids one set can have
 *
 */
#define SET_MX_CAP 100

/**
 * @brief Stores an array with ids and the number of ids it has
 *
 */
typedef struct _Set Set;

/**
 * @brief Creates a new set of ids initialazing its members
 * @author Juan Ibáñez
 *
 * @return Pointer to the new initialized set
 */
Set *set_create();

/**
 * @brief Destroys a set freeing all allocated memory
 * @author Juan Ibáñez
 *
 * @param set Pointer to the set being destroyed
 * @return OK if it was destroyed correctly, ERROR if the set was non-existing
 */
Status set_destroy(Set *set);

/**
 * @brief Adds a new id to the last position of a set
 * @author Juan Ibáñez
 *
 * @param set Pointer to the target set
 * @param id Id being added to the set
 * @return OK if the id was added correctly, ERROR if the parameters are wrong
 * or the set is full
 */
Status set_add(Set *set, Id id);

/**
 * @brief Removes an id from a set
 * @author Juan Ibáñez
 *
 * @param set Pointer to the set
 * @param id Id that will be removed from the set
 * @return ERROR if the set or id dont exist, OK otherwise when finished
 */
Status set_remove(Set *set, Id id);

/** 
 * @brief Gets the number of ids in a set 
 * @author Juan Ibáñez
 * 
 * @param set Pointer to the set
 * @return Number of ids in the set, -1 if the set does not exist
 */
int set_get_num_ids(Set *set);

/**
 * @brief Gets the id in the given position
 * @author Juan Ibáñez
 *
 * @param set Pointer to the set 
 * @param pos Position of the id we want to get
 * @return Id of the id in the given position, NO_ID if the set does not exist or
 */
Id set_get_id_at_pos(Set *set, int pos);

/**
 * @brief Checks if an id is in a set or not
 * @author Juan Ibáñez
 *
 * @param set Pointer to the set
 * @param id Id that we want to find
 * @return TRUE if the id is inside the set, FALSE if not
 */
Bool set_find(Set *set, Id id);

/**
 * @brief Checks if a set is full or not
 * @author Tiago Oselka
 *
 * @param set Pointer to the set
 * @return TRUE if the set is full, FALSE if not
 */
Bool set_is_full(Set *set);

/**
 * @brief Prints all information about a set
 * @author Juan Ibáñez
 *
 * @param set Pointer to the set
 * @return ERROR if the set does not exist, OK otherwise
 */
Status set_print(Set *set);

#endif