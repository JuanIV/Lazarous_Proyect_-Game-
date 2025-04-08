/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Tiago Oselka
 * @version 0 (1)
 * @date 25-02-2025
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct that stores the information of a character: Id, name, gdesc, message and health
 * @author Tiago Oselka
 * 
 */
struct _Character {
  Id id; /*!< Id number of the character, it must be unique */
  char name[WORD_SIZE + 1];    /*!< Name of the character */
  char gdesc[CHR_GD_SZ + 1];   /*!< Graphic description of the character*/
  char message[MESG_SIZE + 1]; /*!< Message of the character*/
  int health;                  /*!< Health of the character*/
  Bool friendly; /*!< The friendlyness of a character. True if friendly, False otherwise*/
};

/*It creates a new character by allocating its memory and initializing its members*/
Character *character_create(Id id) {
  Character *character = NULL;

  if (!(character = (Character *)malloc(sizeof(Character)))) return NULL;

  character->id = id;
  character->name[0] = '\0';
  character->gdesc[0] = '\0';
  character->message[0] = '\0';
  character->health = 0;
  character->friendly = TRUE;

  return character;
}

/*It destroys a character by freeing its allocated memory*/
Status character_destroy(Character *charr) {
  if (!charr) return ERROR;

  free(charr);
  charr = NULL;

  return OK;
}

/*It gets the id of a character*/
Id character_get_id(Character *charr) {
  if (!charr) return NO_ID;

  return charr->id;
}

/*It sets the id of a character*/
Status character_set_id(Character *charr, Id id) {
  if (!charr) return ERROR;

  charr->id = id;

  return OK;
}

/*It gets the name of a character*/
char *character_get_name(Character *charr) {
  if (!charr) return NULL;

  return charr->name;
}

/*It sets the name of a character*/
Status character_set_name(Character *charr, char *name) {
  if (!charr || !name) return ERROR;

  sprintf(charr->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/*It gets the graphic description of a character*/
char *character_get_gdesc(Character *charr) {
  if (!charr) return NULL;

  return charr->gdesc;
}

/*It sets the graphic description of a character*/
Status character_set_gdesc(Character *charr, char *gdesc) {
  if (!charr || !gdesc) return ERROR;

  sprintf(charr->gdesc, "%.*s", CHR_GD_SZ, gdesc);

  return OK;
}

/*It gets the message of a character*/
char *character_get_message(Character *charr) {
  if (!charr) return NULL;

  return charr->message;
}

/*It sets the message of a character*/
Status character_set_message(Character *charr, char *message) {
  if (!charr) return ERROR;

  if (!message) return ERROR;

  sprintf(charr->message, "%.*s", MESG_SIZE, message);

  return OK;
}

/*It gets the health of a character*/
int character_get_health(Character *charr) {
  if (!charr) return -1;

  return charr->health;
}

/*It sets the health of a character*/
Status character_set_health(Character *charr, int health) {
  if (!charr) return ERROR;

  if (health < 0) return ERROR;

  charr->health = health;

  return OK;
}

/*It gets the friendlyness (ally/enemy) of a character*/
Bool character_get_friendly(Character *charr) {
  if (!charr) return FALSE;

  return charr->friendly;
}

/*It sets the friendlyness of a character*/
Status character_set_friendly(Character *charr, Bool friendly) {
  if (!charr) return ERROR;

  charr->friendly = friendly;

  return OK;
}

/*It prints the character information*/
Status character_print(Character *charr) {
  if (!charr) return ERROR;

  fprintf(stdout, "\n\n-------------\n\n");
  fprintf(stdout, "=> Character id: %ld\n", charr->id);
  fprintf(stdout, "=> Character name: %s\n", charr->name);
  fprintf(stdout, "=> Character health: %d\n", charr->health);
  fprintf(stdout, "=> Character graphic description: %s\n", charr->gdesc);
  fprintf(stdout, "=> Character message: %s\n", charr->message);
  fprintf(stdout, "=> Character friendly: %s\n",
          (charr->friendly == TRUE) ? "True" : "False");

  return OK;
}
