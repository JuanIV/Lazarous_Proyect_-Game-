/**
 * @brief It defines the character module
 *
 * @file character.h
 * @author Tiago Oselka
 * @version 0 (1)
 * @date 25-02-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/**
 * @brief Defines the maximum length of a characters message
 *
 */
#define MESG_SIZE 1000

/**
 * @brief Defines the size in characters of the graphic description of a
 * character
 *
 */
#define CHR_GD_SZ 6

/**
 * @brief It stores a characters id, name, graphic description, health and
 * friendlyness
 *
 */
typedef struct _Character Character;

/**
 * @brief It creates a new character by allocating its memory and initializing
 * its members
 * @author Tiago Oselka
 *
 * @param id The id our character will have
 * @return Pointer to the created character
 */
Character *character_create(Id id);

/**
 * @brief It destroys a character by freeing its allocated memory
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character that will be destroyed
 * @return Status
 */
Status character_destroy(Character *charr);

/**
 * @brief It gets the id of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @return the id of the character
 */
Id character_get_id(Character *charr);

/**
 * @brief It sets the id of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @param id the id number to be assigned to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_id(Character *charr, Id id);

/**
 * @brief It gets the name of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @return a string with the name of the character
 */
char *character_get_name(Character *charr);

/**
 * @brief It sets the name of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_name(Character *charr, char *name);

/**
 * @brief It gets the graphic description of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @return a string with the gdesc of a character
 */
char *character_get_gdesc(Character *charr);

/**
 * @brief It sets the graphic description of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @param gdesc the graphic description of the character
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_gdesc(Character *charr, char *gdesc);

/**
 * @brief It gets the id of the player the character is following
 * @author Tiago Oselka
 * 
 * @param charr Pointer to a character
 * @return The Id of said player and NO_ID in casa of error or if the character is not following anyone
 */
Id character_get_following(Character *charr);

/**
 * @brief It sets the id of the player the character is following
 * @author Tiago Oselka
 * 
 * @param charr Pointer to a character
 * @param id Id of the player the character will be following
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_following(Character *charr, Id id);

/**
 * @brief It gets the message of a character
 * @author Juan Ibáñez
 *
 * @param charr Pointer to the character
 * @return String with the message of the character
 */
char *character_get_message(Character *charr);

/**
 * @brief It sets the message of a character
 * @author Juan Ibáñez
 *
 * @param charr Pointer to the character
 * @param message The new message for the character
 * @return OK if everything went well, ERROR if ther was a mistake
 */
Status character_set_message(Character *charr, char *message);

/**
 * @brief Gets the weapon equipped by the character
 * @author Juan Ibáñez
 * 
 * @param charr Pointer to the character
 * @return Id of the object that serves as weapon
 */
Id character_get_weapon(Character *charr);

/**
 * @brief Sets the armor equipped by the character
 * @author Juan Ibáñez
 * 
 * @param charr Pointer to the character
 * @param weapon_id Id of the new weapon
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_weapon(Character *charr, Id weapon_id);

/**
 * @brief Gets the armor equipped by the character
 * @author Juan Ibáñez
 * 
 * @param charr Pointer to the character
 * @return Id of the object that serves as armor
 */
Id character_get_armor(Character *charr);

/**
 * @brief Sets the armor equipped by the character
 * @author Juan Ibáñez
 * 
 * @param charr Pointer to the character
 * @param armor_id Id of the new armor
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_armor(Character *charr, Id armor_id);

/**
 * @brief It gets the health of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @return the number of health points a character has
 */
int character_get_health(Character *charr);

/**
 * @brief It sets the health of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @param health the number of health points of the character
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_health(Character *charr, int health);

/**
 * @brief It gets the friendlyness (ally/enemy) of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @return TRUE if the character is friendly and FALSE otherwise
 */
Bool character_get_friendly(Character *charr);

/**
 * @brief It sets the friendlyness of a character
 * @author Tiago Oselka
 *
 * @param charr a pointer to the character
 * @param friendly a bool that represents wether a character is friendly or not
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_friendly(Character *charr, Bool friendly);

/**
 * @brief It prints the character information
 * @author Tiago Oselka
 *
 * This function shows the id, name, graphic description, message, health and friendliness, as
 * well as the id of the player being followed 
 * @param charr a pointer to the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_print(Character *charr);

#endif
