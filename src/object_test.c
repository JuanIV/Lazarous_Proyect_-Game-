/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Alina Datsko
 * @version 1.0
 * @date 06-05-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 20

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if(argc < 2) {
    printf("Running all tests for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if(test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if(all || test == 1) test1_object_create();
  if(all || test == 2) test2_object_create();

  if(all || test == 3) test1_object_destroy();
  if(all || test == 4) test2_object_destroy();

  if(all || test == 5) test1_object_get_id();
  if(all || test == 6) test2_object_get_id();

  if(all || test == 7) test1_object_set_id();
  if(all || test == 8) test2_object_set_id();

  if(all || test == 9) test1_object_get_class_id();
  if(all || test == 10) test2_object_get_class_id();

  if(all || test == 11) test1_object_set_class_id();
  if(all || test == 12) test2_object_set_class_id();

  if(all || test == 13) test1_object_get_role();
  if(all || test == 14) test2_object_get_role();

  if(all || test == 15) test1_object_set_role();
  if(all || test == 16) test2_object_set_role();

  if(all || test == 17) test1_object_get_use_value();
  if(all || test == 18) test2_object_get_use_value();

  if(all || test == 19) test1_object_set_use_value();
  if(all || test == 20) test2_object_set_use_value();

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
  PRINT_TEST_RESULT(object_set_id(obj, 2) == OK);
  PRINT_TEST_RESULT(object_get_id(obj) == 2);
  object_destroy(obj);
}

void test2_object_set_id() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_id(obj, 2) == ERROR);
}

void test1_object_get_class_id() {
  Object *obj = object_create(1);
  object_set_class_id(obj, 10);
  PRINT_TEST_RESULT(object_get_class_id(obj) == 10);
  object_destroy(obj);
}

void test2_object_get_class_id() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_class_id(obj) == NO_ID);
}

void test1_object_set_class_id() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(object_set_class_id(obj, 10) == OK);
  PRINT_TEST_RESULT(object_get_class_id(obj) == 10);
  object_destroy(obj);
}

void test2_object_set_class_id() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_class_id(obj, 10) == ERROR);
}

void test1_object_get_role() {
  Object *obj = object_create(1);
  object_set_role(obj, HOSTILE);
  PRINT_TEST_RESULT(object_get_role(obj) == HOSTILE);
  object_destroy(obj);
}

void test2_object_get_role() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_role(obj) == NO_ROLE);
}

void test1_object_set_role() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(object_set_role(obj, HOSTILE) == OK);
  PRINT_TEST_RESULT(object_get_role(obj) == HOSTILE);
  object_destroy(obj);
}

void test2_object_set_role() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_role(obj, HOSTILE) == ERROR);
}

void test1_object_get_use_value() {
  Object *obj = object_create(1);
  object_set_use_value(obj, 50);
  PRINT_TEST_RESULT(object_get_use_value(obj) == 50);
  object_destroy(obj);
}

void test2_object_get_use_value() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_get_use_value(obj) == -1);
}

void test1_object_set_use_value() {
  Object *obj = object_create(1);
  PRINT_TEST_RESULT(object_set_use_value(obj, 75) == OK);
  PRINT_TEST_RESULT(object_get_use_value(obj) == 75);
  object_destroy(obj);
}

void test2_object_set_use_value() {
  Object *obj = NULL;
  PRINT_TEST_RESULT(object_set_use_value(obj, 75) == ERROR);
}
