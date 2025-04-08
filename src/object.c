/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Juan Ibáñez
 * @version 0
 * @date 07-02-2025
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct that stores the information of an object: Id, name and desc
 * @author Juan Ibáñez
 * 
 */
struct _Object {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  char desc[OBJ_DESC_MX + 1]; /*!< Description of the object*/
};

/*Creates a new object by allocating memmory for it and initialazing its members*/
Object *object_create(Id id) {
  Object *obj = NULL;

  if(id == NO_ID) return NULL;
  if (!(obj = (Object *)malloc(sizeof(Object)))) return NULL;

  obj->id = id;
  obj->name[0] = '\0';
  obj->desc[0] = '\0';

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

/*Gets the name of an object*/
char *object_get_name(Object *obj) {
  if (!obj) return NULL;

  return obj->name;
}

/*Sets a string as the name of an object*/
Status object_set_name(Object *obj, char *name) {
  if (!obj || !name) return ERROR;

  sprintf(obj->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/*Gets the description of an object*/
char *object_get_desc(Object *obj) {
  if(!obj) return NULL;

  return obj->desc;
}

/*Sets the description of an object*/
Status object_set_desc(Object *obj, char *desc) {
  if(!obj || !desc) return ERROR;

  sprintf(obj->desc, "%.*s", OBJ_DESC_MX, desc);

  return OK;
}

/*Prints all information about an object*/
Status object_print(Object *obj) {
  if (!obj) return ERROR;

  fprintf(stdout, "--> Object id: %d\n", (int)obj->id);
  fprintf(stdout, "--> Object name: %s\n", obj->name);

  return OK;
}
