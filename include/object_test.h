/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Alina Datsko
 * @version 2.0
 * @date 04-04-2025 / 
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre None
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation with invalid ID
 * @pre Invalid ID
 * @post Output == NULL
 */
void test2_object_create();

/**
 * @test Test object destruction
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
 * @test Test getting object ID
 * @pre Non NULL pointer to object
 * @post Output == Expected ID
 */
void test1_object_get_id();

/**
 * @test Test getting object ID with NULL pointer
 * @pre NULL pointer to object
 * @post Output == NO_ID
 */
void test2_object_get_id();

/**
 * @test Test setting object ID
 * @pre Non NULL pointer to object and valid ID
 * @post Output == OK
 */
void test1_object_set_id();

/**
 * @test Test setting object ID with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_id();

/**
 * @test Test getting object name
 * @pre Non NULL pointer to object with valid name
 * @post Output == Expected name
 */
void test1_object_get_name();

/**
 * @test Test getting object name with NULL pointer
 * @pre NULL pointer to object
 * @post Output == NULL
 */
void test2_object_get_name();

/**
 * @test Test setting object name
 * @pre Non NULL pointer to object and valid name
 * @post Output == OK
 */
void test1_object_set_name();

/**
 * @test Test setting object name with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_name();

/**
 * @test Test getting object description
 * @pre Non NULL pointer to object with valid description
 * @post Output == Expected description
 */
void test1_object_get_desc();

/**
 * @test Test getting object description with NULL pointer
 * @pre NULL pointer to object
 * @post Output == NULL
 */
void test2_object_get_desc();

/**
 * @test Test setting object description
 * @pre Non NULL pointer to object and valid description
 * @post Output == OK
 */
void test1_object_set_desc();

/**
 * @test Test getting object health
 * @pre Non NULL pointer to object
 * @post Output == Expected health
 */
void test1_object_get_health();

/**
 * @test Test getting object health with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_get_health();

/**
 * @test Test setting object health
 * @pre Non NULL pointer to object 
 * @post Output == OK
 */
void test1_object_set_health();

/**
 * @test Test setting object health with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_health();

/** 
 * @test Test getting object dependency
 * @pre Non NULL pointer to object
 * @post Output == Expected dependency
 */
void test1_object_get_dependency();

/**
 * @test Test getting object dependency with NULL pointer
 * @pre NULL pointer to object
 * @post Output == NO_ID
 */
void test2_object_get_dependency();

/**
 * @test Test setting object dependency
 * @pre Non NULL pointer to object 
 * @post Output == OK
 */
void test1_object_set_dependency();

/**
 * @test Test setting object dependency with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_dependency();

/**
 * @test Test getting object open property
 * @pre Non NULL pointer to object
 * @post Output == Expected open property
 */
void test1_object_get_open();

/**
 * @test Test getting object open property with NULL pointer
 * @pre NULL pointer to object
 * @post Output == NO_ID
 */
void test2_object_get_open();

/**
 * @test Test setting object open property
 * @pre Non NULL pointer to object 
 * @post Output == OK
 */
void test1_object_set_open();

/**
 * @test Test setting object open property
 * @pre NULL pointer to object 
 * @post Output == ERROR
 */
void test2_object_set_open();

/**
 * @test Test getting object movable
 * @pre Non NULL pointer to object
 * @post Output = OK
 */
void test1_object_get_movable();

/** 
 * @test Test getting object movable
 * @pre NULL pointer to object
 * @post Output = OK
 */
void test2_object_get_movable();

/**
 * @test Test setting object movable property
 * @pre Non NULL pointer to object 
 * @post Output == OK
 */
void test1_object_set_movable();

/**
 * @test Test setting object movable property
 * @pre NULL pointer to object 
 * @post Output == ERROR
 */
void test2_object_set_movable();

/**
 * @test Test getting object luck
 * @pre Non NULL pointer to object
 * @post Output = OK
 */
void test1_object_get_luck();

/** 
 * @test Test getting object luck
 * @pre NULL pointer to object
 * @post Output = OK
 */
void test2_object_get_luck();

/**
 * @test Test setting object luck  property
 * @pre Non NULL pointer to object 
 * @post Output == OK
 */
void test1_object_set_luck();

/**
 * @test Test setting object luck property
 * @pre NULL pointer to object 
 * @post Output == ERROR
 */
void test2_object_set_luck();

/**
 * @test Test setting object description with NULL pointer
 * @pre NULL pointer to object
 * @post Output == ERROR
 */
void test2_object_set_desc();

#endif