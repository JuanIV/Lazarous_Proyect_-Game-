/**
 * @brief It declares the tests for the character module
 * 
 * @file character_test.h
 * @author Juan Ibañez
 * @version 1.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

/**
 * @test Test character creation
 * @pre None
 * @post Non NULL pointer to character
 */
void test1_character_create();

/**
 * @test Test character creation
 * @pre None
 * @post Character id is set correctly
 */
void test2_character_create();

/**
 * @test Test character creation
 * @pre None
 * @post Character name, gdesc and message are initialized to empty strings
 */
void test3_character_create();

/**
 * @test Test character destruction
 * @pre Non NULL pointer to character
 * @post Output = OK
 */
void test1_character_destroy();

/**
 * @test Test character destruction
 * @pre NULL pointer to character
 * @post Output = ERROR
 */
void test2_character_destroy();

/**
 * @test Test getting character id
 * @pre Non NULL pointer to character
 * @post Output == Expected id
 */
void test1_character_get_id();

/**
 * @test Test getting character id
 * @pre NULL pointer to character
 * @post Output == NO_ID
 */
void test2_character_get_id();

/**
 * @test Test setting character id
 * @pre Non NULL pointer to character
 * @post Id is propertly set
 */
void test1_character_set_id();

/**
 * @test Test getting character name
 * @pre Non NULL pointer to character
 * @post Output == Expected name
 */
void test1_character_get_name();

/**
 * @test Test getting character name
 * @pre NULL pointer to character
 * @post Output == NULL
 */
void test2_character_get_name();

/**
 * @test Test setting character name
 * @pre Non NULL pointer to character
 * @post Name is propertly set
 */
void test1_character_set_name();

/**
 * @test Test getting character graphic description
 * @pre Non NULL pointer to character
 * @post Output == Expected graphic description
 */
void test1_character_get_gdesc();

/**
 * @test Test getting character graphic description
 * @pre NULL pointer to character
 * @post Output == NULL
 */
void test2_character_get_gdesc();

/**
 * @test Test setting character graphic description
 * @pre Non NULL pointer to character
 * @post Gdesc is correctly set
 */
void test1_character_set_gdesc();

/**
 * @test Test getting character message
 * @pre Non NULL pointer to character
 * @post Output == Expected message
 */
void test1_character_get_message();

/**
 * @test Test getting character message
 * @pre NULL pointer to character
 * @post Output == NULL
 */
void test2_character_get_message();

/**
 * @test Test setting character message
 * @pre Non NULL pointer to character
 * @post Message is correctly set
 */
void test1_character_set_message();

/**
 * @test Test getting character health
 * @pre Non NULL pointer to character
 * @post Output == Expected health
 */
void test1_character_get_health();

/**
 * @test Test getting character health
 * @pre NULL pointer to character
 * @post Output == -1
 */
void test2_character_get_health();

/**
 * @test Test setting character health
 * @pre Non NULL pointer to character
 * @post Health sets correctly
 */
void test1_character_set_health();

/**
 * @test Test getting character friendly
 * @pre Non NULL pointer to character
 * @post Output == Expected value
 */
void test1_character_get_friendly();

/**
 * @test Test getting character friendly
 * @pre Non NULL pointer to character
 * @post Output == Expected value
 */
void test2_character_get_friendly();

/**
 * @test Test getting character friendly
 * @pre NULL pointer to character
 * @post Output == FALSE
 */
void test3_character_get_friendly();


#endif