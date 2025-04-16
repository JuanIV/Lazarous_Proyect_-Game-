/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author Tiago Oselka
 * @version 0
 * @date 21-3-2025
 * @copyright GNU Public License
 */

#include "link.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief converts a direction into a string
 * 
 */
char *dir_to_str[N_DIR][N_DIRT] = {
  {"", "Unknown"}, {"n", "North"}, {"s", "South"},
  {"e", "East"},   {"w", "West"}};

/**
 * @brief Struct that stores the information of a Link: Id, name, id of the origin space, id of the destination space, the direction and if its opened
 * @author Tiago Oselka
 * 
 */
struct _Link {
  Id id;                      /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1];   /*!< Name of the link */
  Id orig;                    /*!< Id number of the space of origin*/
  Id destination;             /*!< Id number of the destination space*/
  Direction direction;        /*!< The direction of the link (N, S, E, W, UNK_DIR)*/
  Bool open;                  /*!< A boolean that represents if the link is open or not*/
};

/** *************** Link data management ***************
 */

/*It creates a new link, allocating memory and initializing its members*/
Link *link_create(Id id) {
  Link *newlink = NULL;

  newlink = (Link*) calloc(1, sizeof(Link));
  if(!newlink) return NULL;

  newlink->id = id;

  newlink->name[0] = '\0';
  newlink->orig = NO_ID;
  newlink->destination = NO_ID;
  newlink->direction = UNK_DIR;
  newlink->open = FALSE;

  return newlink;
}

/*It destroys a link, freeing the allocated memory*/
Status link_destroy(Link *link) {
  if(!link) return ERROR;

  free(link);

  return OK;
}

/*It gets the id of a link*/
Id link_get_id(Link *link) {
  if(!link) return NO_ID;

  return link->id;
}

/** ***************  Name management  ***************
 */

/*It gets the name of a link*/
char *link_get_name(Link *link) {
  if(!link) return NULL;

  return link->name;
}

/*It sets the name of a link*/
Status link_set_name(Link *link, char *name) {
  if(!name) return ERROR;

  sprintf(link->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/** ***************  Origin management  ***************
 */

/*It gets the id of the space located at the origin of the link*/
Id link_get_orig(Link *link) {
  if(!link) return NO_ID;

  return link->orig;
}

/*It sets the id of the space located at the origin of the link*/
Status link_set_orig(Link *link, Id origin) {
  if(!link) return ERROR;

  link->orig = origin;

  return OK;
}

/** ***************  Destination management  ***************
 */

/*It gets the id of the space located at the destination of the link*/
Id link_get_dest(Link *link) {
  if(!link) return NO_ID;

  return link->destination;
}

/*It sets the id of the space located at the destination of the link*/
Status link_set_dest(Link *link, Id destination) {
  if(!link) return ERROR;

  link->destination = destination;

  return OK;
}

/** ***************  Direction management  ***************
 */

/*It gets the direction followed when traversing the link orig -> dest*/
Direction link_get_direction(Link *link) {
  if(!link) return UNK_DIR;

  return link->direction;
}

/*It sets the direction followed when traversing the link orig -> dest*/
Status link_set_direction(Link *link, Direction direction) {
  if(!link || direction == UNK_DIR) return ERROR;

  link->direction = direction;

  return OK;
}

/** ***************  Open management  ***************
 */

/*It gets the state of the link, TRUE if it's opened or FALSE if its closed*/
Bool link_get_open(Link *link) {
  if(!link) return FALSE;

  return link->open;
}

/*It sets the state of the link, TRUE if it's opened or FALSE if its closed*/
Status link_set_open(Link * link, Bool bool) {
  if(!link) return ERROR;

  link->open = bool;

  return OK;
}

/** ***************  Debugging functions  ***************
 */

/*It prints the link information*/
Status link_print(Link *link) {

  /* Error control */
  if(!link) return ERROR;
  /* 1. Print the Id and name of the link */
  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);

  /* 2. Prints the parameters of the link: origin, destination and direction*/
  fprintf(stdout, "--> Origin: %ld\n", link->orig);
  fprintf(stdout, "--> Destination: %ld\n", link->destination);
  fprintf(stdout, "--> Direction: %s\n", dir_to_str[link->direction - UNK_DIR][DIRL]);

  /* 3. Prints the state of the link: TRUE if it's opened and FALSE if it's closed*/
  if(link->open == TRUE) fprintf(stdout, "--> Open: TRUE\n");
  else fprintf(stdout, "--> Open: FALSE\n");

  return OK;

}