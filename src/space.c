/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct that stores the information of a space: id, name, graphic description, a set of objects, the character in the space and whether it is discovered
 * @author Juan Ibáñez
 * 
 */
struct _Space {
  Id id;                                  /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1];               /*!< Name of the space */
  char gdesc[SP_GD_HGHT][SP_GD_WTH + 1];  /*!< Graphic description of the space */
  Set *objects;                           /*!< Set of the objects in the space */
  Id trap;                                /*!< Id of the trap currently set on the space */
  Set *characters;                        /*!< Set of the characters in the space */
  Bool discovered;                        /*!< Bool to know if the space has been discovered */
};

/** *************** Space data management ***************
 */

/*It creates a new space, allocating memory and initializing its members*/
Space *space_create(Id id) {
  Space *newSpace = NULL;
  int i;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  if (newSpace == NULL) return NULL;

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  for (i = 0; i < SP_GD_HGHT; i++) {
    newSpace->gdesc[i][0] = '\0';
  }

  newSpace->discovered = FALSE;

  if (!(newSpace->objects = set_create())) {
    space_destroy(newSpace);
    return NULL;
  }

  if(!(newSpace->characters = set_create())) {
    space_destroy(newSpace);
    return NULL;
  }

  return newSpace;
}

/*It destroys a space, freeing the allocated memory*/
Status space_destroy(Space *space) {
  if (!space) return ERROR;

  if (space->objects) set_destroy(space->objects);

  free(space);
  space = NULL;
  return OK;
}

/*It gets the id of a space*/
Id space_get_id(Space *space) {
  if (!space) return NO_ID;

  return space->id;
}

/**
 * ***************  Name management  ***************
 */

/*It sets the name of a space*/
Status space_set_name(Space *space, char *name) {
  if (!space || !name) return ERROR;

  sprintf(space->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/*It gets the name of a space*/
const char *space_get_name(Space *space) {
  if (!space) return NULL;

  return space->name;
}

/**
 * ***************  Graphic description management  ***************
 */

/*Sets the graphic description of a space*/
Status space_set_gdesc_at(Space *space, char *gdesc, int pos) {
  int i;

  if (!space) return ERROR;

  if (pos < 0 || pos >= SP_GD_HGHT) return ERROR;

  if (!gdesc) space->gdesc[pos][0] = '\0';

  sprintf(space->gdesc[pos], "%-*.*s", SP_GD_WTH, SP_GD_WTH, gdesc);

  /*We prevent from saving a line break in the gdesc*/
  for (i = 0; i < SP_GD_WTH; i++) {
    if ((space->gdesc[pos][i] == '\n') || (space->gdesc[pos][i] == '\r'))
      space->gdesc[pos][i] = ' ';
  }

  return OK;
}

/*Gets the graphic descrpition of a space*/
char *space_get_gdesc_at(Space *space, int line) {
  if (!space) return NULL;
  return space->gdesc[line];
}
/**
 * ***************  Discovered spaces management  ***************
 */

/*It sets the discovered status of a space*/
Status space_set_discovered(Space *space, Bool discovered) {
  if (!space) return ERROR;

  space->discovered = discovered;
  return OK;
}

/*It gets the discovered status of a space*/
Bool space_get_discovered(Space *space) {
  if (!space) return FALSE;

  return space->discovered;
}

/**
 * ***************  Set of objects management  ***************
 */

/*It adds an object to the space*/
Status space_add_object(Space *space, Id obj) {
  if (!space) return ERROR;

  return set_add(space->objects, obj);
} /*Error check inside set_add()*/

/*It removes an object from a space*/
Status space_remove_object(Space *space, Id obj) {
  if (!space) return ERROR;

  return set_remove(space->objects, obj);
} /*Error check inside set_remove()*/

/*It gets whether the space has an object or not*/
Bool space_find_object(Space *space, Id obj) {
  if (!space) return FALSE;

  return set_find(space->objects, obj);
} /*Error check inside set_find()*/

/*It gets the id of the object at a certain position inside the space*/
Id space_get_object_at_pos(Space *space, int pos) {
  if (!space) return NO_ID;

  return set_get_id_at_pos(space->objects, pos);
} /*Error check inside set_get_object_at_pos()*/

/*It gets whether the set in a space is full*/
Bool space_objects_is_full(Space *space) {
  if (!space) return TRUE;

  return set_is_full(space->objects);
}

/*It gets the number of objects contained in a space*/
int space_get_num_objects(Space *space){
  if(!space) return 0;

  return set_get_num_ids(space->objects);
}

/**
 * ***************  Trap management  ********************
 */

/*Gets the id of the trap currently set on a space*/
Id space_get_trap(Space *space){
  if(!space) return NO_ID;

  return space->trap;
}

/*Sets a trap in a space*/
Status space_set_trap(Space *space, Id trap){
  if(!space) return ERROR;

  space->trap = trap;
  return OK;
}

/**
 * ***************  Character management  ***************
 */ 

/*Adds a character to the set of characters of the space*/
Status space_add_character(Space *space, Id charr) {
  if(!space || charr == NO_ID) return ERROR;

  return set_add(space->characters, charr);
}

/*Removes a character from the set of characters of the space*/
Status space_remove_character(Space *space, Id charr) {
  if(!space || charr == NO_ID) return ERROR;
  
  return set_remove(space->characters, charr);
}

/*It gets whether the space has a certain character or not*/
Bool space_find_character(Space *space, Id charr) {
  if(!space || charr == NO_ID) return FALSE;

  return set_find(space->characters, charr);
}

/*It gets the id of the character at a certain position inside the space*/
Id space_get_character_at_pos(Space *space, int pos) {
  if(!space) return NO_ID;

  return set_get_id_at_pos(space->characters, pos);
}

/*Checks whether the set of characters is full*/
Bool space_characters_is_full(Space *space) {
  if(!space) return TRUE;

  return set_is_full(space->characters);
}

/*It gets the number of characters contained in a space*/
int space_get_num_characters(Space *space) {
  if(!space) return -1;

  return set_get_num_ids(space->characters);
}

/**
 * ***************  Debugging functions  ***************
 */

/*It prints the space information*/
Status space_print(Space *space) {
  int i;

  /* Error Control */
  if (!space) return ERROR;

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  

  /* 2. Print if the space has been discovered */
  if (space_get_discovered(space) == TRUE) {
    fprintf(stdout, "---> The space has been discovered.\n");
  } else {
    fprintf(stdout, "---> The space has not been discovered.\n");
  }

  /* 3. Print the list of objects in the space*/
  set_print(space->objects);

  /* 4. Print the list of characters in the space*/
  set_print(space->characters);

  /* 5. Print the graphic description*/
  fprintf(stdout, "---> Graphic description:\n");
  for (i = 0; i < SP_GD_HGHT; i++) {
    fprintf(stdout, "%s\n", space->gdesc[i]);
  }

  return OK;
}
