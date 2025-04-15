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
  Tag tag;                  /*!< Represents the type of object that it is */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  char desc[OBJ_DESC_MX + 1]; /*!< Description of the object */
  int use_value;            /*!< Value for its specific action (damage of a wapon, defence of an armor...) */
  Bool movable;             /*!< True if the object is movable or False if not */
  Id depedency;             /*!< Id of the object that is needed to use this one */
  Id open;                  /*!< Id of the link that this object can open */
  int luck;                /*!< Luck that it gives or takes to the player */
};

/*Creates a new object by allocating memmory for it and initialazing its members*/
Object *object_create(Id id) {
  Object *obj = NULL;

  if(id == NO_ID) return NULL;
  if (!(obj = (Object *)malloc(sizeof(Object)))) return NULL;

  obj->id = id;
  obj->tag = NORMAL;
  obj->name[0] = '\0';
  obj->desc[0] = '\0';
  obj->use_value = 0;
  obj->movable = FALSE;
  obj->depedency = NO_ID;
  obj->open = NO_ID;
  obj->luck = 0;

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

/*Gets the tag of an object*/
Tag object_get_tag(Object *obj){
  if(!obj) return NO_ID;

  return obj->tag;
}

/*Sets the tag of an object*/
Status object_set_tag(Object *obj, Tag tag){
  if(!obj) return ERROR;

  obj->tag = tag;
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

/*Gets the use_value of an object*/
int object_get_use_value(Object *obj) {
  if (!obj) return 0;

  return obj->use_value;
}

/*Sets the use_value of an object*/
Status object_set_use_value(Object *obj, int use_value) {
  if (!obj) return ERROR;

  obj->use_value = use_value;

  return OK;
}

/*Gets the movable property of an object*/
Bool object_get_movable(Object *obj) {
  if (!obj) return FALSE;

  return obj->movable;
}

/*Sets the movable property of an object*/
Status object_set_movable(Object *obj, Bool movable) {
  if (!obj) return ERROR;

  obj->movable = movable;

  return OK;
}

/*Gets the dependency of an object*/
Id object_get_dependency(Object *obj) {
  if (!obj) return NO_ID;

  return obj->depedency;
}

/*Sets the dependency of an object*/
Status object_set_dependency(Object *obj, Id depedency) {
  if (!obj) return ERROR;

  obj->depedency = depedency;

  return OK;
}

/*Gets the open property of an object*/
Id object_get_open(Object *obj) {
  if (!obj) return NO_ID;

  return obj->open;
}

/*Sets the open property of an object*/
Status object_set_open(Object *obj, Id open) {
  if (!obj) return ERROR;

  obj->open = open;

  return OK;
}

/*Gets the luck property of an object*/
int object_get_luck(Object *obj) {
  if (!obj) return FALSE;

  return obj->luck;
}

/*Sets the luck property of an object*/
Status object_set_luck(Object *obj, int luck) {
  if (!obj) return ERROR;

  obj->luck = luck;

  return OK;
}

/*Prints all information about an object*/
Status object_print(Object *obj) {
  if (!obj) return ERROR;

  fprintf(stdout, "--> Object id: %d\n", (int)obj->id);
  fprintf(stdout, "--> Object tag: %d\n", (int)obj->tag);
  fprintf(stdout, "--> Object name: %s\n", obj->name);
  fprintf(stdout, "--> Object description: %s\n", obj->desc);
  fprintf(stdout, "--> Object use value: %d\n", obj->use_value);
  fprintf(stdout, "--> Object movable: %d\n", (int)obj->movable);
  fprintf(stdout, "--> Object dependency: %d\n", (int)obj->depedency);
  fprintf(stdout, "--> Object open: %d\n", (int)obj->open);
  fprintf(stdout, "--> Object luck: %d\n", obj->luck);
  fprintf(stdout, "\n");

  return OK;
}
