/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author Lucas Blanco Rodriguez y Alina Datsko Yaskerska
 * @version 0
 * @date 20-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct that stores the information of an Inventory: a set of objects and the max number of objects to be stored 
 * @author Lucas Blanco Rodriguez y Alina Datsko Yaskerska
 * 
 */
struct _Inventory {
  Set *objects;     /*!< Set of objects contained in the inventory*/
  int max_objects;  /*!< Maximum ammount of objects the inventory can have*/
};

/*Creates a new inventory initialazing its members*/
Inventory *inventory_create() {
  Inventory *newInventory = NULL;

  newInventory = (Inventory *)malloc(sizeof(Inventory));
  if (!newInventory) return NULL;

  if (!(newInventory->objects = set_create())) return NULL;
  newInventory->max_objects = 0;

  return newInventory;
}

/*Destroys an inventory freeing all allocated memory*/
Status inventory_destroy(Inventory *inventory) {
  if (!inventory) return ERROR;

  if (inventory->objects) {
    if (set_destroy(inventory->objects) == ERROR) return ERROR;
  }

  free(inventory);
  inventory = NULL;
  return OK;
}

/*Adds a new object to an inventory*/
Status inventory_add_object(Inventory *inventory, Id obj) {
  if (!inventory || obj == NO_ID) return ERROR;

  if (inventory_is_full(inventory) == TRUE) return ERROR;

  if (set_add(inventory->objects, obj) == ERROR) return ERROR;

  return OK;
}

/*Removes an object from an inventory*/
Status inventory_remove_object(Inventory *inventory, Id obj) {
  if (!inventory || obj == NO_ID) return ERROR;

  if (inventory_find_object(inventory, obj) == FALSE) return ERROR;

  if (set_remove(inventory->objects, obj) == ERROR) return ERROR;

  return OK;
}

/*Gets the array of ids of the objects of an inventory*/
Set *inventory_get_objects(Inventory *inventory) {
  if (!inventory) return NULL;

  return inventory->objects;
}

/*Gets the maximum ammount of objects an inventory can have*/
int inventory_get_max_objects(Inventory *inventory){
  if(!inventory) return -1;

  return inventory->max_objects;
}

/*Sets the maximum ammount of objects an inventory can have*/
Status inventory_set_max_objects(Inventory *inventory, int max){
  if(!inventory) return ERROR;

  inventory->max_objects = max;
  return OK;
}

/*Gets the number of objects in an inventory*/
int inventory_get_num_objects(Inventory *inventory) {
  if (!inventory) return -1;

  return set_get_num_ids(inventory->objects);
}

/*Checks if an object is in an inventory or not*/
Bool inventory_find_object(Inventory *inventory, Id obj) {
  if (!inventory || obj == NO_ID) return FALSE;

  return set_find(inventory->objects, obj);
}

/*Gets the object at a certain position in an inventory*/
Id inventory_get_object_at_pos(Inventory *inventory, int pos) {
  if (!inventory) return NO_ID;

  if(pos < 0 || pos >= inventory->max_objects) return NO_ID;

  return set_get_id_at_pos(inventory->objects, pos);
}

/*Checks if an inventory is full or not*/
Bool inventory_is_full(Inventory *inventory) {
  if (!inventory) return TRUE;

  if(set_is_full(inventory->objects) == TRUE) return TRUE;

  if(set_get_num_ids(inventory->objects) >= inventory->max_objects)
    return TRUE;
  else return FALSE;
}

/*Prints all information about an inventory*/
Status inventory_print(Inventory *inventory) {
  if (!inventory) return ERROR;

  fprintf(stdout, "--> Inventory objects:\n");
  if (set_print(inventory->objects) == ERROR) return ERROR;

  return OK;
}
