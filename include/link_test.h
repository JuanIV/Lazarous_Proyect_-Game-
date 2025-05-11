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
 * @test Test link creation with valid ID
 * @pre Valid ID passed to link_create
 * @post Non NULL pointer to link is returned
 */
void test1_link_create();

/**
 * @test Test link creation with invalid ID
 * @pre NO_ID passed to link_create
 * @post NULL pointer is returned
 */
void test2_link_create();

/**
 * @test Test destruction of a valid link
 * @pre A valid link has been created
 * @post link_destroy returns OK
 */
void test1_link_destroy();

/**
 * @test Test destruction of a NULL link
 * @pre NULL pointer passed to link_destroy
 * @post link_destroy returns ERROR
 */
void test2_link_destroy();

/**
 * @test Test getting the ID from a valid link
 * @pre A valid link with a known ID
 * @post The correct ID is returned
 */
void test1_link_get_id();

/**
 * @test Test getting the ID from a NULL link
 * @pre NULL pointer passed to link_get_id
 * @post NO_ID is returned
 */
void test2_link_get_id();

/**
 * @test Test getting the name of a valid link
 * @pre A valid link with name set
 * @post Non NULL name is returned
 */
void test1_link_get_name();

/**
 * @test Test getting the name of a NULL link
 * @pre NULL pointer passed to link_get_name
 * @post NULL is returned
 */
void test2_link_get_name();

/**
 * @test Test setting the name of a link
 * @pre Valid link and name passed
 * @post The name is correctly stored
 */
void test1_link_set_name();

/**
 * @test Test setting a NULL name
 * @pre Valid link but NULL name passed
 * @post link_set_name returns ERROR
 */
void test2_link_set_name();

/**
 * @test Test getting the origin ID from a valid link
 * @pre A valid link with origin set
 * @post The correct origin ID is returned
 */
void test1_link_get_orig();

/**
 * @test Test getting the origin ID from a NULL link
 * @pre NULL link
 * @post NO_ID is returned
 */
void test2_link_get_orig();

/**
 * @test Test setting the origin ID
 * @pre A valid link and origin ID
 * @post Origin ID is set correctly
 */
void test1_link_set_orig();

/**
 * @test Test setting origin ID in NULL link
 * @pre NULL link passed
 * @post link_set_orig returns ERROR
 */
void test2_link_set_orig();

/**
 * @test Test getting destination ID from a valid link
 * @pre A valid link with destination set
 * @post Correct destination ID is returned
 */
void test1_link_get_dest();

/**
 * @test Test getting destination ID from NULL link
 * @pre NULL link
 * @post NO_ID is returned
 */
void test2_link_get_dest();

/**
 * @test Test setting the destination ID
 * @pre Valid link and ID
 * @post Destination ID is set and returned correctly
 */
void test1_link_set_dest();

/**
 * @test Test setting destination ID in NULL link
 * @pre NULL link
 * @post link_set_dest returns ERROR
 */
void test2_link_set_dest();

/**
 * @test Test getting direction of a valid link
 * @pre Direction was set
 * @post Correct direction is returned
 */
void test1_link_get_direction();

/**
 * @test Test getting direction of a NULL link
 * @pre NULL link
 * @post UNK_DIR is returned
 */
void test2_link_get_direction();

/**
 * @test Test setting the direction
 * @pre Valid link and direction
 * @post Direction is set correctly
 */
void test1_link_set_direction();

/**
 * @test Test setting direction in NULL link
 * @pre NULL link
 * @post link_set_direction returns ERROR
 */
void test2_link_set_direction();

/**
 * @test Test getting 'open' status
 * @pre Valid link with known open status
 * @post link_get_open returns OK and correct value
 */
void test1_link_get_open();

/**
 * @test Test getting 'open' from NULL link
 * @pre NULL link
 * @post link_get_open returns ERROR
 */
void test2_link_get_open();

/**
 * @test Test setting 'open' status
 * @pre Valid link and value
 * @post Status is set correctly
 */
void test1_link_set_open();

/**
 * @test Test setting 'open' in NULL link
 * @pre NULL link
 * @post link_set_open returns ERROR
 */
void test2_link_set_open();

/**
 * @test Test getting 'locked' status
 * @pre Valid link with locked status set
 * @post Correct status and OK returned
 */
void test1_link_get_locked();

/**
 * @test Test getting 'locked' from NULL link
 * @pre NULL link
 * @post link_get_locked returns ERROR
 */
void test2_link_get_locked();

/**
 * @test Test setting 'locked' status
 * @pre Valid link and status
 * @post Status is updated correctly
 */
void test1_link_set_locked();

/**
 * @test Test setting 'locked' in NULL link
 * @pre NULL link
 * @post link_set_locked returns ERROR
 */
void test2_link_set_locked();

/**
 * @test Test getting 'connected' status
 * @pre Valid link with known connection state
 * @post Correct status and OK returned
 */
void test1_link_get_connected();

/**
 * @test Test getting 'connected' from NULL link
 * @pre NULL link
 * @post link_get_connected returns ERROR
 */
void test2_link_get_connected();

/**
 * @test Test setting 'connected' status
 * @pre Valid link and value
 * @post link_set_connected returns OK
 */
void test1_link_set_connected();

/**
 * @test Test setting 'connected' in NULL link
 * @pre NULL link
 * @post link_set_connected returns ERROR
 */
void test2_link_set_connected();

/**
 * @test Test getting open role
 * @pre Valid link with role set
 * @post Correct role is returned
 */
void test1_link_get_open_role();

/**
 * @test Test getting open role from NULL link
 * @pre NULL link
 * @post NO_ROLE is returned
 */
void test2_link_get_open_role();

/**
 * @test Test setting open role
 * @pre Valid link and role
 * @post Role is correctly stored
 */
void test1_link_set_open_role();

/**
 * @test Test setting open role in NULL link
 * @pre NULL link
 * @post link_set_open_role returns ERROR
 */
void test2_link_set_open_role();

/**
 * @test Test getting use role
 * @pre Valid link with use role set
 * @post Correct role is returned
 */
void test1_link_get_use_role();

/**
 * @test Test getting use role from NULL link
 * @pre NULL link
 * @post NO_ROLE is returned
 */
void test2_link_get_use_role();

/**
 * @test Test setting use role
 * @pre Valid link and role
 * @post Role is correctly set
 */
void test1_link_set_use_role();

/**
 * @test Test setting use role in NULL link
 * @pre NULL link
 * @post link_set_use_role returns ERROR
 */
void test2_link_set_use_role();

#endif