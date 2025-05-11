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

#define MAX_TESTS 46

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

 
  if (all || test == 1)  test1_space_create();
  if (all || test == 2)  test2_space_create();

  if (all || test == 3)  test1_space_set_name();
  if (all || test == 4)  test2_space_set_name();

  if (all || test == 5)  test1_space_get_name();
  if (all || test == 6)  test2_space_get_name();

  if (all || test == 7)  test1_space_set_discovered();
  if (all || test == 8)  test2_space_set_discovered();

  if (all || test == 9)  test1_space_get_discovered();
  if (all || test == 10) test2_space_get_discovered();

  if (all || test == 11) test1_space_set_gdesc_at();
  if (all || test == 12) test2_space_set_gdesc_at();

  if (all || test == 13) test1_space_get_gdesc_at();
  if (all || test == 14) test2_space_get_gdesc_at();

  if (all || test == 15) test1_space_add_object();
  if (all || test == 16) test2_space_add_object();

  if (all || test == 17) test1_space_remove_object();
  if (all || test == 18) test2_space_remove_object();

  if (all || test == 19) test1_space_find_object();
  if (all || test == 20) test2_space_find_object();

  if (all || test == 21) test1_space_get_object_at_pos();
  if (all || test == 22) test2_space_get_object_at_pos();

  if (all || test == 23) test1_space_objects_is_full();
  if (all || test == 24) test2_space_objects_is_full();

  if (all || test == 25) test1_space_get_num_objects();
  if (all || test == 26) test2_space_get_num_objects();

  if (all || test == 27) test1_space_set_trap();
  if (all || test == 28) test2_space_set_trap();

  if (all || test == 29) test1_space_get_trap();
  if (all || test == 30) test2_space_get_trap();

  if (all || test == 31) test1_space_add_character();
  if (all || test == 32) test2_space_add_character();

  if (all || test == 33) test1_space_remove_character();
  if (all || test == 34) test2_space_remove_character();

  if (all || test == 35) test1_space_find_character();
  if (all || test == 36) test2_space_find_character();

  if (all || test == 37) test1_space_get_character_at_pos();
  if (all || test == 38) test2_space_get_character_at_pos();

  if (all || test == 39) test1_space_characters_is_full();
  if (all || test == 40) test2_space_characters_is_full();

  if (all || test == 41) test1_space_get_num_characters();
  if (all || test == 42) test2_space_get_num_characters();

  if (all || test == 43) test1_space_destroy();
  if (all || test == 44) test2_space_destroy();

  if (all || test == 45) test1_space_get_id();
  if (all || test == 46) test2_space_get_id();


  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_space_create() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(sp != NULL);
  space_destroy(sp);
}

void test2_space_create() {
  Space *sp = space_create(NO_ID);
  PRINT_TEST_RESULT(sp == NULL);
}

void test1_space_destroy() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_destroy(sp) == OK);
}

void test2_space_destroy() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_destroy(sp) == ERROR);
}

void test1_space_get_id() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_get_id(sp) == 1);
  space_destroy(sp);
}

void test2_space_get_id() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_id(sp) == NO_ID);
}

void test1_space_set_name() {
  Space *sp = space_create(1);
  space_set_name(sp, "Nombre");
  PRINT_TEST_RESULT(strcmp(space_get_name(sp), "Nombre") == 0);
  space_destroy(sp);
}

void test2_space_set_name() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_set_name(sp, "Nombre") == ERROR);
}

void test1_space_get_name() {
  Space *sp = space_create(1);
  space_set_name(sp, "Nombre");
  PRINT_TEST_RESULT(strcmp(space_get_name(sp), "Nombre") == 0);
  space_destroy(sp);
}

void test2_space_get_name() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_name(sp) == NULL);
}

void test1_space_set_gdesc_at() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc_at(sp, "Linea", 0) == OK);
  space_destroy(sp);
}

void test2_space_set_gdesc_at() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_set_gdesc_at(sp, "Linea", 0) == ERROR);
}

void test1_space_get_gdesc_at() {
  Space *sp = space_create(1);
  space_set_gdesc_at(sp, "holahola", 0);
  PRINT_TEST_RESULT(strncmp(space_get_gdesc_at(sp, 0), "holahola", 8) == 0);
  space_destroy(sp);
}

void test2_space_get_gdesc_at() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_gdesc_at(sp, 0) == NULL);
}

void test1_space_set_discovered() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_set_discovered(sp, TRUE) == OK);
  space_destroy(sp);
}

void test2_space_set_discovered() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_set_discovered(sp, TRUE) == ERROR);
}

void test1_space_get_discovered() {
  Space *sp = space_create(1);
  Bool val = FALSE;
  space_set_discovered(sp, TRUE);
  space_get_discovered(sp, &val);
  PRINT_TEST_RESULT(val == TRUE);
  space_destroy(sp);
}

void test2_space_get_discovered() {
  Bool val;
  PRINT_TEST_RESULT(space_get_discovered(NULL, &val) == ERROR);
}

void test1_space_add_object() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_add_object(sp, 10) == OK);
  space_destroy(sp);
}

void test2_space_add_object() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_add_object(sp, 10) == ERROR);
}

void test1_space_remove_object() {
  Space *sp = space_create(1);
  space_add_object(sp, 20);
  PRINT_TEST_RESULT(space_remove_object(sp, 20) == OK);
  space_destroy(sp);
}

void test2_space_remove_object() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_remove_object(sp, 20) == ERROR);
}

void test1_space_find_object() {
  Space *sp = space_create(1);
  space_add_object(sp, 30);
  PRINT_TEST_RESULT(space_find_object(sp, 30) == TRUE);
  space_destroy(sp);
}

void test2_space_find_object() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_find_object(sp, 30) == FALSE);
}

void test1_space_get_object_at_pos() {
  Space *sp = space_create(1);
  space_add_object(sp, 40);
  PRINT_TEST_RESULT(space_get_object_at_pos(sp, 0) == 40);
  space_destroy(sp);
}

void test2_space_get_object_at_pos() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_object_at_pos(sp, 0) == NO_ID);
}

void test1_space_objects_is_full() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_objects_is_full(sp) == FALSE);
  space_destroy(sp);
}

void test2_space_objects_is_full() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_objects_is_full(sp) == TRUE);
}

void test1_space_get_num_objects() {
  Space *sp = space_create(1);
  space_add_object(sp, 50);
  space_add_object(sp, 51);
  PRINT_TEST_RESULT(space_get_num_objects(sp) == 2);
  space_destroy(sp);
}

void test2_space_get_num_objects() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_num_objects(sp) == 0);
}

void test1_space_set_trap() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_set_trap(sp, 77) == OK);
  space_destroy(sp);
}

void test2_space_set_trap() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_set_trap(sp, 77) == ERROR);
}

void test1_space_get_trap() {
  Space *sp = space_create(1);
  Id trap;
  space_set_trap(sp, 88);
  PRINT_TEST_RESULT(space_get_trap(sp, &trap) == OK && trap == 88);
  space_destroy(sp);
}

void test2_space_get_trap() {
  Space *sp = NULL;
  Id trap;
  PRINT_TEST_RESULT(space_get_trap(sp, &trap) == ERROR);
}

void test1_space_add_character() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_add_character(sp, 10) == OK);
  space_destroy(sp);
}

void test2_space_add_character() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_add_character(sp, 10) == ERROR);
}

void test1_space_remove_character() {
  Space *sp = space_create(1);
  space_add_character(sp, 20);
  PRINT_TEST_RESULT(space_remove_character(sp, 20) == OK);
  space_destroy(sp);
}

void test2_space_remove_character() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_remove_character(sp, 20) == ERROR);
}

void test1_space_find_character() {
  Space *sp = space_create(1);
  space_add_character(sp, 30);
  PRINT_TEST_RESULT(space_find_character(sp, 30) == TRUE);
  space_destroy(sp);
}

void test2_space_find_character() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_find_character(sp, 30) == FALSE);
}

void test1_space_get_character_at_pos() {
  Space *sp = space_create(1);
  space_add_character(sp, 40);
  PRINT_TEST_RESULT(space_get_character_at_pos(sp, 0) == 40);
  space_destroy(sp);
}

void test2_space_get_character_at_pos() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_character_at_pos(sp, 0) == NO_ID);
}

void test1_space_characters_is_full() {
  Space *sp = space_create(1);
  PRINT_TEST_RESULT(space_characters_is_full(sp) == FALSE);
  space_destroy(sp);
}

void test2_space_characters_is_full() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_characters_is_full(sp) == TRUE);
}

void test1_space_get_num_characters() {
  Space *sp = space_create(1);
  space_add_character(sp, 50);
  PRINT_TEST_RESULT(space_get_num_characters(sp) == 1);
  space_destroy(sp);
}

void test2_space_get_num_characters() {
  Space *sp = NULL;
  PRINT_TEST_RESULT(space_get_num_characters(sp) == -1);
}

