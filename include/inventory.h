/**
 * @brief It defines the inventory module interface
 *
 * @file inventory.h
 * @author Lucas Blanco Rodriguez y Alina Datsko Yaskerska
 * @version 0
 * @date 20-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H
 
#include "set.h"
#include "types.h"

/**
 * @brief It stores the Id and name of a space and its adjacent spaces' ids
 *
 */
typedef struct _Inventory Inventory;

/**
 * @brief Creates a new inventory initialazing its members
 * @author Lucas Blanco Rodriguez 
 *
 * @return Pointer to the new initialized inventory
 */
Inventory *inventory_create();

/**
 * @brief Destroys an inventory freeing all allocated memory
 * @author Alina Datsko Yaskerska
 *
 * @param inventory Pointer to the inventory being destroyed
 * @return OK if it was destroyed correctly, ERROR if the inventory was non-existing
 */
Status inventory_destroy(Inventory *inventory);

/**
 * @brief Adds a new object to an inventory
 * @author Lucas Blanco Rodriguez
 *
 * @param inventory Pointer to the inventory
 * @param obj Id of the object being added to the inventory
 * @return OK if the object was added correctly, ERROR if the parameters are wrong
 * or the inventory is full
 */
Status inventory_add_object(Inventory *inventory, Id obj);

/**
 * @brief Removes an object from an inventory
 * @author Alina Datsko Yaskerska
 *
 * @param inventory Pointer to the inventory
 * @param obj Id of the object being removed from the inventory
 * @return OK if the object was removed correctly, ERROR if the parameters are wrong
 * or the object was not in the inventory
 */
Status inventory_remove_object(Inventory *inventory, Id obj);

/**
 * @brief Gets the array of ids of the objects of an inventory
 * @author Lucas Blanco Rodriguez
 *
 * @param inventory Pointer to the inventory
 * @return Pointer to the set of objects. Null in case of error
 */
Set *inventory_get_objects(Inventory *inventory);

/**
 * @brief Gets the maximum ammount of objects an inventory can have
 * @author Juan Ibáñez
 * 
 * @param inventory Pointer to the inventory
 * @return Maximum ammount of objects the inventory can have. -1 if ERROR
 */
int inventory_get_max_objects(Inventory *inventory);

/**
 * @brief Sets the maximum ammount of objects an inventory can have
 * @author Juan Ibáñez
 * 
 * @param inventory Pointer to the inventory
 * @return OK if everything went well, ERROR if there was any mistake
 */
Status inventory_set_max_objects(Inventory *inventory, int max);

/**
 * @brief Gets the number of objects in an inventory
 * @author Alina Datsko Yaskerska
 *
 * @param inventory Pointer to the inventory
 * @return Number of objects in the inventory, -1 if the inventory is non-existing 
 * or there was an error
 */
int inventory_get_num_objects(Inventory *inventory);

/**
 * @brief Checks if an object is in an inventory or not
 * @author Lucas Blanco Rodriguez
 *
 * @param inventory Pointer to the inventory
 * @param obj Id of the object being checked
 * @return TRUE if the object is in the inventory, FALSE if it is not or there was an error
 */
Bool inventory_find_object(Inventory *inventory, Id obj);

/**
 * @brief Gets the object at a certain position in an inventory
 * @author Alina Datsko Yaskerska
 *
 * @param inventory Pointer to the inventory
 * @param pos Position of the object in the inventory
 * @return Id of the object at the position, NO_ID if the inventory is non-existing
 * or there was an error
 */
Id inventory_get_object_at_pos(Inventory *inventory, int pos);

/**
 * @brief Checks if an inventory is full or not
 * @author Alina Datsko Yaskerska
 * 
 * @param inventory Pointer to the inventory
 * @return TRUE if the inventory is full, FALSE if it is not or there was an error
 */
Bool inventory_is_full(Inventory *inventory);

/**
 * @brief Prints all information about an inventory
 * @author Lucas Blanco Rodriguez
 * 
 * @param inventory Pointer to the inventory
 * @return OK if everything went well, ERROR if there was a mistake
 */
Status inventory_print(Inventory *inventory);

#endif

