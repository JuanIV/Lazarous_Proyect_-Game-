/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Juan Ibáñez
 * @version 0 (1)
 * @date 07-02-2025 (fix 09-02-2025)
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Maximum size of the description of an object
 *
 */
#define OBJ_DESC_MX 1000

/**
 * @brief It defines the type of objects there are in the game
 *
 */
typedef enum { NO_TAG = -1, NORMAL, HEALER, WEAPON, ARMOR, TRAP } Tag;

typedef struct _Class Class;

/**
 * @brief It stores the id and name of an object
 *
 */
typedef struct _Object Object;

/**
 * @brief It creates and initializes a new class
 * @author Juan Ibáñez
 * 
 * @param id Id of the class
 * @return A new class, initialized
 */
Class *object_class_create(Id id);

/**
 * @brief It destroys a class freeing allocated memory
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_destroy(Class *class);

/**
 * @brief It gets the id of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Id of the class
 */
Id object_class_get_id(Class *class);

/**
 * @brief Sets the id of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param id New id for the class
 * @return ERROR if class doesnt exist or id is NO_ID, OK otherwise
 */
Status object_class_set_id(Class *class, Id id);

/**
 * @brief Gets the tag of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Tag of the class
 */
Tag object_class_get_tag(Class *class);

/**
 * @brief Sets the tag of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param tag New tag for the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_tag(Class *class, Tag tag);

/**
 * @brief Gets the name of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return String with the name of the class
 */
char *object_class_get_name(Class *class);

/**
 * @brief Sets the name of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param name New name for the class
 * @return ERROR if class or name dont exist, OK otherwise
 */
Status object_class_set_name(Class *class, char *name);

/**
 * @brief Gets the description of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return String with the description of the class
 */
char *object_class_get_desc(Class *class);

/**
 * @brief Sets the description of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param desc New description for the class
 * @return ERROR if class or desc doesnt exist, OK otherwise
 */
Status object_class_set_desc(Class *class, char *desc);

/**
 * @brief Gets the use value of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Int use value of the class
 */
int object_class_get_use_value(Class *class);

/**
 * @brief Sets the use value of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param value New use value for the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_use_value(Class *class, int value);

/**
 * @brief Gets the movable property of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return TRUE if its movable, FALSE if its not
 */
Bool object_class_get_movable(Class *class);

/**
 * @brief Sets the movable property of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param movable Boolean new movable property
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_movable(Class *class, Bool movable);

/*Gets the dependency of a class*/
/**
 * @brief Gets the dependency of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Id of the class that is needed to use this one
 */
Id object_class_get_dependency(Class *class);

/**
 * @brief Sets the dependency of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param dependency Id of the new dependency class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_dependency(Class *class, Id dependency);

/**
 * @brief Gets the open property of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Id of the link that it can open
 */
Id object_class_get_open(Class *class);

/**
 * @brief Sets the link this class can open
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param open Id of the link the class can open
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_open(Class *class, Id open);

/*Gets the luck property of a class*/
/**
 * @brief Gets the luck property of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return Int value of the luck bonus the class gives
 */
int object_class_get_luck(Class *class);

/**
 * @brief Sets the luck bonus of a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @param luck New luck bonus value
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_set_luck(Class *class, int luck);

/**
 * @brief Prints all information about a class
 * @author Juan Ibáñez
 * 
 * @param class Pointer to the class
 * @return ERROR if class doesnt exist, OK otherwise
 */
Status object_class_print(Class *class);

/**
 * @brief Creates a new object by allocating memmory for it and initialazing its
 * members
 * @author Juan Ibáñez
 *
 * @param id Id of the object
 * @return A new object, initialized
 */
Object *object_create(Id id);

/**
 * @brief Destroys an object by freeing its allocated memmory
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object being destroyed
 * @return OK if everything went well, ERROR if the object does not exist
 */
Status object_destroy(Object *obj);

/**
 * @brief It gets the id from an object
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @return Id of the object
 */
Id object_get_id(Object *obj);

/**
 * @brief Gets the class of an object
 * @author Juan Ibáñez
 * 
 * @param obj Pointer to the object
 * @return Pointer to the class of the object
 */
Class *object_get_class(Object *obj);

/**
 * @brief Sets the class of an object
 * @author Juan Ibáñez
 * 
 * @param obj Pointer to the object
 * @param class Pointer to the new class
 * @return ERROR if class or object dont exist, OK otherwise
 */
Status object_set_class(Object *obj, Class *class);

/**
 * @brief Sets the id of an object to an especific id
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @param id New object id to be set
 * @return ERROR if the object or id are non-existing, OK otherwise
 */
Status object_set_id(Object *obj, Id id);

/**
 * @brief Gets the id of the class of an object
 * @author Juan  Ibáñez
 * 
 * @param obj Pointer to the object
 * @return Id of the class of the object
 */
Id object_get_class_id(Object *obj);

/**
 * @brief Gets the tag of an ocject
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @return Tag of the object
 */
Tag object_get_tag(Object *obj);

/**
 * @brief Gets the name of an object
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @return Name of the object
 */
char *object_get_name(Object *obj);

/**
 * @brief Gets the description of an object
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @return String with the description of the object
 */
char *object_get_desc(Object *obj);

/**
 * @brief Gets the use_value of an object
 * @author Alina Datsko
 *
 * @param obj Pointer to the object
 * @return Use value of the object
 */
int object_get_use_value(Object *obj);

/**
 * @brief Gets the dependency of an object
 * @author Alina Datsko
 *
 * @param obj Pointer to the object
 * @return Id of the object it depends on
 */
Id object_get_dependency(Object *obj);

/**
 * @brief Gets the open property of an object
 * @author Alina Datsko
 *
 * @param obj Pointer to the object
 * @return Id of the object it opens
 */
Id object_get_open(Object *obj);

/**
 * @brief Gets the movable property of an object
 * @author Alina Datsko
 *
 * @param obj Pointer to the object
 * @return TRUE if the object is movable, FALSE otherwise
 */
Bool object_get_movable(Object *obj);

/**
 * @brief Gets the luck property of an object
 * @author Alina Datsko
 *
 * @param obj Pointer to the object
 * @return Luck of the object
 */
int object_get_luck(Object *obj);

/**
 * @brief Gets the role of a trap
 * 
 * @param obj Pointer to the object
 * @return Role of the object
 */
Role object_get_role(Object *obj);

/**
 * @brief Sets the role of a trap
 * 
 * @param obj Pointer to the object
 * @param role New role for the trap
 * @return ERROR if obj or role dont exist, OK otherwise
 */
Status object_set_role(Object *obj, Role role);

/**
 * @brief Prints all information about an object
 * @author Juan Ibáñez
 *
 * @param obj Pointer to the object
 * @return ERROR if the object does not exist, OK if everything went well
 */
Status object_print(Object *obj);

#endif
