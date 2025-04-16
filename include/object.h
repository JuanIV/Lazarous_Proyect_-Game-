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
 typedef enum {NORMAL, HEALER, WEAPON, ARMOR, TRAP} Tag;
 
 /**
  * @brief It stores the id and name of an object
  *
  */
 typedef struct _Object Object;
 
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
  * @brief Sets the id of an object to an especific id
  * @author Juan Ibáñez
  *
  * @param obj Pointer to the object
  * @param id New object id to be set
  * @return ERROR if the object or id are non-existing, OK otherwise
  */
 Status object_set_id(Object *obj, Id id);
 
 /**
  * @brief Gets the tag of an ocject
  * @author Juan Ibáñez
  * 
  * @param obj Pointer to the object
  * @return Tag of the object
  */
 Tag object_get_tag(Object *obj);
 
 /**
  * @brief Sets the tag of an object
  * 
  * @param obj Pointer to the object
  * @param tag New tag for the object
  * @return ERROR if the object does not exist, OK otherwise
  */
 Status object_set_tag(Object *obj, Tag tag);
 
 /**
  * @brief Gets the name of an object
  * @author Juan Ibáñez
  *
  * @param obj Pointer to the object
  * @return Name of the object
  */
 char *object_get_name(Object *obj);
 
 /**
  * @brief Sets a string as the name of an object
  * @author Juan Ibáñez
  *
  * @param obj Pointer to the object
  * @param name String of the name
  * @return OK if everything goes well, ERROR if object is NULL or the name is
  * too big
  */
 Status object_set_name(Object *obj, char *name);
 
 /**
  * @brief Gets the description of an object
  * @author Juan Ibáñez
  * 
  * @param obj Pointer to the object
  * @return String with the description of the object
  */
 char *object_get_desc(Object *obj);
 
 /**
  * @brief Sets the description of an object
  * 
  * @param obj Pointer to the object
  * @param desc String with the new description
  * @return OK if everything went well, ERROR if NULL arguments
  */
 Status object_set_desc(Object *obj, char *desc);
 
 /**
  * @brief Gets the use_value of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @return Use value of the object
  */
 int object_get_use_value(Object *obj);
 
 /**
  * @brief Sets the use_value of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @param use_value New use value
  * @return OK if everything went well, ERROR if the object does not exist
  */
 Status object_set_use_value(Object *obj, int use_value);
 
 /**
  * @brief Gets the dependency of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @return Id of the object it depends on
  */
 Id object_get_dependency(Object *obj);
 
 /**
  * @brief Sets the dependency of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @param depedency New dependency id
  * @return OK if everything went well, ERROR if the object does not exist
  */
 Status object_set_dependency(Object *obj, Id depedency);
 
 /**
  * @brief Gets the open property of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @return Id of the object it opens
  */
 Id object_get_open(Object *obj);
 
 /**
  * @brief Sets the open property of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @param opens New open id
  * @return OK if everything went well, ERROR if the object does not exist
  */ 
 Status object_set_open(Object *obj, Id opens);
 
 /**
  * @brief Gets the movable property of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @return TRUE if the object is movable, FALSE otherwise
  */
 Bool object_get_movable(Object *obj);
 
 /**
  * @brief Sets the movable property of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @param movable New movable value
  * @return OK if everything went well, ERROR if the object does not exist
  */
 Status object_set_movable(Object *obj, Bool movable);
 
 /**
  * @brief Gets the luck property of an object
  * @author Alina Datsko
  * 
  * @param obj Pointer to the object
  * @return Luck of the object
  */
 int object_get_luck(Object *obj);
 
 /**
  * @brief Sets the luck property of an object
  * @author Alina Datsko
  *
  * @param obj Pointer to the object
  * @param luck New luck value
  * @return OK if everything went well, ERROR if the object does not exist
  */
 Status object_set_luck(Object *obj, int luck);
 
 /**
  * @brief Prints all information about an object
  * @author Juan Ibáñez
  *
  * @param obj Pointer to the object
  * @return ERROR if the object does not exist, OK if everything went well
  */
 Status object_print(Object *obj);
 
 #endif
 