/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Alina Datsko
 * @version 2.0
 * @date 04-04-2025 / 
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre None
 * @post Non NULL pointer to player
 */
void test1_player_create();

/**
 * @test Test player creation with invalid ID
 * @pre Invalid ID
 * @post Output == NULL
 */
void test2_player_create();

/**
 * @test Test player destruction
 * @pre Non NULL pointer to player
 * @post Output == OK
 */
void test1_player_destroy();

/**
 * @test Test player destruction with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_destroy();

/**
 * @test Test getting player ID
 * @pre Non NULL pointer to player
 * @post Output == Expected ID
 */
void test1_player_get_id();

/**
 * @test Test getting player ID with NULL pointer
 * @pre NULL pointer to player
 * @post Output == NO_ID
 */
void test2_player_get_id();

/**
 * @test Test setting player ID
 * @pre Non NULL pointer to player and valid ID
 * @post Output == OK
 */
void test1_player_set_id();

/**
 * @test Test setting player ID with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_id();

/**
 * @test Test getting player name
 * @pre Non NULL pointer to player with a valid name
 * @post Output == Expected name
 */
void test1_player_get_name();

/**
 * @test Test getting player name with NULL pointer
 * @pre NULL pointer to player
 * @post Output == NULL
 */
void test2_player_get_name();

/**
 * @test Test setting player name
 * @pre Non NULL pointer to player and valid name
 * @post Output == OK
 */
void test1_player_set_name();

/**
 * @test Test setting player name with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_name();

/**
 * @test Test adding an object to the player's inventory
 * @pre Non NULL pointer to player and valid object ID
 * @post Output == OK
 */
void test1_player_add_object();

/**
 * @test Test adding an object with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_add_object();

/**
 * @test Test deleting an object from the player's inventory
 * @pre Non NULL pointer to player and valid object ID
 * @post Output == OK
 */
void test1_player_delete_object();

/**
 * @test Test deleting an object with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_delete_object();

/**
 * @test Test checking if the player has an object
 * @pre Non NULL pointer to player and valid object ID
 * @post Output == TRUE
 */
void test1_player_has_object();

/**
 * @test Test checking if the player has an object with NULL pointer
 * @pre NULL pointer to player
 * @post Output == FALSE
 */
void test2_player_has_object();

/**
 * @test Test checking if the player's inventory is full
 * @pre Player's inventory is full
 * @post Output == TRUE
 */
void test1_player_inventory_is_full();

/**
 * @test Test checking if the player's inventory is full with NULL pointer
 * @pre NULL pointer to player
 * @post Output == FALSE
 */
void test2_player_inventory_is_full();

/**
 * @test Test setting the size of the player's inventory
 * @pre Non NULL pointer to player and valid size
 * @post Output == OK
 */
void test1_player_set_inventory_size();

/**
 * @test Test setting the size of the player's inventory with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_inventory_size();

/**
 * @test Test setting the size of the player's inventory with negative size
 * @pre Non NULL pointer to player and negative size
 * @post Output == ERROR
 */
void test2_player_set_inventory_size();

/**
 * @test Test getting player health
 * @pre Non NULL pointer to player with valid health
 * @post Output == Expected health value
 */
void test1_player_get_health();

/**
 * @test Test getting player health with NULL pointer
 * @pre NULL pointer to player
 * @post Output == -1 (or equivalent error value)
 */
void test2_player_get_health();

/**
 * @test Test setting player health
 * @pre Non NULL pointer to player and valid health value
 * @post Output == OK
 */
void test1_player_set_health();

/**
 * @test Test setting player health with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_health();

/**
 * @test Test getting player location
 * @pre Non NULL pointer to player with valid location
 * @post Output == Expected location ID
 */
void test1_player_get_location();

/**
 * @test Test getting player location with NULL pointer
 * @pre NULL pointer to player
 * @post Output == NO_ID
 */
void test2_player_get_location();

/**
 * @test Test setting player location
 * @pre Non NULL pointer to player and valid location ID
 * @post Output == OK
 */
void test1_player_set_location();

/**
 * @test Test setting player location with NULL pointer
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_location();

/**
 * @test Test getting player graphic description
 * @pre Non NULL pointer to player with valid graphic description
 * @post Output == Expected graphic description
 */
void test1_player_get_gdesc();

/**
 * @test Test getting player graphic description with NULL pointer
 * @pre NULL pointer to player
 * @post Output == NULL
 */
void test2_player_get_gdesc();

/**
 * @test Test setting player graphic description
 * @pre Non NULL pointer to player and valid graphic description
 * @post Output == OK
 */
void test1_player_set_gdesc();

/**
 * @test Test setting player graphic description with NULL pointer 
 * @pre NULL pointer to player
 * @post Output == ERROR
 */
void test2_player_set_gdesc();

#endif /* PLAYER_TEST_H */