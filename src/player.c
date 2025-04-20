/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Tiago Oselka
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Initial size of the player´s inventory
 * 
 */
#define INIT_BAG_SIZE 8

/**
 * @brief Struct that stores the information of a player: Id, name, its backpack, its health, location and graphic description
 * @author Tiago Oselka
 * 
 */
struct _Player {
  Id id;                    /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  Role role;                /*!< Role of the player in the game*/
  char gdesc[PLY_GD_SZ + 1];/*!< Graphic description of the player*/
  Id location;              /*!< Id number of the space where the player is currently located*/
  int health;               /*!< The player's health */
  Id armor;                 /*!< Id of the object that serves as armor */
  Id weapon;                /*!< Id of the object that serves as weapon */
  Inventory *backpack;     /*!< Inventory that the player carries */
};

/*It creates a new player by allocating its memory and initializing its members*/
Player *player_create(Id id) {
  Player *play = NULL;

  if(id == NO_ID) return NULL;
  if (!(play = (Player *)malloc(sizeof(Player)))) return NULL;

  play->id = id;
  play->role = UNDEFINED;
  play->name[0] = '\0';
  play->weapon = 0;
  play->armor = 0;
  play->backpack = inventory_create();
	inventory_set_max_objects(play->backpack,INIT_BAG_SIZE);
  play->health = 10;
  play->location = NO_ID;

  return play;
}

/*It destroys a player by freeing its allocated memory*/
Status player_destroy(Player *play) {
  if (!play) return ERROR;

  if (play->backpack) {
    if (!inventory_destroy(play->backpack)) return ERROR;
  }

  free(play);
  play = NULL;

  return OK;
}

/*It gets the id of a player*/
Id player_get_id(Player *play) {
  if (!play) return NO_ID;

  return play->id;
}

/*It sets the id of a player*/
Status player_set_id(Player *play, Id id) {
  if (!play) return ERROR;

  play->id = id;

  return OK;
}

/*It gets the role of a player*/
Role player_get_role(Player *play) {
  if (!play) return NO_ROLE;

  return play->role;
}

/*It sets the role of a player*/
Status player_set_role(Player *play, Role role) {
  if (!play || role == NO_ROLE) return ERROR;

  play->role = role;

  return OK;
}

/*It gets the name of a player*/
char *player_get_name(Player *play) {
  if (!play) return NULL;

  return play->name;
}

/*It sets the name of a player*/
Status player_set_name(Player *play, char *name) {
  if (!play || !name) return ERROR;

  sprintf(play->name, "%.*s", WORD_SIZE, name);

  return OK;
}

/*Gets the weapon equipped by a player*/
Status player_get_weapon(Player *play, Id *weapon){
  if(!play || !weapon) return ERROR;

  *weapon = play->weapon;

  return OK;
}

/*Sets the armor equipped by a player*/
Status player_set_weapon(Player *play, Id weapon_id){
  if(!play) return ERROR;

  play->weapon = weapon_id;

  return OK;
}

/*Gets the armor equipped by a player*/
Status player_get_armor(Player *play, Id *armor){
  if(!play || !armor) return ERROR;

  *armor = play->armor;

  return OK;
}

/*Sets the armor equipped by a player*/
Status player_set_armor(Player *play, Id armor_id){
  if(!play) return ERROR;

  play->armor = armor_id;
  return OK;
}

/*It gets the backpack of the player*/
Inventory *player_get_backpack(Player *play) {
  if (!play) return NULL;

  return play->backpack;
}

/*It adds the object to the player's inventory*/
Status player_add_object(Player *play, Id id_obj) {
  if (!play || id_obj == NO_ID || id_obj == 0) return ERROR;

  if (inventory_add_object(play->backpack, id_obj) == ERROR) return ERROR;

  return OK;
}

/*It deletes the object from the player's inventory*/
Status player_delete_object(Player *play, Id id_obj) {
  if (!play || id_obj == NO_ID) return ERROR;

  if (inventory_remove_object(play->backpack, id_obj) == ERROR) return ERROR;

  return OK;
}

/*It checks if the player is carrying the object or not*/
Bool player_has_object(Player *play, Id id_obj) {
  if (!play || id_obj == NO_ID) return FALSE;

  return inventory_find_object(play->backpack, id_obj);
}

/*It checks if the player's inventory is full or not*/
Bool player_inventory_is_full(Player *play) {
  if (!play) return FALSE;

  return inventory_is_full(play->backpack);
}

/*It sets the size of the backpack of the player*/
Status player_set_inventory_size(Player *play, int size) {
  if (!play || size < 0 || size > SET_MX_CAP) return ERROR;

  if (inventory_set_max_objects(play->backpack, size) == ERROR) return ERROR;

  return OK;
}

/*It gets the health of the player*/
int player_get_health(Player *play) {
  if (!play) return -1;

  return play->health;
}

/*It sets the health of the player*/
Status player_set_health(Player *play, int health) {
  if (!play) return ERROR;

  play->health = health;

  return OK;
}

/*It gets the location of the player*/
Id player_get_location(Player *play) {
  if (!play) return NO_ID;

  return play->location;
}

/*It sets the location of the player*/
Status player_set_location(Player *play, Id location_id) {
  if (!play) return ERROR;

  play->location = location_id;

  return OK;
}

/*It gets the graphic description of a player*/
char *player_get_gdesc(Player *play) {
  if (!play) return NULL;

  return play->gdesc;
}

/*It sets the graphic description of a player*/
Status player_set_gdesc(Player *play, char *gdesc) {
  if (!play || !gdesc) return ERROR;

  sprintf(play->gdesc, "%.*s", PLY_GD_SZ, gdesc);

  return OK;
}

/*It prints the player information*/
Status player_print(Player *play) {
  /*extern char *role_to_str[N_ROLES];*/
  if (!play) return ERROR;


  fprintf(stdout, "\n\n-------------\n\n");
  fprintf(stdout, "=> Player id: %ld\n", play->id);
  fprintf(stdout, "=> Player name: %s\n", play->name);
  /*fprintf(stdout, "=> Player role: %s\n", role_to_str[play->role - NO_ROLE]);*/
  fprintf(stdout, "=> Player health: %d\n", play->health);
  fprintf(stdout, "=> Player equipped weapon: %ld\n", play->weapon);
  fprintf(stdout, "=> Player equipped armor: %ld\n", play->armor);
  fprintf(stdout, "=> Player gdesc: %s\n", play->gdesc);
  fprintf(stdout, "=> Player backpack: \n");
	set_print(inventory_get_objects(play->backpack));
  fprintf(stdout, "=> Player location Id: %ld\n", play->location);

  return OK;
}