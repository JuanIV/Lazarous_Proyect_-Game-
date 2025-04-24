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
 * @brief Stores all information about a class of objects that share same values
 * @author Juan Ibáñez
 *
 */
struct _Class {
  Id id;                      /*!< Id number of the space, it must be unique */
  Tag tag;                    /*!< Represents the type of object that it is */
  char name[WORD_SIZE + 1];   /*!< Name of the space */
  char desc[OBJ_DESC_MX + 1]; /*!< Description of the class */
  char close_up[POV_HGHT][POV_WDTH + 1]; /*!< Close up aspect of the object*/ 
  int use_value; /*!< Value for its specific action (damage of a wapon, defence of an armor...) */
  Bool movable;  /*!< True if the objects of thie class are movable or False if not */
  Id depedency;  /*!< Id of the object class that is needed to use this one */
  Id open;       /*!< Id of the link that this class' objects can open */
  int luck;      /*!< Luck that it gives or takes to the player */
};

/**
 * @brief Stores information for a single object: its class and specific id
 * @author Juan Ibáñez
 *
 */
struct _Object {
  Class *class; /*!< Class of the object*/
  Id id;        /*!< Unique id for the specific object*/
  Role role;    /*!< Role to which the object is friendly (only for traps)*/
};

/**
 * ****************** CLASS MANAGEMENT *****************************
 */

/*It creates and initializes a new class*/
Class *object_class_create(Id id) {
  Class *class = NULL;

  if (id == NO_ID) return NULL;
  if (!(class = (Class *)malloc(sizeof(Class)))) return NULL;

  class->id = id;
  class->tag = NO_TAG;
  class->name[0] = '\0';
  class->desc[0] = '\0';
  class->use_value = 0;
  class->movable = FALSE;
  class->depedency = NO_ID;
  class->open = NO_ID;
  class->luck = 0;

  return class;
}

/*It destroys a class freeing allocated memory*/
Status object_class_destroy(Class *class) {
  if (!class) return ERROR;

  free(class);
  class = NULL;
  return OK;
}

/*It gets the id of a class*/
Id object_class_get_id(Class *class) {
  if (!class) return NO_ID;

  return class->id;
}

/* Sets the id of a class*/
Status object_class_set_id(Class *class, Id id) {
  if (!class || id == NO_ID) return ERROR;

  class->id = id;
  return OK;
}

/*Gets the tag of a class*/
Tag object_class_get_tag(Class *class) {
  if (!class) return NO_TAG;

  return class->tag;
}

/*Sets the tag of a class*/
Status object_class_set_tag(Class *class, Tag tag) {
  if (!class || tag == NO_TAG) return ERROR;

  class->tag = tag;
  return OK;
}

/*Gets the name of a class*/
char *object_class_get_name(Class *class) {
  if (!class) return NULL;

  return class->name;
}

/*Sets the name of a class*/
Status object_class_set_name(Class *class, char *name) {
  if (!class || !name) return ERROR;

  if (sprintf(class->name, "%.*s", WORD_SIZE, name) < 0) return ERROR;
  return OK;
}

/*Gets the description of a class*/
char *object_class_get_desc(Class *class) {
  if (!class) return NULL;

  return class->desc;
}

/*Sets the description of a class*/
Status object_class_set_desc(Class *class, char *desc) {
  if (!class || !desc) return ERROR;

  if (sprintf(class->desc, "%.*s", OBJ_DESC_MX, desc) < 0) return ERROR;
  return OK;
}

/*Gets the close up aspect of a class*/
char *object_class_get_closeup_at_pos(Class *class, int pos) {
  if(!class) return NULL;

  if(pos<0 || pos>=POV_HGHT) return NULL;

  return class->close_up[pos];
}

/*Gets the full close up of a class*/
Status object_class_get_closeup(Class *class, char closeup[POV_HGHT][POV_WDTH + 1]){
  int i;

  if(!class || !closeup) return ERROR;

  for(i=0;i<POV_HGHT;i++){
    sprintf(closeup[i], "%.*s", POV_WDTH, class->close_up[i]);
  }

  return OK;
}

/*Sets the close up aspect of a class*/
Status object_class_set_closeup_at_pos(Class *class, int pos, char *closeup) {
  int i;

  if(!class) return ERROR;

  if(pos<0 || pos>=POV_HGHT) return ERROR;

  if(!closeup) class->close_up[pos][0] = '\0';

  sprintf(class->close_up[pos], "%*.*s", POV_WDTH,POV_WDTH, closeup);

  /*We prevent from saving a line break in the gdesc*/
  for (i = 0; i < POV_WDTH; i++) {
    if ((class->close_up[pos][i] == '\n') || (class->close_up[pos][i] == '\r'))
      class->close_up[pos][i] = ' ';
  }

  return OK;
}

/*Gets the use_value of a class*/
int object_class_get_use_value(Class *class) {
  if (!class) return 0;

  return class->use_value;
}

/*Sets the use value of a class*/
Status object_class_set_use_value(Class *class, int value) {
  if (!class) return ERROR;

  class->use_value = value;
  return OK;
}

/*Gets the movable property of a class*/
Status object_class_get_movable(Class *class, Bool *bool) {
  if (!bool || !class) return ERROR;

  *bool = class->movable;

  return OK;
}

/*Sets the movable property of a class*/
Status object_class_set_movable(Class *class, Bool movable) {
  if (!class) return ERROR;

  class->movable = movable;
  return OK;
}

/*Gets the dependency of a class*/
Status object_class_get_dependency(Class *class, Id *dependency) {
  if (!class || !dependency) return ERROR;

  *dependency = class->depedency;

  return OK;
}

/*Sets the dependency of a class*/
Status object_class_set_dependency(Class *class, Id dependency) {
  if (!class) return ERROR;

  class->depedency = dependency;
  return OK;
}

/*Gets the open property of a class*/
Status object_class_get_open(Class *class, Id *open) {
  if (!class || !open) return ERROR;

  *open = class->open;

  return OK;
}

/*Sets the link this class can open*/
Status object_class_set_open(Class *class, Id open) {
  if (!class) return ERROR;

  class->open = open;
  return OK;
}

/*Gets the luck property of a class*/
int object_class_get_luck(Class *class) {
  if (!class) return -1;

  return class->luck;
}

/*Sets the luck bonus of a class*/
Status object_class_set_luck(Class *class, int luck) {
  if (!class) return ERROR;

  class->luck = luck;
  return OK;
}

/*Prints all information about a class*/
Status object_class_print(Class *class) {
  if (!class) return ERROR;

  fprintf(stdout, "--> Class id: %d\n", (int)class->id);
  fprintf(stdout, "--> Class tag: %d\n", (int)class->tag);
  fprintf(stdout, "--> Class name: %s\n", class->name);
  fprintf(stdout, "--> Class description: %s\n", class->desc);
  fprintf(stdout, "--> Class use value: %d\n", class->use_value);
  fprintf(stdout, "--> Class movable: %d\n", (int)class->movable);
  fprintf(stdout, "--> Class dependency: %d\n", (int)class->depedency);
  fprintf(stdout, "--> Class open: %d\n", (int)class->open);
  fprintf(stdout, "--> Class luck: %d\n", class->luck);

  return OK;
}

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
  obj->class = NULL;

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

Class *object_get_class(Object *obj) {
  if (!obj) return NULL;

  return obj->class;
}

Status object_set_class(Object *obj, Class *class) {
  if (!obj || !class) return ERROR;

  obj->class = class;
  return OK;
}

/*Gets the id of the class of an object*/
Id object_get_class_id(Object *obj) {
  if (!obj) return NO_ID;

  return object_class_get_id(obj->class);
}

/*Gets the tag of an object*/
Tag object_get_tag(Object *obj) {
  if (!obj) return NO_TAG;

  return object_class_get_tag(obj->class);
}

/*Gets the name of an object*/
char *object_get_name(Object *obj) {
  if (!obj) return NULL;

  return object_class_get_name(obj->class);
}

/*Gets the description of an object*/
char *object_get_desc(Object *obj) {
  if (!obj) return NULL;

  return object_class_get_desc(obj->class);
}

/*Gets the close up aspect of a class*/
char *object_get_closeup_at_pos(Object *obj, int pos) {
  if(!obj) return NULL;

  return object_class_get_closeup_at_pos(obj->class, pos);
}

/*Gets the full close up of an object*/
Status object_get_closeup(Object *obj, char closeup[POV_HGHT][POV_WDTH +1]) {
  if(!obj) return ERROR;

  return object_class_get_closeup(obj->class, closeup);
}

/*Gets the use_value of an object*/
int object_get_use_value(Object *obj) {
  if (!obj) return 0;

  return object_class_get_use_value(obj->class);
}

/*Gets the movable property of an object*/
Status object_get_movable(Object *obj, Bool *bool) {
  if (!obj || !bool) return ERROR;

  return object_class_get_movable(obj->class, bool);
}

/*Gets the dependency of an object*/
Status object_get_dependency(Object *obj, Id *dependency) {
  if (!obj || !dependency) return ERROR;

  return object_class_get_dependency(obj->class, dependency);
}

/*Gets the open property of an object*/
Status object_get_open(Object *obj, Id *open) {
  if (!obj || !open) return ERROR;

  return object_class_get_open(obj->class, open);
}

/*Gets the luck property of an object*/
int object_get_luck(Object *obj) {
  if (!obj) return -1;

  return object_class_get_luck(obj->class);
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

/*Prints all information about an object*/
Status object_print(Object *obj) {
  if (!obj) return ERROR;

  fprintf(stdout, "--> Object id: %d\n", (int)obj->id);
  if (obj->class) {
    fprintf(stdout, "--> Object class id: %d\nClass info:\n",
            (int)obj->class->id);
    fprintf(stdout, "--> Object class tag: %d\n", (int)obj->class->tag);
    fprintf(stdout, "--> Object class name: %s\n", obj->class->name);
    fprintf(stdout, "--> Object class description: %s\n", obj->class->desc);
    fprintf(stdout, "--> Object class use value: %d\n", obj->class->use_value);
    fprintf(stdout, "--> Object class movable: %d\n", (int)obj->class->movable);
    fprintf(stdout, "--> Object class dependency: %d\n",
            (int)obj->class->depedency);
    fprintf(stdout, "--> Object class open: %d\n", (int)obj->class->open);
    fprintf(stdout, "--> Object class luck: %d\n", obj->class->luck);
  } else
    fprintf(stdout, "No class available\n");

  return OK;
}
