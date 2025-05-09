/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author Tiago Oselka
 * @version 0
 * @date 21-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

/**
 * @brief Defines the number of ways a direction can be written
 *
 */
#define N_DIRT 2

/**
 * @brief Defines the ways a direction can be written (short, long)
 *
 */
typedef enum { DIRS, DIRL } DirectionType;

/**
 * @brief This struct stores all the information related to a link
 *
 */
typedef struct _Link Link;

/**
 * @brief It creates a new link, allocating memory and initializing its members
 * @author Tiago Oselka
 *
 * @param id the identification number for the new link
 * @return a new link, initialized
 */
Link *link_create(Id id);

/**
 * @brief It destroys a link, freeing the allocated memory
 * @author Tiago Oselka
 *
 * @param link a pointer to the link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link *link);

/**
 * @brief It gets the id of a link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @return the id of the link
 */
Id link_get_id(Link *link);

/**
 * @brief It gets the name of a link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @return  a string with the name of the link
 */
char *link_get_name(Link *link);

/**
 * @brief It sets the name of a link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link *link, char *name);

/**
 * @brief It gets the id of the space located at the origin of the link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @return the id number of the space located at the origin
 */
Id link_get_orig(Link *link);

/**
 * @brief It sets the id of the space located at the origin of the link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param origin the id number of the space located at the origin
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_orig(Link *link, Id origin);

/**
 * @brief It gets the id of the space located at the destination of the link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @return the id number of the space located at the destination of the link
 */
Id link_get_dest(Link *link);

/**
 * @brief It sets the id of the space located at the destination of the link
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param destination the id number of the space located at the destination
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_dest(Link *link, Id destination);

/**
 * @brief It gets the direction followed when traversing the link orig -> dest
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @return the said direction
 */
Direction link_get_direction(Link *link);

/**
 * @brief It sets the direction followed when traversing the link orig -> dest
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param direction the said direction
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief It gets the state of the link, TRUE if it's opened or FALSE if its
 * closed
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param bool pointer to a Bool where the function will store the result
 * @return the state of the link
 * bool: TRUE if the connection is opened or FALSE if it isn't opened
 */
Status link_get_open(Link *link, Bool *bool);

/**
 * @brief It sets the state of the link, TRUE if it's opened or FALSE if its
 * closed
 * @author Tiago Oselka
 *
 * @param link a pointer to the link
 * @param bool boolean that represents the state of the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_open(Link *link, Bool bool);

/**
 * @brief Gets if the link needs a key or not to be opened
 * @author Juan Ibáñez
 * 
 * @param link Pointer to the link
 * @param bool pointer to a Bool where the function will store the result
 * @return the state of the link
 * bool: TRUE if the connection is opened or FALSE if its closed
 */
Status link_get_locked(Link *link, Bool *bool);

/**
 * @brief Sets if the link needs a key or not to be opened
 * @author Juan Ibáñez
 * 
 * @param link Pointer to the link
 * @param bool New state of the lock
 * @return ERROR if link doesnt exist, OK otherwise
 */
Status link_set_locked(Link * link, Bool bool);

/**
 * @brief Gets if the two spaces are connected
 * @author Juan Ibáñez
 * 
 * @param link Pointer to the link
 * @param bool Pointer to a boolean to store the result
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_get_connected(Link *link, Bool *bool);

/**
 * @brief Sets the state of conexion between the spaces
 * @author Juan Ibáñez
 * 
 * @param link Pointer to the link
 * @param bool New state of conexion (True or False)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_connected(Link *link, Bool bool);

/**
 * @brief Gets the role that can open or close the link
 * @author Juan Ibáñez
 *
 * @param link Pointer to the link
 * @return Role that can open and close the link
 */
Role link_get_open_role(Link *link);

/**
 * @brief Sets the role that can open the link
 * @author Juan Ibáñez
 *
 * @param link Pointer to the link
 * @param role New role for the link
 * @return ERROR if link or role are invalid, OK otherwise
 */
Status link_set_open_role(Link *link, Role role);

/**
 * @brief Gets the role that can use the link
 * @author Juan Ibáñez
 *
 * @param link Pointer to the link
 * @return Only role that can use this link
 */
Role link_get_use_role(Link *link);

/**
 * @brief Sets the only role that can use the link
 * @author Juan Ibáñez
 *
 * @param link Pointer to the link
 * @param role New role that can use it
 * @return ERROR if link or role are invalid, OK otherwise
 */
Status link_set_use_role(Link *link, Role role);

/**
 * @brief It prints the link information
 *
 * @param link a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link *link);

#endif
