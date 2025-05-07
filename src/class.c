/**
 * @brief It implements the object class module
 *
 * @file class.c
 * @author Alina Datsko
 * @version 0
 * @date 05-05-2025
 * @copyright GNU Public License
 */

#include "class.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Stores all information about a class of objects that share same values
 * @author Juan Ibáñez
 *
 */
struct _Class {
  Id id;                      /*!< Id number of the class, it must be unique */
  Tag tag;                    /*!< Represents the type of object that it is */
  char name[WORD_SIZE + 1];   /*!< Name of the space */
  char desc[OBJ_DESC_MX + 1]; /*!< Description of the class */
  char close_up[POV_HGHT][POV_WDTH + 1]; /*!< Close up aspect of the object*/ 
  Bool movable;  /*!< True if the objects of thie class are movable or False if not */
  Id depedency;  /*!< Id of the object class that is needed to use this one */
  Id open;       /*!< Id of the link that this class' objects can open */
  int luck;      /*!< Luck that it gives or takes to the player */
};

/**
 * ****************** CLASS MANAGEMENT *****************************
 */


/*It creates and initializes a new class*/
Class *class_create(Id id) {
  Class *class = NULL;

  if (id == NO_ID) return NULL;
  if (!(class = (Class *)malloc(sizeof(Class)))) return NULL;

  class->id = id;
  class->tag = NO_TAG;
  class->name[0] = '\0';
  class->desc[0] = '\0';
  class->movable = FALSE;
  class->depedency = NO_ID;
  class->open = NO_ID;
  class->luck = 0;

  return class;
}

/*It destroys a class freeing allocated memory*/
Status class_destroy(Class *class) {
  if (!class) return ERROR;

  free(class);
  class = NULL;
  return OK;
}

/*It gets the id of a class*/
Id class_get_id(Class *class) {
  if (!class) return NO_ID;

  return class->id;
}

/* Sets the id of a class*/
Status class_set_id(Class *class, Id id) {
  if (!class || id == NO_ID) return ERROR;

  class->id = id;
  return OK;
}

/*Gets the tag of a class*/
Tag class_get_tag(Class *class) {
  if (!class) return NO_TAG;

  return class->tag;
}

/*Sets the tag of a class*/
Status class_set_tag(Class *class, Tag tag) {
  if (!class || tag == NO_TAG) return ERROR;

  class->tag = tag;
  return OK;
}

/*Gets the name of a class*/
char *class_get_name(Class *class) {
  if (!class) return NULL;

  return class->name;
}

/*Sets the name of a class*/
Status class_set_name(Class *class, char *name) {
  if (!class || !name) return ERROR;

  if (sprintf(class->name, "%.*s", WORD_SIZE, name) < 0) return ERROR;
  return OK;
}

/*Gets the description of a class*/
char *class_get_desc(Class *class) {
  if (!class) return NULL;

  return class->desc;
}

/*Sets the description of a class*/
Status class_set_desc(Class *class, char *desc) {
  if (!class || !desc) return ERROR;

  if (sprintf(class->desc, "%.*s", OBJ_DESC_MX, desc) < 0) return ERROR;
  return OK;
}

/*Gets the close up aspect of a class*/
char *class_get_closeup_at_pos(Class *class, int pos) {
  if (!class) return NULL;

  if (pos < 0 || pos >= POV_HGHT) return NULL;

  return class->close_up[pos];
}

/*Gets the full close up of a class*/
Status class_get_closeup(Class *class, char closeup[POV_HGHT][POV_WDTH + 1]){
  int i;

  if(!class || !closeup) return ERROR;

  for(i=0;i<POV_HGHT;i++){
    sprintf(closeup[i], "%.*s", POV_WDTH, class->close_up[i]);
  }

  return OK;
}

/*Sets the close up aspect of a class*/
Status class_set_closeup_at_pos(Class *class, int pos, char *closeup) {
  int i;

  if(!class) return ERROR;

  if(pos<0 || pos>=POV_HGHT) return ERROR;

  if(!closeup) class->close_up[pos][0] = '\0';

  sprintf(class->close_up[pos], "%-*.*s", POV_WDTH,POV_WDTH, closeup);

  /*We prevent from saving a line break in the gdesc*/
  for (i = 0; i < POV_WDTH; i++) {
    if ((class->close_up[pos][i] == '\n') || (class->close_up[pos][i] == '\r'))
      class->close_up[pos][i] = ' ';
  }

  return OK;
}

/*Gets the movable property of a class*/
Status class_get_movable(Class *class, Bool *bool) {
  if (!bool || !class) return ERROR;

  *bool = class->movable;

  return OK;
}

/*Sets the movable property of a class*/
Status class_set_movable(Class *class, Bool movable) {
  if (!class) return ERROR;

  class->movable = movable;
  return OK;
}

/*Gets the dependency of a class*/
Status class_get_dependency(Class *class, Id *dependency) {
  if (!class || !dependency) return ERROR;

  *dependency = class->depedency;

  return OK;
}

/*Sets the dependency of a class*/
Status class_set_dependency(Class *class, Id dependency) {
  if (!class) return ERROR;

  class->depedency = dependency;
  return OK;
}

/*Gets the open property of a class*/
Status class_get_open(Class *class, Id *open) {
  if (!class || !open) return ERROR;

  *open = class->open;

  return OK;
}

/*Sets the link this class can open*/
Status class_set_open(Class *class, Id open) {
  if (!class) return ERROR;

  class->open = open;
  return OK;
}

/*Gets the luck property of a class*/
int class_get_luck(Class *class) {
  if (!class) return -1;

  return class->luck;
}

/*Sets the luck bonus of a class*/
Status class_set_luck(Class *class, int luck) {
  if (!class) return ERROR;

  class->luck = luck;
  return OK;
}

/*Prints all information about a class*/
Status class_print(Class *class) {
  if (!class) return ERROR;

  fprintf(stdout, "--> Class id: %d\n", (int)class->id);
  fprintf(stdout, "--> Class tag: %d\n", (int)class->tag);
  fprintf(stdout, "--> Class name: %s\n", class->name);
  fprintf(stdout, "--> Class description: %s\n", class->desc);
  fprintf(stdout, "--> Class movable: %d\n", (int)class->movable);
  fprintf(stdout, "--> Class dependency: %d\n", (int)class->depedency);
  fprintf(stdout, "--> Class open: %d\n", (int)class->open);
  fprintf(stdout, "--> Class luck: %d\n", class->luck);

  return OK;
}