/**
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Tiago Oselka
 * @version 0.0
 * @date 24-02-2025
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre None
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test set creation
 * @pre None
 * @post Number of ids in the set is 0
 */
void test2_set_create();

/**
 * @test Test set destruction
 * @pre Non NULL pointer to set
 * @post Output == OK
 */
void test1_set_destroy();

/**
 * @test Test set destruction
 * @pre NULL pointer to set
 * @post Output == ERROR
 */
void test2_set_destroy();

/**
 * @test Test adding an id to the set
 * @pre Non NULL pointer to set and valid id
 * @post Output == OK
 */
void test1_set_add();

/**
 * @test Test adding an id to the set
 * @pre Set is full
 * @post Output == ERROR
 */
void test2_set_add();

/**
 * @test Test adding an id to the set
 * @pre Non NULL pointer to set and valid id
 * @post Id is added to the set
 */
void test3_set_add()   ;

/**
 * @test Test removing an id from the set
 * @pre Non NULL pointer to set and valid id
 * @post Output == OK
 */
void test1_set_remove()  ;

/**
 * @test Test removing an id from the set
 * @pre Non NULL pointer to set and valid id
 * @post Id is removed from the set
 */
void test2_set_remove() ;

/**
 * @test Test getting an id at a specific position
 * @pre Non NULL pointer to set and valid position
 * @post Output == Expected id
 */
void test1_set_get_id_at_pos();

/**
 * @test Test getting an id at a specific position
 * @pre Invalid position (negative)
 * @post Output == NO_ID
 */
void test2_set_get_id_at_pos() ;

/**
 * @test Test getting an id at a specific position
 * @pre NULL pointer to set
 * @post Output == NO_ID
 */
void test3_set_get_id_at_pos() ;

/**
 * @test Test finding an id in the set
 * @pre Non NULL pointer to set and valid id
 * @post Output == TRUE
 */
void test1_set_find() ;

/**
 * @test Test finding an id in the set
 * @pre Id not in the set
 * @post Output == FALSE
 */
void test2_set_find() ;

/**
 * @test Test finding an id in the set
 * @pre NULL pointer to set
 * @post Output == FALSE
 */
void test3_set_find() ;

/**
 * @test Test if the set is full
 * @pre Set is full
 * @post Output == TRUE
 */
void test1_set_is_full() ;

/**
 * @test Test if the set is full
 * @pre Set is not full
 * @post Output == FALSE
 */
void test2_set_is_full() ;

/**
 * @test Test if the set is full
 * @pre NULL pointer to set
 * @post Output == TRUE
 */
void test3_set_is_full() ;

/**
 * @test Test getting the number of ids in the set
 * @pre Non NULL pointer to set
 * @post Output == Expected number of ids
 */
void test1_set_get_num_ids() ;

/**
 * @test Test getting the number of ids in the set
 * @pre NULL pointer to set
 * @post Output == -1
 */
void test2_set_get_num_ids() ;


#endif