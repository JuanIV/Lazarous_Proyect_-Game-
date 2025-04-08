/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Profesores Pprog (Modified by Juan Ibañez)
 * @version 1.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space_test.h"
#include "test.h"

#define MAX_TESTS 29

/**
 * @brief Main function for SPACE unit tests.
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
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();

  if (all || test == 3) test1_space_set_name();
  if (all || test == 4) test2_space_set_name();
  if (all || test == 5) test3_space_set_name();

  if (all || test == 6) test1_space_set_discovered();
  if (all || test == 7) test2_space_set_discovered();

  if (all || test == 8) test1_space_get_discovered();
  if (all || test == 9) test2_space_get_discovered();

  if (all || test == 10) test1_space_set_gdesc_at();
  if (all || test == 11) test2_space_set_gdesc_at();
  if (all || test == 12) test3_space_set_gdesc_at();

  if (all || test == 13) test1_space_get_gdesc_at();
  if (all || test == 14) test2_space_get_gdesc_at();

  if (all || test == 15) test1_space_add_object();
  if (all || test == 16) test2_space_add_object();

  if (all || test == 17) test1_space_remove_object();
  if (all || test == 18) test2_space_remove_object();

  if (all || test == 19) test1_space_find_object();
  if (all || test == 20) test2_space_find_object();
  if (all || test == 21) test3_space_find_object();

  if (all || test == 22) test1_space_get_object_at_pos();
  if (all || test == 23) test2_space_get_object_at_pos();

  if (all || test == 24) test1_space_is_full();
  if (all || test == 25) test2_space_is_full();

  if (all || test == 26) test1_space_set_character();
  if (all || test == 27) test2_space_set_character();

  if (all || test == 28) test1_space_get_character();
  if (all || test == 29) test2_space_get_character();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_set_discovered() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
  space_destroy(s);
}

void test2_space_set_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == ERROR);
}

void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_discovered() {
  Space *s;
  s = space_create(5);
  space_set_discovered(s, TRUE);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test2_space_get_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}

void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_set_gdesc_at() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_gdesc_at(s, "graphic line", 0) == OK);
  space_destroy(s);
}

void test2_space_set_gdesc_at() {
  Space *s = space_create(5);
  space_set_gdesc_at(s, "gdesc", 0);
  PRINT_TEST_RESULT(strncmp(space_get_gdesc_at(s, 0), "gdesc", 5) == 0);
  space_destroy(s);
}

void test3_space_set_gdesc_at() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_gdesc_at(s, "graphic line", SP_GD_HGHT) == ERROR);
  space_destroy(s);
}

void test1_space_get_gdesc_at() {
  Space *s;
  s = space_create(5);
  space_set_gdesc_at(s, "holahola", 0);
  PRINT_TEST_RESULT(strncmp(space_get_gdesc_at(s, 0), "holahola", 8) == 0);
  space_destroy(s);
}

void test2_space_get_gdesc_at() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_gdesc_at(s, 0) == NULL);
}

void test1_space_add_object() {
  Space *s;
  s = space_create(5);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_find_object(s, 10) == TRUE);
  space_destroy(s);
}

void test2_space_add_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}

void test1_space_remove_object() {
  Space *s;
  s = space_create(5);
  space_add_object(s, 10);
  space_remove_object(s, 10);
  PRINT_TEST_RESULT(space_find_object(s, 10) == FALSE);
  space_destroy(s);
}

void test2_space_remove_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR);
}

void test1_space_find_object() {
  Space *s;
  s = space_create(5);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_find_object(s, 10) == TRUE);
  space_destroy(s);
}

void test2_space_find_object() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_find_object(s, 10) == FALSE);
  space_destroy(s);
}

void test3_space_find_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_find_object(s, 10) == FALSE);
}

void test1_space_get_object_at_pos() {
  Space *s;
  s = space_create(5);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_get_object_at_pos(s, 0) == 10);
  space_destroy(s);
}

void test2_space_get_object_at_pos() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_object_at_pos(s, 0) == NO_ID);
}

void test1_space_is_full() {
  int i = 0;
  Space *s;
  s = space_create(5);
  for (i = 0; i < SET_MX_CAP; i++) {
    space_add_object(s, i);
  }
  PRINT_TEST_RESULT(space_is_full(s) == TRUE);
  space_destroy(s);
}

void test2_space_is_full() {
  Space *s;
  s = space_create(5);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_is_full(s) == FALSE);
  space_destroy(s);
}

void test1_space_set_character() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_character(s, 10) == OK);
  space_destroy(s);
}

void test2_space_set_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_character(s, 10) == ERROR);
}

void test1_space_get_character() {
  Space *s;
  s = space_create(5);
  space_set_character(s, 10);
  PRINT_TEST_RESULT(space_get_character(s) == 10);
  space_destroy(s);
}

void test2_space_get_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
}