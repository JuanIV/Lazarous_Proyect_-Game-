/**
 * @brief It implements the tests for the inventory module
 * 
 * @file inventory_test.c
 * @author Juan Ibáñez
 * @version 0.1
 * @date 2025-03-24
 * @copyright Copyright GNU Public License
 */

#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 26

/**
 * @brief Main function for INVENTORY unit tests.
 *
 * You may execute ALL or a SINGLE test
 *
 * 1.- No parameter -> ALL test are executed
 *
 * 2.- A number means a particular test (the one identified by that number)
 *
 */

int main(int argc, char **argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Inventory:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();

  if (all || test == 3) test1_inventory_destroy();
  if (all || test == 4) test2_inventory_destroy();

  if (all || test == 5) test1_inventory_add_object();
  if (all || test == 6) test2_inventory_add_object();
  if (all || test == 7) test3_inventory_add_object();

  if (all || test == 8) test1_inventory_remove_object();
  if (all || test == 9) test2_inventory_remove_object();
  if (all || test == 10) test3_inventory_remove_object();

  if (all || test == 11) test1_inventory_get_objects();
  if (all || test == 12) test2_inventory_get_objects();

  if (all || test == 13) test1_inventory_get_max_objects();
  if (all || test == 14) test2_inventory_get_max_objects();

  if (all || test == 15) test1_inventory_set_max_objects();
  if (all || test == 16) test2_inventory_set_max_objects();

  if (all || test == 17) test1_inventory_get_num_objects();
  if (all || test == 18) test2_inventory_get_num_objects();

  if (all || test == 19) test1_inventory_find_object();
  if (all || test == 20) test2_inventory_find_object();
  if (all || test == 21) test3_inventory_find_object();

  if (all || test == 22) test1_inventory_is_full();
  if (all || test == 23) test2_inventory_is_full();
  if (all || test == 24) test3_inventory_is_full();

  if (all || test == 25) test1_inventory_get_object_at_pos();
  if (all || test == 26) test2_inventory_get_object_at_pos();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_inventory_create() {
  Inventory *inv = inventory_create();
  PRINT_TEST_RESULT(inv != NULL);
  inventory_destroy(inv);
}

void test2_inventory_create() {
  Inventory *inv = inventory_create();
  PRINT_TEST_RESULT(inventory_get_num_objects(inv) == 0);
  inventory_destroy(inv);
}

void test1_inventory_destroy() {
  Inventory *inv = inventory_create();
  PRINT_TEST_RESULT(inventory_destroy(inv) == OK);
}

void test2_inventory_destroy() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_destroy(inv) == ERROR);
}

void test1_inventory_add_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  PRINT_TEST_RESULT(inventory_add_object(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_add_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 1);
  inventory_add_object(inv, 1);
  /* Inventory is full*/ 
  PRINT_TEST_RESULT(inventory_add_object(inv, 2) == ERROR);
  
  inventory_destroy(inv);
}

void test3_inventory_add_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_find_object(inv, 1) == TRUE);
  inventory_destroy(inv);
}

void test1_inventory_remove_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_remove_object(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_remove_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  inventory_remove_object(inv, 1);
  PRINT_TEST_RESULT(inventory_find_object(inv, 1) == FALSE);
  inventory_destroy(inv);
}

void test3_inventory_remove_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  PRINT_TEST_RESULT(inventory_remove_object(inv, 1) == ERROR);
  inventory_destroy(inv);
}

void test1_inventory_get_objects() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_get_objects(inv) != NULL);
  inventory_destroy(inv);
}

void test2_inventory_get_objects() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_objects(inv) == NULL);
}

void test1_inventory_get_max_objects() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  PRINT_TEST_RESULT(inventory_get_max_objects(inv) == 5);
  inventory_destroy(inv);
}

void test2_inventory_get_max_objects() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_max_objects(inv) == -1);
}

void test1_inventory_set_max_objects() {
  Inventory *inv = inventory_create();
  PRINT_TEST_RESULT(inventory_set_max_objects(inv, 5) == OK);
  inventory_destroy(inv);
}

void test2_inventory_set_max_objects() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_set_max_objects(inv, 5) == ERROR);
}

void test1_inventory_get_num_objects() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_get_num_objects(inv) == 1);
  inventory_destroy(inv);
}

void test2_inventory_get_num_objects() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_num_objects(inv) == -1);
}

void test1_inventory_find_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_find_object(inv, 1) == TRUE);
  inventory_destroy(inv);
}

void test2_inventory_find_object() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  PRINT_TEST_RESULT(inventory_find_object(inv, 1) == FALSE);
  inventory_destroy(inv);
}

void test3_inventory_find_object() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_find_object(inv, 1) == FALSE);
}

void test1_inventory_is_full() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 1);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_is_full(inv) == TRUE);
  inventory_destroy(inv);
}

void test2_inventory_is_full() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  PRINT_TEST_RESULT(inventory_is_full(inv) == FALSE);
  inventory_destroy(inv);
}

void test3_inventory_is_full() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_is_full(inv) == TRUE);
}

void test1_inventory_get_object_at_pos() {
  Inventory *inv = inventory_create();
  inventory_set_max_objects(inv, 5);
  inventory_add_object(inv, 1);
  PRINT_TEST_RESULT(inventory_get_object_at_pos(inv, 0) == 1);
  inventory_destroy(inv);
}

void test2_inventory_get_object_at_pos() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_object_at_pos(inv, 0) == NO_ID);
}
