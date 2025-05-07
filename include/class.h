/**
 * @brief It defines the object class module interface
 *
 * @file class.h
 * @author Alina Datsko
 * @version 0 (1)
 * @date 05-05-2025 
 * @copyright GNU Public License
 */

#ifndef CLASS_H
#define CLASS_H
 
#include "types.h"

/**
 * @brief Maximum size of the description of an object
 *
 */
#define OBJ_DESC_MX 1000

typedef struct _Class Class;

/**
 * @brief It creates and initializes a new class
 * @author Juan Ibáñez
 *
 * @param id Id of the class
 * @return A new class, initialized
 */
Class *class_create(Id id);

/**
 * @brief It destroys a class freeing allocated memory
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_destroy(Class *class);

/**
 * @brief It gets the id of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return Id of the class
 */
Id class_get_id(Class *class);

/**
 * @brief Sets the id of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param id New id for the class
 * @return ERROR if class doesnt exist or id is NO_ID, OK otherwise
 */
Status class_set_id(Class *class, Id id);

/**
 * @brief Gets the tag of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return Tag of the class
 */
Tag class_get_tag(Class *class);

/**
 * @brief Sets the tag of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param tag New tag for the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_set_tag(Class *class, Tag tag);

/**
 * @brief Gets the name of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return String with the name of the class
 */
char *class_get_name(Class *class);

/**
 * @brief Sets the name of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param name New name for the class
 * @return ERROR if class or name dont exist, OK otherwise
 */
Status class_set_name(Class *class, char *name);

/**
 * @brief Gets the description of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return String with the description of the class
 */
char *class_get_desc(Class *class);

/**
 * @brief Sets the description of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param desc New description for the class
 * @return ERROR if class or desc doesnt exist, OK otherwise
 */
Status class_set_desc(Class *class, char *desc);

/**
 * @brief Gets a line of the close up aspect of a class
 * @author Juan Ibáñez
 * 
 * @param pos Number of the line wanted
 * @return String with the visuals
 */
char *class_get_closeup_at_pos(Class *class, int pos);

/**
 * @brief Gets the full close up aspect of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param closeup Group of strings to store the close up
 * @return ERROR if class or desc doesnt exist, OK otherwise
 */
Status class_get_closeup(Class *class, char closeup[POV_HGHT][POV_WDTH + 1]);

/**
 * @brief Sets a line of the close up aspect of a class
 * @author Juan Ibáñez
 * 
 * @param pos Number of the line wanted
 * @param closeup New line
 * @return OK if everything went well, ERROR otherwise
 */
Status class_set_closeup_at_pos(Class *class, int pos, char *closeup);

/**
 * @brief Gets the movable property of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param bool Pointer to a boolean where the value will be stored
 * @return ERROR if there was a mistake, OK otherwise
 * bool: TRUE if its movable, FALSE if its not
 */
Status class_get_movable(Class *class, Bool *bool);

/**
 * @brief Sets the movable property of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param movable Boolean new movable property
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_set_movable(Class *class, Bool movable);

/*Gets the dependency of a class*/
/**
 * @brief Gets the dependency of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param dependency Pointer to an Id where the dependency will be stored
 * @return ERROR if there was a mistake, OK otherwise
 * dependency: Id of the class that is needed to use this one
 */
Status class_get_dependency(Class *class, Id *dependency);

/**
 * @brief Sets the dependency of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param dependency Id of the new dependency class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_set_dependency(Class *class, Id dependency);

/**
 * @brief Gets the open property of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param open Pointer to an Id where the value will be stored
 * @return ERROR if there was a mistake, OK otherwise
 * open: Id of the link that it can open
 */
Status class_get_open(Class *class, Id *open);

/**
 * @brief Sets the link this class can open
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param open Id of the link the class can open
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_set_open(Class *class, Id open);

/*Gets the luck property of a class*/
/**
 * @brief Gets the luck property of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return Int value of the luck bonus the class gives
 */
int class_get_luck(Class *class);

/**
 * @brief Sets the luck bonus of a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @param luck New luck bonus value
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_set_luck(Class *class, int luck);

/**
 * @brief Prints all information about a class
 * @author Juan Ibáñez
 *
 * @param class Pointer to the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status class_print(Class *class);

#endif
