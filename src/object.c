/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Juan Ibáñez
 * @version 0
 * @date 16-04-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Stores information for a single object: its class and specific id
 * @author Juan Ibáñez
 *
 */
struct _Object {
  Id class;     /*!< Id of the class of the object*/
  Id id;        /*!< Unique id for the specific object*/
  Role role;    /*!< Role to which the object is friendly (only for traps)*/
  int use_value; /*!< Value for its specific action (damage of a wapon, defence of an armor...) */
};

/**
 * **************** OBJECT MANAGEMENT **************************
 */

/*Creates a new object by allocating memmory for it and initialazing its
 * members*/
Object *object_create(Id id) {
  Object *obj = NULL;

  if (id == NO_ID) return NULL;
  if (!(obj = (Object *)malloc(sizeof(Object)))) return NULL;

  obj->id = id;
  obj->role = UNDEFINED;
  obj->class = NO_ID;

  return obj;
}

/*Destroys an object by freeing its allocated memmory*/
Status object_destroy(Object *obj) {
  if (!obj) return ERROR;

  free(obj);
  obj = NULL;
  return OK;
}

/*It gets the id from an object*/
Id object_get_id(Object *obj) {
  if (!obj) return NO_ID;

  return obj->id;
}

/*Sets the id of an object to an especific id*/
Status object_set_id(Object *obj, Id id) {
  if ((!obj) || (id == NO_ID)) return ERROR;

  obj->id = id;
  return OK;
}

/*Gets the id of the class of an object*/
Id object_get_class_id(Object *obj) {
  if (!obj) return NO_ID;

  return obj->class;
}

/*Sets the id of the class of an object*/
Status object_set_class_id(Object *obj, Id class) {
  if (!obj) return ERROR;

  obj->class = class;

  return OK;
}

Role object_get_role(Object *obj) {
  if (!obj) return NO_ROLE;

  return obj->role;
}

Status object_set_role(Object *obj, Role role) {
  if (!obj || role == NO_ROLE) return ERROR;

  obj->role = role;
  return OK;
}

int object_get_use_value(Object *obj) {
  if (!obj) return -1;

  return obj->use_value;
}

Status object_set_use_value(Object *obj, int value) {
  if (!obj) return ERROR;

  obj->use_value = value;

  return OK;
}

/*Prints all information about an object*/
Status object_print(Object *obj) {
  if (!obj) return ERROR;

  fprintf(stdout, "--> Object id: %d\n", (int)obj->id);
  fprintf(stdout, "--> Object class id: %d\n", (int)obj->class);
  fprintf(stdout, "--> Object role: %d\n", (int)obj->role);

  return OK;
}
