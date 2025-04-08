/**
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Lucas Blanco Rodríguez
 * @version 0.0
 * @date 24-03-2025
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre None
 * @post Non NULL pointer to link is returned
 */
void test1_link_create();

/**
 * @test Test link creation with NO_ID
 * @pre None
 * @post Link id is set to NO_ID
 */
void test2_link_create();

/**
 * @test Test link destruction
 * @pre Non NULL pointer to link
 * @post Returns OK
 */
void test1_link_destroy();

/**
 * @test Test link destruction with NULL pointer
 * @pre NULL pointer
 * @post Returns ERROR
 */
void test2_link_destroy();

/**
 * @test Test getting link id
 * @pre Non NULL pointer to link
 * @post Output equals expected id
 */
void test1_link_get_id();

/**
 * @test Test getting link id with NO_ID
 * @pre Non NULL pointer to link
 * @post Output equals NO_ID
 */
void test2_link_get_id();

/**
 * @test Test setting link name
 * @pre Non NULL pointer to link
 * @post Name is properly set
 */
void test1_link_set_name();

/**
 * @test Test setting link name with NULL parameter
 * @pre Non NULL pointer to link
 * @post Returns ERROR
 */
void test2_link_set_name();

/**
 * @test Test getting link name
 * @pre Non NULL pointer to link
 * @post Output equals expected name
 */
void test1_link_get_name();

/**
 * @test Test setting link origin
 * @pre Non NULL pointer to link
 * @post Origin is properly set
 */
void test1_link_set_origin();

/**
 * @test Test setting link origin to NO_ID
 * @pre Non NULL pointer to link
 * @post Origin is set to NO_ID
 */
void test2_link_set_origin();

/**
 * @test Test getting link origin
 * @pre Non NULL pointer to link
 * @post Output equals expected origin
 */
void test1_link_get_orig();

/**
 * @test Test setting link destination
 * @pre Non NULL pointer to link
 * @post Destination is properly set
 */
void test1_link_set_destination();

/**
 * @test Test setting link destination to NO_ID
 * @pre Non NULL pointer to link
 * @post Destination is set to NO_ID
 */
void test2_link_set_destination();

/**
 * @test Test getting link destination
 * @pre Non NULL pointer to link
 * @post Output equals expected destination
 */
void test1_link_get_dest();

/**
 * @test Test setting link direction
 * @pre Non NULL pointer to link
 * @post Direction is properly set
 */
void test1_link_set_direction();

/**
 * @test Test setting link direction to UNK_DIR
 * @pre Non NULL pointer to link
 * @post Direction is set to UNK_DIR
 */
void test2_link_set_direction();

/**
 * @test Test getting link direction
 * @pre Non NULL pointer to link
 * @post Output equals expected direction
 */
void test1_link_get_direction();

/**
 * @test Test setting link open status
 * @pre Non NULL pointer to link
 * @post Open state is properly set to TRUE
 */
void test1_link_set_open();

/**
 * @test Test setting link open status to FALSE
 * @pre Non NULL pointer to link
 * @post Open state is properly set to FALSE
 */
void test2_link_set_open();

/**
 * @test Test getting link open status
 * @pre Non NULL pointer to link
 * @post Output equals expected open state
 */
void test1_link_get_open();


#endif
 
 