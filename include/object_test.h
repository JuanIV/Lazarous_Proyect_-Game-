/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Alina Datsko
 * @version 1.0
 * @date 06-05-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "test.h"

/**
 * @test Test object creation with valid ID
 * @pre Valid ID (e.g., 1)
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation with invalid ID (NO_ID)
 * @pre NO_ID as ID
 * @post Output == NULL
 */
void test2_object_create();

/**
 * @test Test object destruction with valid object
 * @pre Non NULL pointer to object
 * @post Output == OK
 */
void test1_object_destroy();

/**
 * @test Test object destruction with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_destroy();

/**
 * @test Test getting object ID from valid object
 * @pre Non NULL pointer to object with known ID
 * @post Output == Expected ID
 */
void test1_object_get_id();

/**
 * @test Test getting ID from NULL object
 * @pre NULL pointer to object
 * @post Output == NO_ID
 */
void test2_object_get_id();

/**
 * @test Test setting object ID with valid input
 * @pre Non NULL pointer and valid ID
 * @post Output == OK
 */
void test1_object_set_id();

/**
 * @test Test setting ID with NULL pointer or NO_ID
 * @pre NULL pointer to object or NO_ID
 * @post Output == ERROR
 */
void test2_object_set_id();

/**
 * @test Test getting class ID from valid object
 * @pre Non NULL pointer to object with known class ID
 * @post Output == Expected class ID
 */
void test1_object_get_class_id();

/**
 * @test Test getting class ID from NULL object
 * @pre NULL pointer to object
 * @post Output == NO_ID
 */
void test2_object_get_class_id();

/**
 * @test Test setting class ID with valid input
 * @pre Non NULL pointer and valid class ID
 * @post Output == OK
 */
void test1_object_set_class_id();

/**
 * @test Test setting class ID with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_class_id();

/**
 * @test Test getting role from valid object
 * @pre Non NULL pointer to object with known role
 * @post Output == Expected role
 */
void test1_object_get_role();

/**
 * @test Test getting role from NULL object
 * @pre NULL pointer to object
 * @post Output == NO_ROLE
 */
void test2_object_get_role();

/**
 * @test Test setting role with valid input
 * @pre Non NULL pointer and valid role
 * @post Output == OK
 */
void test1_object_set_role();

/**
 * @test Test setting role with NULL pointer or NO_ROLE
 * @pre NULL pointer to object or NO_ROLE
 * @post Output == ERROR
 */
void test2_object_set_role();

/**
 * @test Test getting use value from valid object
 * @pre Non NULL pointer to object with known use value
 * @post Output == Expected use value
 */
void test1_object_get_use_value();

/**
 * @test Test getting use value from NULL object
 * @pre NULL pointer to object
 * @post Output == -1
 */
void test2_object_get_use_value();

/**
 * @test Test setting use value with valid input
 * @pre Non NULL pointer and valid integer
 * @post Output == OK
 */
void test1_object_set_use_value();

/**
 * @test Test setting use value with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_use_value();

#endif /* OBJECT_TEST_H */