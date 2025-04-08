/**
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Juan Ibáñez
 * @version 1.0
 * @date 20-03-2025
 * @copyright GNU Public License
*/

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @pre None
 * @post Non NULL pointer to inventory
 */
void test1_inventory_create();

/**
 * @test Test inventory creation
 * @pre None
 * @post Number of objects in the inventory is 0
 */
void test2_inventory_create();

/**
 * @test Test inventory destruction
 * @pre Non NULL pointer to inventory
 * @post Output == OK
 */
void test1_inventory_destroy();

/**
 * @test Test inventory destruction
 * @pre NULL pointer to inventory
 * @post Output == ERROR
 */
void test2_inventory_destroy();

/**
 * @test Test adding an object to the inventory
 * @pre Non NULL pointer to inventory and valid id
 * @post Output == OK
 */
void test1_inventory_add_object();

/**
 * @test Test adding an object to the inventory
 * @pre Inventory is full
 * @post Output == ERROR
 */
void test2_inventory_add_object();

/**
 * @test Test adding an object to the inventory
 * @pre Non NULL pointer to inventory and valid id
 * @post Object is added to the inventory
 */
void test3_inventory_add_object();

/**
 * @test Test removing an object from the inventory
 * @pre Non NULL pointer to inventory and valid id
 * @post Output == OK
 */
void test1_inventory_remove_object();

/**
 * @test Test removing an object from the inventory
 * @pre Non NULL pointer to inventory and valid id
 * @post Object is removed from the inventory
 */
void test2_inventory_remove_object();

/**
 * @test Test removing an object from the inventory
 * @pre Object not in inventory
 * @post Output == ERROR
 */
void test3_inventory_remove_object();

/**
 * @test Test getting objects from the inventory
 * @pre Non NULL pointer to inventory
 * @post Output != NULL
 */
void test1_inventory_get_objects();

/**
 * @test Test getting objects from the inventory
 * @pre NULL pointer to inventory
 * @post Output == NULL
 */
void test2_inventory_get_objects();

/**
 * @test Test getting max objects from the inventory
 * @pre Non NULL pointer to inventory with max objects set
 * @post Output == expected max objects
 */
void test1_inventory_get_max_objects();

/**
 * @test Test getting max objects from the inventory
 * @pre NULL pointer to inventory
 * @post Output == -1
 */
void test2_inventory_get_max_objects();

/**
 * @test Test setting max objects for the inventory
 * @pre Non NULL pointer to inventory
 * @post Output == OK
 */
void test1_inventory_set_max_objects();

/**
 * @test Test setting max objects for the inventory
 * @pre NULL pointer to inventory
 * @post Output == ERROR
 */
void test2_inventory_set_max_objects();

/**
 * @test Test getting number of objects in inventory
 * @pre Non NULL pointer to inventory with objects
 * @post Output == expected number of objects
 */
void test1_inventory_get_num_objects();

/**
 * @test Test getting number of objects in inventory
 * @pre NULL pointer to inventory
 * @post Output == -1
 */
void test2_inventory_get_num_objects();

/**
 * @test Test finding an object in the inventory
 * @pre Non NULL pointer to inventory and object exists
 * @post Output == TRUE
 */
void test1_inventory_find_object();

/**
 * @test Test finding an object in the inventory
 * @pre Object not in inventory
 * @post Output == FALSE
 */
void test2_inventory_find_object();

/**
 * @test Test finding an object in the inventory
 * @pre NULL pointer to inventory
 * @post Output == FALSE
 */
void test3_inventory_find_object();

/**
 * @test Test if the inventory is full
 * @pre Inventory is full
 * @post Output == TRUE
 */
void test1_inventory_is_full();

/**
 * @test Test if the inventory is full
 * @pre Inventory is not full
 * @post Output == FALSE
 */
void test2_inventory_is_full();

/**
 * @test Test if the inventory is full
 * @pre NULL pointer to inventory
 * @post Output == TRUE
 */
void test3_inventory_is_full();

#endif /* INVENTORY_TEST_H */