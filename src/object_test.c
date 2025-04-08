/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Alina Datsko
 * @version 0.0
 * @date 04-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 16

/**
 * @brief Main function for OBJECT unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();

  if (all || test == 3) test1_object_destroy();
  if (all || test == 4) test2_object_destroy();

  if (all || test == 5) test1_object_get_id();
  if (all || test == 6) test2_object_get_id();

  if (all || test == 7) test1_object_set_id();
  if (all || test == 8) test2_object_set_id();

  if (all || test == 9) test1_object_get_name();
  if (all || test == 10) test2_object_get_name();

  if (all || test == 11) test1_object_set_name();
  if (all || test == 12) test2_object_set_name();

  if (all || test == 13) test1_object_get_desc();
  if (all || test == 14) test2_object_get_desc();

  if (all || test == 15) test1_object_set_desc();
  if (all || test == 16) test2_object_set_desc();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_object_create() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(obj != NULL);
  object_destroy(obj);
}

void test2_object_create() {
  Object *obj = object_create(NO_ID);
  PRINT_TEST_RESULT(obj == NULL);
}

void test1_object_destroy() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(object_destroy(obj) == OK);
}

void test2_object_destroy() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_destroy(obj) == ERROR);
}

void test1_object_get_id() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(object_get_id(obj) == 1);
  object_destroy(obj);
}

void test2_object_get_id() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_id(obj) == NO_ID);
}

void test1_object_set_id() {
  Object *obj = object_create(1);
  object_set_id(obj, 2);
  PRINT_TEST_RESULT(object_get_id(obj) == 2);
  object_destroy(obj);
}

void test2_object_set_id() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_id(obj, 2) == ERROR);
}

void test1_object_get_name() {
  Object *obj = object_create(1);
  object_set_name(obj, "Sword");
  PRINT_TEST_RESULT(strcmp(object_get_name(obj), "Sword") == 0);
  object_destroy(obj);
}

void test2_object_get_name() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_name(obj) == NULL);
}

void test1_object_set_name() {
  Object *obj = object_create(1);
  object_set_name(obj, "Sword");
  PRINT_TEST_RESULT(strcmp(object_get_name(obj), "Sword") == 0);
  object_destroy(obj);
}

void test2_object_set_name() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_name(obj, "Sword") == ERROR);
}

void test1_object_get_desc() {
  Object *obj = object_create(1);
  object_set_desc(obj, "A shiny sword.");
  PRINT_TEST_RESULT(strcmp(object_get_desc(obj), "A shiny sword.") == 0);
  object_destroy(obj);
}

void test2_object_get_desc() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_desc(obj) == NULL);
}

void test1_object_set_desc() {
  Object *obj = object_create(1);
  object_set_desc(obj, "A shiny sword.");
  PRINT_TEST_RESULT(strcmp(object_get_desc(obj), "A shiny sword.") == 0);
  object_destroy(obj);
}

void test2_object_set_desc() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_desc(obj, "A shiny sword.") == ERROR);
}


