/**
 * @brief It defines the object module interface
 *
 * @file player.h
 * @author Tiago Oselka
 * @version 0
 * @date 09-02-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"

/**
 * @brief Defines the size in characters of the graphic description of a
 * player
 *
 */
#define PLY_GD_SZ 5

/**
 * @brief It stores a players ID, name, location and object being carried
 *
 */
typedef struct _Player Player;

/**
 * @brief It creates a new player by allocating its memory and initializing its
 * members
 * @author Tiago Oselka
 *
 * @param id The id our player will have
 * @return Pointer to the created player
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player by freeing its allocated memory
 * @author Tiago Oselka
 *
 * @param play a pointer to the player that will be destroyed
 * @return Status
 */
Status player_destroy(Player *play);

/**
 * @brief It gets the id of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @return the id of the player
 */
Id player_get_id(Player *play);

/**
 * @brief It sets the id of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @param id the id number to be assigned to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_id(Player *play, Id id);

/**
 * @brief It gets the role of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @return the role of the player
 */
Role player_get_role(Player *play);

/**
 * @brief It sets the role of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @param role the role to be assigned to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_role(Player *play, Role role);

/**
 * @brief It gets the name of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @return a string with the name of the player
 */
char *player_get_name(Player *play);

/**
 * @brief It sets the name of a player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player *play, char *name);


/**
 * @brief Gets the weapon equipped by a player
 * @author Juan Ibáñez
 * 
 * @param play Pointer to the player
 * @param weapon Pointer where the id of the weapon is stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 * weapon: Id of the object that serves as weapon
 */
Status player_get_weapon(Player *play, Id *weapon);

/**
 * @brief Sets the weapon equipped by a player
 * @author Juan Ibáñez
 * 
 * @param play Pointer to the player
 * @param weapon_id Id of the new weapon
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_weapon(Player *play, Id weapon_id);

/**
 * @brief Gets the armor equipped by a player
 * @author Juan Ibáñez
 * 
 * @param play Pointer to the player
 * @param armor Pointer where the id of the armor is stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 * armor: Id of the object that serves as armor
 */
Status player_get_armor(Player *play, Id *armor);

/**
 * @brief Sets the armor equipped by a player
 * @author Juan Ibáñez
 * 
 * @param play Pointer to the player
 * @param armor_id Id of the new armor
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_armor(Player *play, Id armor_id);

/**
 * @brief It gets the backpack of the player
 * @author Lucas Blanco Rodriguez
 *
 * @param play Pointer to the player
 * @return Pointer to the players backpack
 */
Inventory *player_get_backpack(Player *play);

/**
 * @brief It adds the object to the player's inventory
 * @author Alina Datsko Yaskerska
 *
 * @param play a pointer to the player
 * @param id_obj the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_add_object(Player *play, Id id_obj);

/**
 * @brief It deletes the object from the player's inventory
 * @author Lucas Blanco Rodriguez
 *
 * @param play a pointer to the player
 * @param id_obj the id of the object to be deleted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_delete_object(Player *play, Id id_obj);

/**
 * @brief It checks if the player is carrying the object or not
 * @author Lucas Blanco Rodriguez
 *
 * @param play a pointer to the player
 * @param id_obj the id of the object being carried by the player
 * @return TRUE if the player is carrying the object, FALSE if it is not
 */
Bool player_has_object(Player *play, Id id_obj);

/**
 * @brief It checks if the player's inventory is full or not
 * @author Lucas Blanco Rodriguez
 * 
 * @param play a pointer to the player
 * @return TRUE if the inventory is full, FALSE if it is not
 */
Bool player_inventory_is_full(Player *play);

/**
  * @brief It sets the size of the backpack of the player
  * @author Alina Datsko Yaskerska
  * 
  * @param play a pointer to the player
  * @param size the size to be set
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
Status player_set_inventory_size(Player *play, int size);

/**
 * @brief It gets the health of the player
 * @author Tiago Oselka
 *
 * @param character a pointer to the player
 * @return the number of health points the player has
 */
int player_get_health(Player *play);

/**
 * @brief It sets the health of the player
 * @author Tiago Oselka
 *
 * @param character a pointer to the player
 * @param health the number of health points of the player
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_health(Player *play, int health);

/**
 * @brief It prints the player information
 * @author Tiago Oselka
 *
 * This function shows the id, name and location of the player, as well as the
 * Id of the object being carried.
 * @param play a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player *play);

/**
 * @brief It gets the location of the player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @return the id number of the space the player is at
 */
Id player_get_location(Player *play);

/**
 * @brief It sets the location of the player
 * @author Tiago Oselka
 *
 * @param play a pointer to the player
 * @param location_id the id of the new current location of the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player *play, Id location_id);

/**
 * @brief It gets the graphic description of a player
 * @author Lucas Blanco Rodríguez
 *
 * @param play a pointer to the player
 * @return a string with the gdesc of the player
 */
char *player_get_gdesc(Player *play);

/**
 * @brief It sets the graphic description of a player
 * @author Lucas Blanco Rodríguez
 *
 * @param play a pointer to the player
 * @param gdesc the graphic description of the player
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_gdesc(Player *play, char *gdesc);

#endif
