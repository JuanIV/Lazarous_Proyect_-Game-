/**
 * @brief It declares the tests for the class module
 *
 * @file class_test.h
 * @author Alina Datsko
 * @version 1.0
 * @date 05-05-2025
 * @copyright GNU Public License
 */

#ifndef CLASS_TEST_H
#define CLASS_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "class.h"
#include "test.h"

/**
 * @test Test class creation with valid ID
 * @pre Valid ID 
 * @post Non NULL pointer to class
 */
void test1_class_create();

/**
 * @test Test class creation with invalid ID (NO_ID)
 * @pre NO_ID as ID
 * @post Output == NULL
 */
void test2_class_create();

/**
 * @test Test class destruction with valid class
 * @pre Non NULL pointer to class
 * @post Output == OK
 */
void test1_class_destroy();

/**
 * @test Test class destruction with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_destroy();

/**
 * @test Test getting class ID from valid class
 * @pre Non NULL pointer to class with known ID
 * @post Output == Expected ID
 */
void test1_class_get_id();

/**
 * @test Test getting ID from NULL class
 * @pre NULL pointer to class
 * @post Output == NO_ID
 */
void test2_class_get_id();

/**
 * @test Test setting class ID with valid input
 * @pre Non NULL pointer and valid ID
 * @post Output == OK
 */
void test1_class_set_id();

/**
 * @test Test setting ID with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_id();

/**
 * @test Test getting class tag from valid class
 * @pre Non NULL pointer to class with known tag
 * @post Output == Expected tag
 */
void test1_class_get_tag();

/**
 * @test Test getting tag from NULL class
 * @pre NULL pointer to class
 * @post Output == NO_TAG or equivalent
 */
void test2_class_get_tag();

/**
 * @test Test setting class tag with valid input
 * @pre Non NULL pointer and valid tag
 * @post Output == OK
 */
void test1_class_set_tag();

/**
 * @test Test setting tag with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_tag();

/**
 * @test Test getting class name from valid class
 * @pre Non NULL pointer to class with known name
 * @post Output == Expected name
 */
void test1_class_get_name();

/**
 * @test Test getting name from NULL class
 * @pre NULL pointer to class
 * @post Output == NULL
 */
void test2_class_get_name();

/**
 * @test Test setting class name with valid input
 * @pre Non NULL pointer and valid name
 * @post Output == OK
 */
void test1_class_set_name();

/**
 * @test Test setting name with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_name();

/**
 * @test Test getting description from valid class
 * @pre Non NULL pointer to class with known description
 * @post Output == Expected description
 */
void test1_class_get_desc();

/**
 * @test Test getting description from NULL class
 * @pre NULL pointer to class
 * @post Output == NULL
 */
void test2_class_get_desc();

/**
 * @test Test setting description with valid input
 * @pre Non NULL pointer and valid description
 * @post Output == OK
 */
void test1_class_set_desc();

/**
 * @test Test setting description with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_desc();

/**
 * @test Test getting closeup at a position from valid class
 * @pre Non NULL pointer and valid pos
 * @post Output == Expected line
 */
void test1_class_get_closeup_at_pos();

/**
 * @test Test getting closeup at position with NULL class
 * @pre NULL pointer to class
 * @post Output == NULL
 */
void test2_class_get_closeup_at_pos();

/**
 * @test Test getting full closeup from valid class
 * @pre Non NULL pointer to class with defined closeup
 * @post Output == OK
 */
void test1_class_get_closeup();

/**
 * @test Test getting closeup with NULL class
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_get_closeup();

/**
 * @test Test setting closeup at a position with valid data
 * @pre Non NULL pointer, valid pos and string
 * @post Output == OK
 */
void test1_class_set_closeup_at_pos();

/**
 * @test Test setting closeup at position with NULL class
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_closeup_at_pos();

/**
 * @test Test getting movable property from valid class
 * @pre Non NULL pointer and valid bool pointer
 * @post Output == OK
 */
void test1_class_get_movable();

/**
 * @test Test getting movable from NULL class
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_get_movable();

/**
 * @test Test setting movable property with valid input
 * @pre Non NULL pointer and valid boolean
 * @post Output == OK
 */
void test1_class_set_movable();

/**
 * @test Test setting movable with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_movable();

/**
 * @test Test getting dependency from valid class
 * @pre Non NULL pointer and valid Id pointer
 * @post Output == OK
 */
void test1_class_get_dependency();

/**
 * @test Test getting dependency from NULL class
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_get_dependency();

/**
 * @test Test setting dependency with valid input
 * @pre Non NULL pointer and valid Id
 * @post Output == OK
 */
void test1_class_set_dependency();

/**
 * @test Test setting dependency with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_dependency();

/**
 * @test Test getting open property from valid class
 * @pre Non NULL pointer and valid Id pointer
 * @post Output == OK
 */
void test1_class_get_open();

/**
 * @test Test getting open from NULL class
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_get_open();

/**
 * @test Test setting open property with valid input
 * @pre Non NULL pointer and valid Id
 * @post Output == OK
 */
void test1_class_set_open();

/**
 * @test Test setting open with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_open();

/**
 * @test Test getting luck value from valid class
 * @pre Non NULL pointer to class with known luck
 * @post Output == Expected luck
 */
void test1_class_get_luck();

/**
 * @test Test getting luck from NULL class
 * @pre NULL pointer to class
 * @post Output == -1 (or error value)
 */
void test2_class_get_luck();

/**
 * @test Test setting luck value with valid input
 * @pre Non NULL pointer and valid integer
 * @post Output == OK
 */
void test1_class_set_luck();

/**
 * @test Test setting luck with NULL pointer
 * @pre NULL pointer to class
 * @post Output == ERROR
 */
void test2_class_set_luck();

#endif /* CLASS_TEST_H */