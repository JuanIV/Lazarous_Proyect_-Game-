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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief converts a direction into a string
 *
 */
char *dir_to_str[N_DIR][N_DIRT] = {
  {"", "Unknown"}, {"n", "North"}, {"s", "South"}, {"e", "East"}, 
  {"w", "West"}, {"u", "Up"}, {"d", "Down"}};

/**
 * @brief Struct that stores the information of a Link: Id, name, id of the
 * origin space, id of the destination space, the direction and if its opened
 * @author Tiago Oselka
 *
 */
struct _Link {
  Id id;                    /*!< Id number of the link, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the link */
  Id orig;                  /*!< Id number of the space of origin*/
  Id destination;           /*!< Id number of the destination space*/
  Direction direction; /*!< The direction of the link (N, S, E, W, UNK_DIR)*/
  Bool open;     /*!< A boolean that represents if the link is open or not*/
  Bool locked;   /*!< Represents if the link needs a key to be opened*/
  Bool connected; /*!< Represents if the two spaces are the same room */
  Role op_role;  /*!< Role of the only people who can open this link */
  Role use_role; /*!< Role of the only people who can use this link */
};

/** *************** Link data management ***************
 */

/*It creates a new link, allocating memory and initializing its members*/
Link *link_create(Id id) {
  Link *newlink = NULL;

  if(id == NO_ID) return NULL;

  newlink = (Link *)calloc(1, sizeof(Link));
  if (!newlink) return NULL;

  newlink->id = id;

  newlink->name[0] = '\0';
  newlink->orig = NO_ID;
  newlink->destination = NO_ID;
  newlink->direction = UNK_DIR;
  newlink->open = FALSE;
  newlink->locked = FALSE;
  newlink->connected = FALSE;
  newlink->op_role = UNDEFINED;
  newlink->use_role = UNDEFINED;

  return newlink;
}

/*It destroys a link, freeing the allocated memory*/
Status link_destroy(Link *link) {
  if (!link) return ERROR;

  free(link);

  return OK;
}

/*It gets the id of a link*/
Id link_get_id(Link *link) {
  if (!link) return NO_ID;

  return link->id;
}

/** ***************  Name management  ***************
 */

/*It gets the name of a link*/
char *link_get_name(Link *link) {
  if (!link) return NULL;

  return link->name;
}

/*It sets the name of a link*/
Status link_set_name(Link *link, char *name) {
  if (!name) return ERROR;

  sprintf(link->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/** ***************  Origin management  ***************
 */

/*It gets the id of the space located at the origin of the link*/
Id link_get_orig(Link *link) {
  if (!link) return NO_ID;

  return link->orig;
}

/*It sets the id of the space located at the origin of the link*/
Status link_set_orig(Link *link, Id origin) {
  if (!link) return ERROR;

  link->orig = origin;

  return OK;
}

/** ***************  Destination management  ***************
 */

/*It gets the id of the space located at the destination of the link*/
Id link_get_dest(Link *link) {
  if (!link) return NO_ID;

  return link->destination;
}

/*It sets the id of the space located at the destination of the link*/
Status link_set_dest(Link *link, Id destination) {
  if (!link) return ERROR;

  link->destination = destination;

  return OK;
}

/** ***************  Direction management  ***************
 */

/*It gets the direction followed when traversing the link orig -> dest*/
Direction link_get_direction(Link *link) {
  if (!link) return UNK_DIR;

  return link->direction;
}

/*It sets the direction followed when traversing the link orig -> dest*/
Status link_set_direction(Link *link, Direction direction) {
  if (!link || direction == UNK_DIR) return ERROR;

  link->direction = direction;

  return OK;
}

/** ***************  Open management  ***************
 */

/*It gets the state of the link, TRUE if it's opened or FALSE if its closed*/
Status link_get_open(Link *link, Bool *bool) {
  if(!bool) return ERROR;
  if(!link) {
    *bool = FALSE;
    return ERROR;
  }

  *bool = link->open;

  return OK;
}

/*It sets the state of the link, TRUE if it's opened or FALSE if its closed*/
Status link_set_open(Link *link, Bool bool) {
  if (!link) return ERROR;

  link->open = bool;

  return OK;
}

/** ***************  Locked management  ***************
 */

/*It gets the lock of the link, TRUE if it's locked or FALSE if its openable*/
Status link_get_locked(Link *link, Bool *bool) {
  if (!link || !bool) return ERROR;

  *bool = link->locked;

  return OK;
}

/*It sets the lock of the link, TRUE if it's locked or FALSE if its openable*/
Status link_set_locked(Link *link, Bool bool) {
  if (!link) return ERROR;

  link->locked = bool;

  return OK;
}

/** ***************  Connected management  ***************
 */

 /*Gets if the two spaces are connected*/
Status link_get_connected(Link *link, Bool *bool) {
  if(!link || !bool) return ERROR;

  *bool = link->connected;

  return OK;
}

/*Sets if the two spaces are connected*/
Status link_set_connected(Link *link, Bool bool) {
  if(!link) return ERROR;

  link->connected = bool;

  return OK;
}

/** ***************  Open Role management  ***************
 */

/*Gets the role that can open or close the link*/
Role link_get_open_role(Link *link) {
  if (!link) return NO_ROLE;

  return link->op_role;
}

/*Sets the role that can open the link*/
Status link_set_open_role(Link *link, Role role) {
  if (!link || role == NO_ROLE) return ERROR;

  link->op_role = role;
  return OK;
}

/** ***************  Use Role management  ***************
 */

/*Gets the role that can use the link*/
Role link_get_use_role(Link *link) {
  if (!link) return NO_ROLE;

  return link->use_role;
}

/*Sets the only role that can use the link*/
Status link_set_use_role(Link *link, Role role) {
  if (!link || role == NO_ROLE) return ERROR;

  link->use_role = role;
  return OK;
}

/** ***************  Debugging functions  ***************
 */

/*It prints the link information*/
Status link_print(Link *link) {
  extern char *role_to_str[N_ROLES];
  /* Error control */
  if (!link) return ERROR;
  /* 1. Print the Id and name of the link */
  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);

  /* 2. Prints the parameters of the link: origin, destination and direction*/
  fprintf(stdout, "--> Origin: %ld\n", link->orig);
  fprintf(stdout, "--> Destination: %ld\n", link->destination);
  fprintf(stdout, "--> Direction: %s\n", dir_to_str[link->direction - UNK_DIR][DIRL]);

  /* 3. Prints the state of the link: TRUE if it's opened and FALSE if it's
   * closed*/
  if (link->open == TRUE) fprintf(stdout, "--> Open: TRUE\n");
  else fprintf(stdout, "--> Open: FALSE\n");

  /* 4. Prints if the link neesds something to be opened */
  if (link->locked == TRUE) fprintf(stdout, "--> Locked: TRUE\n");
  else fprintf(stdout, "--> Locked: FALSE\n");

  /* 5. Prints the role of those who can open or use the link */
  fprintf(stdout, "--> %s and allies can open the link\n", role_to_str[link->op_role - NO_ROLE]);
  fprintf(stdout, "--> %s and allies can use the link\n", role_to_str[link->use_role - NO_ROLE]);

  return OK;
}