/**
 * @brief It tests class module
 *
 * @file class_test.c
 * @author Alina Datsko
 * @version 1.0
 * @date 05-05-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "class.h"
#include "class_test.h"
#include "test.h"

#define MAX_TESTS 42

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if(argc < 2) {
    printf("Running all tests for module Class:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if(test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if(all || test == 1) test1_class_create();
  if(all || test == 2) test2_class_create();

  if(all || test == 3) test1_class_destroy();
  if(all || test == 4) test2_class_destroy();

  if(all || test == 5) test1_class_get_id();
  if(all || test == 6) test2_class_get_id();

  if(all || test == 7) test1_class_set_id();
  if(all || test == 8) test2_class_set_id();

  if(all || test == 9) test1_class_get_tag();
  if(all || test == 10) test2_class_get_tag();

  if(all || test == 11) test1_class_set_tag();
  if(all || test == 12) test2_class_set_tag();

  if(all || test == 13) test1_class_get_name();
  if(all || test == 14) test2_class_get_name();

  if(all || test == 15) test1_class_set_name();
  if(all || test == 16) test2_class_set_name();

  if(all || test == 17) test1_class_get_desc();
  if(all || test == 18) test2_class_get_desc();

  if(all || test == 19) test1_class_set_desc();
  if(all || test == 20) test2_class_set_desc();

  if(all || test == 21) test1_class_get_closeup_at_pos();
  if(all || test == 22) test2_class_get_closeup_at_pos();

  if(all || test == 23) test1_class_get_closeup();
  if(all || test == 24) test2_class_get_closeup();

  if(all || test == 25) test1_class_set_closeup_at_pos();
  if(all || test == 26) test2_class_set_closeup_at_pos();

  if(all || test == 27) test1_class_get_movable();
  if(all || test == 28) test2_class_get_movable();

  if(all || test == 29) test1_class_set_movable();
  if(all || test == 30) test2_class_set_movable();

  if(all || test == 31) test1_class_get_dependency();
  if(all || test == 32) test2_class_get_dependency();

  if(all || test == 33) test1_class_set_dependency();
  if(all || test == 34) test2_class_set_dependency();

  if(all || test == 35) test1_class_get_open();
  if(all || test == 36) test2_class_get_open();

  if(all || test == 37) test1_class_set_open();
  if(all || test == 38) test2_class_set_open();

  if(all || test == 39) test1_class_get_luck();
  if(all || test == 40) test2_class_get_luck();

  if(all || test == 41) test1_class_set_luck();
  if(all || test == 42) test2_class_set_luck();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_class_create() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(cl != NULL);
  class_destroy(cl);
}

void test2_class_create() {
  Class *cl = class_create(NO_ID);
  PRINT_TEST_RESULT(cl == NULL);
}

void test1_class_destroy() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_destroy(cl) == OK);
}

void test2_class_destroy() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_destroy(cl) == ERROR);
}

void test1_class_get_id() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_get_id(cl) == 1);
  class_destroy(cl);
}

void test2_class_get_id() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_id(cl) == NO_ID);
}

void test1_class_set_id() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_id(cl, 2) == OK);
  class_destroy(cl);
}

void test2_class_set_id() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_id(cl, 2) == ERROR);
}

void test1_class_get_tag() {
  Class *cl = class_create(1);
  class_set_tag(cl, 'A');
  PRINT_TEST_RESULT(class_get_tag(cl) == 'A');
  class_destroy(cl);
}

void test2_class_get_tag() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_tag(cl) == NO_TAG);
}

void test1_class_set_tag() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_tag(cl, 'B') == OK);
  class_destroy(cl);
}

void test2_class_set_tag() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_tag(cl, 'B') == ERROR);
}

void test1_class_get_name() {
  Class *cl = class_create(1);
  class_set_name(cl, "Warrior");
  PRINT_TEST_RESULT(strcmp(class_get_name(cl), "Warrior") == 0);
  class_destroy(cl);
}

void test2_class_get_name() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_name(cl) == NULL);
}

void test1_class_set_name() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_name(cl, "Archer") == OK);
  class_destroy(cl);
}

void test2_class_set_name() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_name(cl, "Archer") == ERROR);
}

void test1_class_get_desc() {
  Class *cl = class_create(1);
  class_set_desc(cl, "A brave warrior.");
  PRINT_TEST_RESULT(strcmp(class_get_desc(cl), "A brave warrior.") == 0);
  class_destroy(cl);
}

void test2_class_get_desc() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_desc(cl) == NULL);
}

void test1_class_set_desc() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_desc(cl, "Fast and stealthy.") == OK);
  class_destroy(cl);
}

void test2_class_set_desc() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_desc(cl, "Fast and stealthy.") == ERROR);
}

void test1_class_get_closeup_at_pos() {
  Class *cl = class_create(1);
  char line[POV_WDTH] = "Closeup";
  class_set_closeup_at_pos(cl, 0, line);
  PRINT_TEST_RESULT(strncmp(class_get_closeup_at_pos(cl, 0), line, 7) == 0);
  class_destroy(cl);
}

void test2_class_get_closeup_at_pos() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_closeup_at_pos(cl, 0) == NULL);
}

void test1_class_get_closeup() {
  int i = 0;
  Class *cl = class_create(1);
  char closeup[POV_HGHT][POV_WDTH + 1], result[POV_HGHT][POV_WDTH + 1];;
  strcpy(closeup[0], "Line1");
  strcpy(closeup[1], "Line2");
  for(i = 0; i < POV_HGHT; i++)
    class_set_closeup_at_pos(cl, i, closeup[i]);

  PRINT_TEST_RESULT(class_get_closeup(cl, result) == OK);

  class_destroy(cl);
}

void test2_class_get_closeup() {
  Class *cl = NULL;
  char result[POV_HGHT][POV_WDTH + 1];
  PRINT_TEST_RESULT(class_get_closeup(cl, result) == ERROR);
}

void test1_class_set_closeup_at_pos() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_closeup_at_pos(cl, 0, "Image line") == OK);
  class_destroy(cl);
}

void test2_class_set_closeup_at_pos() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_closeup_at_pos(cl, 0, "Image line") == ERROR);
}

void test1_class_get_movable() {
  Class *cl = class_create(1);
  Bool is_movable;
  class_set_movable(cl, TRUE);
  PRINT_TEST_RESULT(class_get_movable(cl, &is_movable) == OK && is_movable == TRUE);
  class_destroy(cl);
}

void test2_class_get_movable() {
  Class *cl = NULL;
  Bool is_movable;
  PRINT_TEST_RESULT(class_get_movable(cl, &is_movable) == ERROR);
}

void test1_class_set_movable() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_movable(cl, FALSE) == OK);
  class_destroy(cl);
}

void test2_class_set_movable() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_movable(cl, FALSE) == ERROR);
}

void test1_class_get_dependency() {
  Class *cl = class_create(1);
  Id dep;
  class_set_dependency(cl, 5);
  PRINT_TEST_RESULT(class_get_dependency(cl, &dep) == OK && dep == 5);
  class_destroy(cl);
}

void test2_class_get_dependency() {
  Class *cl = NULL;
  Id dep;
  PRINT_TEST_RESULT(class_get_dependency(cl, &dep) == ERROR);
}

void test1_class_set_dependency() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_dependency(cl, 7) == OK);
  class_destroy(cl);
}

void test2_class_set_dependency() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_dependency(cl, 7) == ERROR);
}

void test1_class_get_open() {
  Class *cl = class_create(1);
  Id link;
  class_set_open(cl, 3);
  PRINT_TEST_RESULT(class_get_open(cl, &link) == OK && link == 3);
  class_destroy(cl);
}

void test2_class_get_open() {
  Class *cl = NULL;
  Id link;
  PRINT_TEST_RESULT(class_get_open(cl, &link) == ERROR);
}

void test1_class_set_open() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_open(cl, 4) == OK);
  class_destroy(cl);
}

void test2_class_set_open() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_open(cl, 4) == ERROR);
}

void test1_class_get_luck() {
  Class *cl = class_create(1);
  class_set_luck(cl, 10);
  PRINT_TEST_RESULT(class_get_luck(cl) == 10);
  class_destroy(cl);
}

void test2_class_get_luck() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_get_luck(cl) == -1);
}

void test1_class_set_luck() {
  Class *cl = class_create(1);
  PRINT_TEST_RESULT(class_set_luck(cl, 5) == OK);
  class_destroy(cl);
}

void test2_class_set_luck() {
  Class *cl = NULL;
  PRINT_TEST_RESULT(class_set_luck(cl, 5) == ERROR);
}
