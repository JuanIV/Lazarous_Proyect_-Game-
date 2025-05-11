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
 * @test Test player creation with valid ID
 * @pre Valid ID passed to player_create
 * @post Non NULL pointer to player is returned
 */
void test1_player_create();

/**
 * @test Test player creation with invalid ID
 * @pre NO_ID passed to player_create
 * @post NULL pointer is returned
 */
void test2_player_create();

/**
 * @test Test destruction of a valid player
 * @pre A valid player has been created
 * @post player_destroy returns OK
 */
void test1_player_destroy();

/**
 * @test Test destruction of a NULL player
 * @pre NULL pointer passed to player_destroy
 * @post player_destroy returns ERROR
 */
void test2_player_destroy();

/**
 * @test Test getting the ID from a valid player
 * @pre A valid player with a known ID
 * @post The correct ID is returned
 */
void test1_player_get_id();

/**
 * @test Test getting the ID from a NULL player
 * @pre NULL pointer passed to player_get_id
 * @post NO_ID is returned
 */
void test2_player_get_id();

/**
 * @test Test setting the ID of a player
 * @pre Valid player and ID
 * @post The ID is updated correctly
 */
void test1_player_set_id();

/**
 * @test Test setting the ID of a NULL player
 * @pre NULL player and valid ID
 * @post player_set_id returns ERROR
 */
void test2_player_set_id();

/**
 * @test Test getting the role of a player
 * @pre Valid player with no role set
 * @post UNDEFINED is returned
 */
void test1_player_get_role();

/**
 * @test Test getting role from NULL player
 * @pre NULL player
 * @post NO_ROLE is returned
 */
void test2_player_get_role();

/**
 * @test Test setting player role
 * @pre Valid player and role
 * @post Role is set correctly
 */
void test1_player_set_role();

/**
 * @test Test setting invalid player role
 * @pre Valid player and NO_ROLE
 * @post player_set_role returns ERROR
 */
void test2_player_set_role();

/**
 * @test Test getting player name
 * @pre Name set previously
 * @post The correct name is returned
 */
void test1_player_get_name();

/**
 * @test Test getting player name from NULL
 * @pre NULL player
 * @post NULL is returned
 */
void test2_player_get_name();

/**
 * @test Test setting valid player name
 * @pre Valid player and name
 * @post Name is set correctly
 */
void test1_player_set_name();

/**
 * @test Test setting NULL name
 * @pre Valid player and NULL name
 * @post player_set_name returns ERROR
 */
void test2_player_set_name();

/**
 * @test Test setting name to NULL player
 * @pre NULL player and valid name
 * @post player_set_name returns ERROR
 */
void test3_player_set_name();

/**
 * @test Test getting player weapon
 * @pre Weapon was set before
 * @post Correct weapon ID is returned
 */
void test1_player_get_weapon();

/**
 * @test Test getting weapon from NULL player
 * @pre NULL player
 * @post player_get_weapon returns ERROR
 */
void test2_player_get_weapon();

/**
 * @test Test getting weapon with NULL ID pointer
 * @pre Valid player and NULL ID pointer
 * @post player_get_weapon returns ERROR
 */
void test3_player_get_weapon();

/**
 * @test Test setting player weapon
 * @pre Valid player and weapon ID
 * @post Weapon is set correctly
 */
void test1_player_set_weapon();

/**
 * @test Test setting weapon to NULL player
 * @pre NULL player and valid ID
 * @post player_set_weapon returns ERROR
 */
void test2_player_set_weapon();

/**
 * @test Test getting player backpack
 * @pre Valid player
 * @post Backpack pointer is not NULL
 */
void test1_player_get_backpack();

/**
 * @test Test getting backpack from NULL player
 * @pre NULL player
 * @post NULL is returned
 */
void test2_player_get_backpack();

/**
 * @test Test adding object to player
 * @pre Valid player and object ID
 * @post Object is added successfully
 */
void test1_player_add_object();

/**
 * @test Test adding object to NULL player
 * @pre NULL player
 * @post player_add_object returns ERROR
 */
void test2_player_add_object();

/**
 * @test Test deleting existing object from player
 * @pre Object was previously added
 * @post Object is removed successfully
 */
void test1_player_delete_object();

/**
 * @test Test deleting non-existing object from player
 * @pre Valid player, but object not present
 * @post player_delete_object returns ERROR
 */
void test2_player_delete_object();

/**
 * @test Test checking object presence
 * @pre Object added to player
 * @post TRUE is returned
 */
void test1_player_has_object();

/**
 * @test Test checking object not present
 * @pre Valid player with no such object
 * @post FALSE is returned
 */
void test2_player_has_object();

/**
 * @test Test inventory is not full
 * @pre Empty or partially filled inventory
 * @post FALSE is returned
 */
void test1_player_inventory_is_full();

/**
 * @test Test inventory still not full after one add
 * @pre One object added
 * @post FALSE is returned
 */
void test2_player_inventory_is_full();

/**
 * @test Test setting valid inventory size
 * @pre Valid player and size
 * @post Inventory size is updated
 */
void test1_player_set_inventory_size();

/**
 * @test Test setting invalid inventory size
 * @pre Valid player and negative size
 * @post player_set_inventory_size returns ERROR
 */
void test2_player_set_inventory_size();

/**
 * @test Test getting initial health
 * @pre Player created
 * @post Default health is returned
 */
void test1_player_get_health();

/**
 * @test Test getting health from NULL player
 * @pre NULL player
 * @post -1 is returned
 */
void test2_player_get_health();

/**
 * @test Test setting valid health
 * @pre Valid player and health value
 * @post Health is updated correctly
 */
void test1_player_set_health();

/**
 * @test Test setting health on NULL player
 * @pre NULL player and valid value
 * @post player_set_health returns ERROR
 */
void test2_player_set_health();

/**
 * @test Test getting initial location
 * @pre Player created
 * @post NO_ID is returned
 */
void test1_player_get_location();

/**
 * @test Test getting location from NULL player
 * @pre NULL player
 * @post NO_ID is returned
 */
void test2_player_get_location();

/**
 * @test Test setting location
 * @pre Valid player and location ID
 * @post Location is updated correctly
 */
void test1_player_set_location();

/**
 * @test Test setting location on NULL player
 * @pre NULL player
 * @post player_set_location returns ERROR
 */
void test2_player_set_location();

/**
 * @test Test getting graphical description
 * @pre Description was set
 * @post Correct description is returned
 */
void test1_player_get_gdesc();

/**
 * @test Test getting gdesc from NULL player
 * @pre NULL player
 * @post NULL is returned
 */
void test2_player_get_gdesc();

/**
 * @test Test setting graphical description
 * @pre Valid player and description
 * @post gdesc is set correctly
 */
void test1_player_set_gdesc();

/**
 * @test Test setting gdesc on NULL player
 * @pre NULL player
 * @post player_set_gdesc returns ERROR
 */
void test2_player_set_gdesc();

/**
 * @test Test getting closeup at line
 * @pre Line was set before
 * @post Correct line is returned
 */
void test1_player_get_closeup_at();

/**
 * @test Test getting closeup line from NULL player
 * @pre NULL player
 * @post NULL is returned
 */
void test2_player_get_closeup_at();

/**
 * @test Test getting all closeup lines
 * @pre All lines set
 * @post All lines returned correctly
 */
void test1_player_get_closeup();

/**
 * @test Test getting closeup from NULL player
 * @pre NULL player
 * @post player_get_closeup returns ERROR
 */
void test2_player_get_closeup();

/**
 * @test Test setting closeup line
 * @pre Valid player and line
 * @post Line is stored correctly
 */
void test1_player_set_closeup_at();

/**
 * @test Test setting closeup line on NULL player
 * @pre NULL player and line
 * @post player_set_closeup_at returns ERROR
 */
void test2_player_set_closeup_at();

/**
 * @test Test getting armor value
 * @pre Valid player with armor set
 * @post Correct armor value is returned
 */ 
void test1_player_get_armor();

/**
 * @test Test getting armor from NULL player
 * @pre NULL player
 * @post -1 is returned
 */
void test2_player_get_armor();

/**
 * @test Test setting armor value
 * @pre Valid player and armor value
 * @post Armor is set correctly
 */
void test1_player_set_armor();

/**
 * @test Test setting armor on NULL player
 * @pre NULL player and valid value
 * @post player_set_armor returns ERROR
 */
void test2_player_set_armor();

#endif