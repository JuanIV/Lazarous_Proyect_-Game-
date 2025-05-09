/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "set.h"
#include "types.h"

/**
 * @brief Defines the height in lines of the graphic description of a space
 *
 */
#define SP_GD_HGHT 5

/**
 * @brief Defines the width in characters of the graphic description of a space
 *
 */
#define SP_GD_WTH 23

/**
 * @brief It stores the Id and name of a space and its adjacent spaces' ids
 *
 */
typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG (modified by Tiago Oselka)
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space *space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG (modified by Tiago Oselka)
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
char *space_get_name(Space *space);

/**
 * @brief Sets the graphic description of a space
 * @author Juan Ibáñez
 *
 * @param space Pointer to the space
 * @param gdesc Array of string with de graphics of the space
 * @return ERROR if any line is too big or small, OK if everything went well
 */
Status space_set_gdesc_at(Space *space, char *gdesc, int pos);

/**
 * @brief Gets the graphic descrpition of a space
 * @author Juan Ibáñez
 *
 * @param space Pointer to the space
 * @param line Number of the line being get
 * @return A string with the graphics of the space in a certain line
 */
char *space_get_gdesc_at(Space *space, int line);

/**
 * @brief It sets the discovered status of a space
 * @author Alina Datsko Yaskerska
 * 
 * @param space a pointer to the space
 * @param discovered the bool to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space *space, Bool discovered);

/**
 * @brief It gets the discovered status of a space
 * @author Alina Datsko Yaskerska
 * 
 * @param space a pointer to the space
 * @return the discovered status of the space
 */
Status space_get_discovered(Space *space, Bool *bool);

/**
 * @brief It adds an object to the space
 * @author Juan Ibáñez
 *
 * @param space Pointer to the space
 * @param obj Id of the object that will be added
 * @return OK if everything goes well, ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id obj);

/**
 * @brief It removes an object from a space
 * @author Juan Ibáñez
 *
 * @param space Pointer to the space
 * @param obj Id of the object that will be removed
 * @return OK if everything goes well, ERROR if there was some mistake
 */
Status space_remove_object(Space *space, Id obj);

/**
 * @brief It gets whether the space has a certain object or not
 * @author Juan Ibáñez
 *
 * @param space a pointer to the space
 * @param obj Id of the object to be
 * @return TRUE if the space has the object, FALSE if not
 */
Bool space_find_object(Space *space, Id obj);

/**
 * @brief It gets the id of the object at a certain position inside the space
 * @author Juan Ibáñez
 *
 * @param space Pointer to the space
 * @param pos Position of the object inside of the space
 * @return Id of the object at the determined position
 */
Id space_get_object_at_pos(Space *space, int pos);

/**
 * @brief It gets whether the set in a space is full
 * @author Tiago Oselka
 *
 * @param space a pointer to the space
 * @return TRUE if the space is full, FALSE if not
 */
Bool space_objects_is_full(Space *space);

/**
 * @brief It gets the number of objects contained in a space
 * @author Juan Ibáñez
 * 
 * @param space Pointer to the space
 * @return Number of objects in the space
 */
int space_get_num_objects(Space *space);

/**
 * @brief Adds a character to the set of characters of the space
 * @author Tiago Oselka
 *
 * @param space Pointer to the space
 * @param charr Id of the character being added
 * @return OK if everything goes well, ERROR if there was some mistake
 */
Status space_add_character(Space *space, Id charr);

/**
 * @brief Removes a character from the set of characters of the space
 * @author Tiago Oselka
 *
 * @param space Pointer to the space
 * @param charr Id of the character being removed
 * @return OK if everything goes well, ERROR if there was some mistake
 */
Status space_remove_character(Space *space, Id charr);

/**
 * @brief It gets whether the space has a certain character or not
 * @author Tiago Oselka
 *
 * @param space a pointer to the space
 * @param charr Id of the character to be found
 * @return TRUE if the space has the object, FALSE if not
 */
Bool space_find_character(Space *space, Id charr);

/**
 * @brief It gets the id of the character at a certain position inside the space
 * @author Tiago Oselka
 *
 * @param space Pointer to the space
 * @param pos Position of the set of characters inside of the space
 * @return Id of the object at the determined position
 */
Id space_get_character_at_pos(Space *space, int pos);

/**
 * @brief Checks whether the set of characters is full
 * @author Tiago Oselka
 * 
 * @param space Pointer to a space
 * @return The state of the set of characters and TRUE in case of error
 */
Bool space_characters_is_full(Space *space);

/**
 * @brief It gets the number of characters contained in a space
 * @author Tiago Oselka
 * 
 * @param space Pointer to the space
 * @return Number of characters in the space
 */
int space_get_num_characters(Space *space);

/**
 * @brief Gets the id of the trap currently set on a space
 * @author Juan Ibáñez
 * 
 * @param space Pointer the space
 * @param trap Pointer where the function will store the result
 * @return ERROR if there was any mistake, OK otherwise
 * trap: Id of the trap in the space
 */
Status space_get_trap(Space *space, Id *trap);

/**
 * @brief Sets a trap in a space
 * 
 * @param space Pointer to the space
 * @param trap Id of the new trap
 * @return ERROR if space does not exist, OK otherwise
 */
Status space_set_trap(Space *space, Id trap);

/**
 * @brief It prints the space information
 * @author LM Tiago Oselka
 *
 * This fucntion shows the id and name of the space, whether the space is discovered,
 * the list of objects and characters and its graphic description
 * 
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space *space);

#endif
