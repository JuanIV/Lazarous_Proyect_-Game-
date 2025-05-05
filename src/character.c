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
  Id id;                       /*!< Id number of the character, it must be unique */
  Role role;                   /*!< Role of the character in the game*/
  char name[WORD_SIZE + 1];    /*!< Name of the character */
  char gdesc[CHR_GD_SZ + 1];   /*!< Graphic description of the character*/
  char close_up[POV_HGHT][POV_WDTH + 1]; /*!< Close up aspect of the character*/ 
  char message[MESG_SIZE + 1]; /*!< Message of the character*/
  Id following;                /*!< Id of the player it's following*/
  Id weapon;                   /*!< Id of the object that serves as weapon */
  Id armor;                    /*!< Id of the object that serves as armor */
  int health;                  /*!< Health of the character*/
  int damage;                  /*!< Damage that the character deals*/
};

/*It creates a new character by allocating its memory and initializing its members*/
Character *character_create(Id id) {
  Character *character = NULL;

  if (!(character = (Character *)malloc(sizeof(Character)))) return NULL;

  character->id = id;
  character->role = UNDEFINED;
  character->name[0] = '\0';
  character->gdesc[0] = '\0';
  character->message[0] = '\0';
  character->following = NO_ID;
  character->weapon = NO_ID;
  character->armor = NO_ID;
  character->health = 0;
  character->damage = 0;

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

/*It gets the role of a character*/
Role character_get_role(Character *charr) {
  if (!charr) return NO_ROLE;

  return charr->role;
}

/*It sets the role of a character*/
Status character_set_role(Character *charr, Role role) {
  if (!charr) return ERROR;

  charr->role = role;

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

/*Gets the close up aspect of a character*/
char *character_get_closeup_at_pos(Character *charr, int pos) {
  if(!charr) return NULL;

  if(pos<0 || pos>=POV_HGHT) return NULL;

  return charr->close_up[pos];
}

/*Gets the full close up of a character*/
Status character_get_closeup(Character *charr, char closeup[POV_HGHT][POV_WDTH + 1]){
  int i;

  if(!charr || !closeup) return ERROR;

  for(i=0;i<POV_HGHT;i++){
    sprintf(closeup[i], "%.*s", POV_WDTH, charr->close_up[i]);
  }

  return OK;
}

/*Sets the close up aspect of a character*/
Status character_set_closeup_at_pos(Character *charr, int pos, char *closeup) {
  int i;

  if(!charr) return ERROR;

  if( pos<0 || pos >= POV_HGHT) return ERROR;

  if(!closeup) charr->close_up[pos][0] = '\0';

  sprintf(charr->close_up[pos], "%-*.*s", POV_WDTH,POV_WDTH, closeup);

  /*We prevent from saving a line break in the gdesc*/
  for (i = 0; i < POV_WDTH; i++) {
    if ((charr->close_up[pos][i] == '\n') || (charr->close_up[pos][i] == '\r'))
      charr->close_up[pos][i] = ' ';
  }

  return OK;
}

/*It gets the id of the player the character is following*/
Status character_get_following(Character *charr, Id *following) {
  if(!charr || !following) return ERROR;

  *following = charr->following;

  return OK;
}

/*It sets the id of the player the character is following*/
Status character_set_following(Character *charr, Id id) {
  if(!charr) return ERROR;

  charr->following = id;

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

/*Gets the weapon equipped by the character*/
Status character_get_weapon(Character *charr, Id *weapon){
  if(!charr || !weapon) return ERROR;

  *weapon = charr->weapon;

  return OK;
}

/*Sets the armor equipped by the character*/
Status character_set_weapon(Character *charr, Id weapon_id){
  if(!charr) return ERROR;

  charr->weapon = weapon_id;
  return OK;
}

/*Gets the armor equipped by the character*/
Status character_get_armor(Character *charr, Id *armor){
  if(!charr || !armor) return ERROR;

  *armor = charr->armor;

  return OK;
}

/*Sets the armor equipped by the character*/
Status character_set_armor(Character *charr, Id armor_id){
  if(!charr) return ERROR;

  charr->armor = armor_id;
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

int character_get_damage(Character *charr){
  if(!charr) return -1;

  return charr->damage;
}

Status character_set_damage(Character *charr, int damage){
  if(!charr || damage < 0) return ERROR;

  charr->damage = damage;

  return OK;
}

/*It prints the character information*/
Status character_print(Character *charr) {
  /*extern char *role_to_str[N_ROLES]*/
  if (!charr) return ERROR;

  fprintf(stdout, "\n\n-------------\n\n");
  fprintf(stdout, "=> Character id: %ld\n", charr->id);
  fprintf(stdout, "=> Character name: %s\n", charr->name);
  /*fprintf(stdout, "=> Character role: %s\n", role_to_str[charr->role - NO_ROLE]);*/
  fprintf(stdout, "=> Character health: %d\n", charr->health);
  fprintf(stdout, "=> Character equipped weapon: %ld\n", charr->weapon);
  fprintf(stdout, "=> Character equipped armor: %ld\n", charr->armor);
  fprintf(stdout, "=> Character graphic description: %s\n", charr->gdesc);
  fprintf(stdout, "=> Character message: %s\n", charr->message);

  return OK;
}
