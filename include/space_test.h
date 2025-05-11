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
 * @test Test space creation with valid ID
 * @pre A valid ID is passed to space_create
 * @post Non NULL pointer to space is returned
 */
void test1_space_create();

/**
 * @test Test space creation with invalid ID
 * @pre NO_ID is passed to space_create
 * @post NULL pointer is returned
 */
void test2_space_create();

/**
 * @test Test destroying a valid space
 * @pre A valid space is created
 * @post space_destroy returns OK
 */
void test1_space_destroy();

/**
 * @test Test destroying a NULL space
 * @pre NULL pointer passed to space_destroy
 * @post space_destroy returns ERROR
 */
void test2_space_destroy();

/**
 * @test Test getting ID of a valid space
 * @pre A space with known ID is created
 * @post Correct ID is returned
 */
void test1_space_get_id();

/**
 * @test Test getting ID from a NULL space
 * @pre NULL space passed to space_get_id
 * @post NO_ID is returned
 */
void test2_space_get_id();

/**
 * @test Test setting name of a valid space
 * @pre A valid space and name
 * @post Name is correctly stored
 */
void test1_space_set_name();

/**
 * @test Test setting name in a NULL space
 * @pre NULL space passed to space_set_name
 * @post space_set_name returns ERROR
 */
void test2_space_set_name();

/**
 * @test Test getting name of a valid space
 * @pre Space has a name set
 * @post Correct name is returned
 */
void test1_space_get_name();

/**
 * @test Test getting name from NULL space
 * @pre NULL space
 * @post NULL is returned
 */
void test2_space_get_name();

/**
 * @test Test setting graphical description line
 * @pre Valid space, line and index
 * @post space_set_gdesc_at returns OK
 */
void test1_space_set_gdesc_at();

/**
 * @test Test setting gdesc line in NULL space
 * @pre NULL space
 * @post space_set_gdesc_at returns ERROR
 */
void test2_space_set_gdesc_at();

/**
 * @test Test getting graphical description line
 * @pre Line was previously set
 * @post Correct line is returned
 */
void test1_space_get_gdesc_at();

/**
 * @test Test getting gdesc from NULL space
 * @pre NULL space
 * @post NULL is returned
 */
void test2_space_get_gdesc_at();

/**
 * @test Test setting discovered flag
 * @pre Valid space and boolean value
 * @post Value is stored correctly
 */
void test1_space_set_discovered();

/**
 * @test Test setting discovered on NULL space
 * @pre NULL space
 * @post space_set_discovered returns ERROR
 */
void test2_space_set_discovered();

/**
 * @test Test getting discovered flag
 * @pre Discovered value has been set
 * @post Correct value is returned
 */
void test1_space_get_discovered();

/**
 * @test Test getting discovered from NULL space
 * @pre NULL space
 * @post space_get_discovered returns ERROR
 */
void test2_space_get_discovered();

/**
 * @test Test adding object to space
 * @pre Valid space and object ID
 * @post Object is added successfully
 */
void test1_space_add_object();

/**
 * @test Test adding object to NULL space
 * @pre NULL space
 * @post space_add_object returns ERROR
 */
void test2_space_add_object();

/**
 * @test Test removing object from space
 * @pre Object previously added
 * @post Object is removed successfully
 */
void test1_space_remove_object();

/**
 * @test Test removing object from NULL space
 * @pre NULL space
 * @post space_remove_object returns ERROR
 */
void test2_space_remove_object();

/**
 * @test Test finding object in space
 * @pre Object added to space
 * @post space_find_object returns TRUE
 */
void test1_space_find_object();

/**
 * @test Test finding object in NULL space
 * @pre NULL space
 * @post space_find_object returns FALSE
 */
void test2_space_find_object();

/**
 * @test Test getting object at specific position
 * @pre Object added at known position
 * @post Correct ID is returned
 */
void test1_space_get_object_at_pos();

/**
 * @test Test getting object at position in NULL space
 * @pre NULL space
 * @post NO_ID is returned
 */
void test2_space_get_object_at_pos();

/**
 * @test Test checking if object container is full
 * @pre Valid space
 * @post Returns FALSE if not full
 */
void test1_space_objects_is_full();

/**
 * @test Test checking if NULL space is full
 * @pre NULL space
 * @post Returns TRUE
 */
void test2_space_objects_is_full();

/**
 * @test Test getting number of objects
 * @pre Multiple objects added
 * @post Correct count is returned
 */
void test1_space_get_num_objects();

/**
 * @test Test getting object count from NULL space
 * @pre NULL space
 * @post Returns 0
 */
void test2_space_get_num_objects();

/**
 * @test Test setting trap in space
 * @pre Valid space and ID
 * @post Trap is set successfully
 */
void test1_space_set_trap();

/**
 * @test Test setting trap in NULL space
 * @pre NULL space
 * @post space_set_trap returns ERROR
 */
void test2_space_set_trap();

/**
 * @test Test getting trap from space
 * @pre Trap set previously
 * @post Correct ID is returned
 */
void test1_space_get_trap();

/**
 * @test Test getting trap from NULL space
 * @pre NULL space
 * @post space_get_trap returns ERROR
 */
void test2_space_get_trap();

/**
 * @test Test adding character to space
 * @pre Valid space and character ID
 * @post Character added successfully
 */
void test1_space_add_character();

/**
 * @test Test adding character to NULL space
 * @pre NULL space
 * @post space_add_character returns ERROR
 */
void test2_space_add_character();

/**
 * @test Test removing character from space
 * @pre Character added before removal
 * @post Character is removed successfully
 */
void test1_space_remove_character();

/**
 * @test Test removing character from NULL space
 * @pre NULL space
 * @post space_remove_character returns ERROR
 */
void test2_space_remove_character();

/**
 * @test Test finding character in space
 * @pre Character added to space
 * @post space_find_character returns TRUE
 */
void test1_space_find_character();

/**
 * @test Test finding character in NULL space
 * @pre NULL space
 * @post space_find_character returns FALSE
 */
void test2_space_find_character();

/**
 * @test Test getting character at specific position
 * @pre Character added at known position
 * @post Correct ID is returned
 */
void test1_space_get_character_at_pos();

/**
 * @test Test getting character from NULL space
 * @pre NULL space
 * @post NO_ID is returned
 */
void test2_space_get_character_at_pos();

/**
 * @test Test checking if character container is full
 * @pre Valid space
 * @post Returns FALSE if not full
 */
void test1_space_characters_is_full();

/**
 * @test Test checking if NULL space is full
 * @pre NULL space
 * @post Returns TRUE
 */
void test2_space_characters_is_full();

/**
 * @test Test getting number of characters
 * @pre Characters added
 * @post Correct number is returned
 */
void test1_space_get_num_characters();

/**
 * @test Test getting character count from NULL space
 * @pre NULL space
 * @post Returns -1
 */
void test2_space_get_num_characters();

#endif