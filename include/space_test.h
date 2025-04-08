/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog (Modified by Juan Ibañez)
 * @version 2.0
 * @date 20-02-2025 / 
 * @copyright GNU Public License
 */

 #ifndef SPACE_TEST_H
 #define SPACE_TEST_H
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Non NULL pointer to space 
  */
 void test1_space_create();
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Space_ID == Supplied Space Id
  */
 void test2_space_create();
 
 /**
  * @test Test function for space_name setting
  * @pre String with space name
  * @post Output == OK 
  */
 void test1_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre Pointer to space = NULL 
  * @post Output == ERROR
  */
 void test2_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre Pointer to space_name = NULL (pointer to space = NON NULL) 
  * @post Output == ERROR
  */
 void test3_space_set_name();
 
 /**
  * @test Test function for setting whether the space is discovered or not 
  * @pre Valid space and valid bool type
  * @post Output == OK
  */
 void test1_space_set_discovered();
 
 /**
  * @test Test function for setting whether the space is discovered or not 
  * @pre Pointer to space = NULL
  * @post Output == ERROR
  */
 void test2_space_set_discovered();
 
 /**
  * @test Test function for getting space ID
  * @pre Valid space
  * @post Output == Space ID
  */
 void test1_space_get_id();
 
 /**
  * @test Test function for getting space ID
  * @pre Pointer to space = NULL
  * @post Output == NO_ID
  */
 void test2_space_get_id();
 
 /**
  * @test Test function for getting space name
  * @pre Valid space with a name set
  * @post Output == Space name
  */
 void test1_space_get_name();
 
 /**
  * @test Test function for getting space name
  * @pre Pointer to space = NULL
  * @post Output == NULL
  */
 void test2_space_get_name();
 
 /**
  * @test Test function for getting whether the space is discovered or not
  * @pre Valid space with a discovered set
  * @post Output == Bool TRUE
  */
 void test1_space_get_discovered();
 
 /**
  * @test Test function for getting whether the space is discovered or not
  * @pre Pointer to space = NULL
  * @post Output == Bool FALSE
  */
 void test2_space_get_discovered();
 
 /**
  * @test Test function for setting graphic description at a specific position
  * @pre Valid space, valid graphic description, and valid position
  * @post Output == OK
  */
 void test1_space_set_gdesc_at();
 
 /**
  * @test Test function for setting graphic description at a specific position
  * @pre Non NULL pointer to space
  * @post Output == expected string
  */
 void test2_space_set_gdesc_at();
 
 /**
  * @test Test function for setting graphic description at a specific position
  * @pre Invalid position (out of bounds)
  * @post Output == ERROR
  */
 void test3_space_set_gdesc_at();
 
 /**
  * @test Test function for getting graphic description at a specific line
  * @pre Valid space and valid line
  * @post Output == expected string at the specified line
  */
 void test1_space_get_gdesc_at();
 
 /**
  * @test Test function for getting graphic description at a specific line
  * @pre Pointer to space = NULL
  * @post Output == NULL
  */
 void test2_space_get_gdesc_at();
 
 /**
  * @test Test function for adding an object to the space
  * @pre Valid space and valid object ID
  * @post Object was added correctly
  */
 void test1_space_add_object();
 
 /**
  * @test Test function for adding an object to the space
  * @pre Pointer to space = NULL
  * @post Output == ERROR
  */
 void test2_space_add_object();
 
 /**
  * @test Test function for removing an object from the space
  * @pre Valid space and valid object ID
  * @post Object was removed correctly
  */
 void test1_space_remove_object();
 
 /**
  * @test Test function for removing an object from the space
  * @pre Pointer to space = NULL
  * @post Output == ERROR
  */
 void test2_space_remove_object();
 
 /**
  * @test Test function for finding an object in the space
  * @pre Valid space and valid object ID
  * @post Output == TRUE (object found)
  */
 void test1_space_find_object();
 
 /**
  * @test Test function for finding an object in the space
  * @pre Valid space and invalid object ID
  * @post Output == FALSE (object not found)
  */
 void test2_space_find_object();
 
 /**
  * @test Test function for finding an object in the space
  * @pre Pointer to space = NULL
  * @post Output == FALSE
  */
 void test3_space_find_object();
 
 /**
  * @test Test function for getting an object at a specific position in the space
  * @pre Valid space and valid position
  * @post Output == Object ID at the specified position
  */
 void test1_space_get_object_at_pos();
 
 /**
  * @test Test function for getting an object at a specific position in the space
  * @pre Pointer to space = NULL
  * @post Output == NO_ID
  */
 void test2_space_get_object_at_pos();
 
 /**
  * @test Test function for checking if the space is full of objects
  * @pre Valid space with objects added up to capacity
  * @post Output == TRUE (space is full)
  */
 void test1_space_is_full();
 
 /**
  * @test Test function for checking if the space is full of objects
  * @pre Valid space with fewer objects than capacity
  * @post Output == FALSE (space is not full)
  */
 void test2_space_is_full();
 
 /**
  * @test Test function for setting a character in the space
  * @pre Valid space and valid character ID
  * @post Output == OK
  */
 void test1_space_set_character();
 
 /**
  * @test Test function for setting a character in the space
  * @pre Pointer to space = NULL
  * @post Output == ERROR
  */
 void test2_space_set_character();
 
 /**
  * @test Test function for getting the character in the space
  * @pre Valid space with a character set
  * @post Output == Character ID
  */
 void test1_space_get_character();
 
 /**
  * @test Test function for getting the character in the space
  * @pre Pointer to space = NULL
  * @post Output == NO_ID
  */
 void test2_space_get_character();
 
 #endif