/**
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Lucas Blanco Rodríguez
 * @version 0.0
 * @date 24-03-2025
 * @copyright GNU Public License
 */

#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link_test.h"
#include "test.h"

#define MAX_TESTS 42


 /** 
 * @brief Main function for LINK unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {
	int test = 0;
	int all = 1;

	if (argc < 2) {
		printf("Running all tests for Link module:\n");
	} else {
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
		if (test < 1 || test > MAX_TESTS) {
			printf("Error: unknown test %d\n", test);
			exit(EXIT_SUCCESS);
		}
	}

	if (all || test == 1) test1_link_create();
    if (all || test == 2) test2_link_create();

    if (all || test == 3) test1_link_destroy();
    if (all || test == 4) test2_link_destroy();

    if (all || test == 5) test1_link_get_id();
    if (all || test == 6) test2_link_get_id();

    if (all || test == 7) test1_link_get_name();
    if (all || test == 8) test2_link_get_name();

    if (all || test == 9) test1_link_set_name();
    if (all || test == 10) test2_link_set_name();

    if (all || test == 11) test1_link_get_orig();
    if (all || test == 12) test2_link_get_orig();

    if (all || test == 13) test1_link_set_orig();
    if (all || test == 14) test2_link_set_orig();

    if (all || test == 15) test1_link_get_dest();
    if (all || test == 16) test2_link_get_dest();

    if (all || test == 17) test1_link_set_dest();
    if (all || test == 18) test2_link_set_dest();

    if (all || test == 19) test1_link_get_direction();
    if (all || test == 20) test2_link_get_direction();

    if (all || test == 21) test1_link_set_direction();
    if (all || test == 22) test2_link_set_direction();

    if (all || test == 23) test1_link_get_open();
    if (all || test == 24) test2_link_get_open();

    if (all || test == 25) test1_link_set_open();
    if (all || test == 26) test2_link_set_open();

    if (all || test == 27) test1_link_get_locked();
    if (all || test == 28) test2_link_get_locked();

    if (all || test == 29) test1_link_set_locked();
    if (all || test == 30) test2_link_set_locked();

    if (all || test == 31) test1_link_get_connected();
    if (all || test == 32) test2_link_get_connected();

    if (all || test == 33) test1_link_set_connected();
    if (all || test == 34) test2_link_set_connected();

    if (all || test == 35) test1_link_get_open_role();
    if (all || test == 36) test2_link_get_open_role();

    if (all || test == 37) test1_link_set_open_role();
    if (all || test == 38) test2_link_set_open_role();

    if (all || test == 39) test1_link_get_use_role();
    if (all || test == 40) test2_link_get_use_role();

    if (all || test == 41) test1_link_set_use_role();
    if (all || test == 42) test2_link_set_use_role();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_link_create() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link != NULL);
	link_destroy(link);
  }
  
  void test2_link_create() {
	Link *link = link_create(NO_ID);
	PRINT_TEST_RESULT(link == NULL);
  }
  
  void test1_link_destroy() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_destroy(link) == OK);
  }
  
  void test2_link_destroy() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_destroy(link) == ERROR);
  }
  
  void test1_link_get_id() {
	Link *link = link_create(22);
	PRINT_TEST_RESULT(link_get_id(link) == 22);
	link_destroy(link);
  }
  
  void test2_link_get_id() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_id(link) == NO_ID);
  }
  
  void test1_link_get_name() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_get_name(link) != NULL);
	link_destroy(link);
  }
  
  void test2_link_get_name() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_name(link) == NULL);
  }
  
  void test1_link_set_name() {
	Link *link = link_create(1);
	link_set_name(link, "Link1");
	PRINT_TEST_RESULT(strcmp(link_get_name(link), "Link1") == 0);
	link_destroy(link);
  }
  
  void test2_link_set_name() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
  }
  
  void test1_link_get_orig() {
	Link *link = link_create(1);
	link_set_orig(link, 100);
	PRINT_TEST_RESULT(link_get_orig(link) == 100);
	link_destroy(link);
  }
  
  void test2_link_get_orig() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_orig(link) == NO_ID);
  }
  
  void test1_link_set_orig() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_orig(link, 200) == OK);
	PRINT_TEST_RESULT(link_get_orig(link) == 200);
	link_destroy(link);
  }
  
  void test2_link_set_orig() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_orig(link, 300) == ERROR);
  }
  
  void test1_link_get_dest() {
	Link *link = link_create(1);
	link_set_dest(link, 500);
	PRINT_TEST_RESULT(link_get_dest(link) == 500);
	link_destroy(link);
  }
  
  void test2_link_get_dest() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_dest(link) == NO_ID);
  }
  
  void test1_link_set_dest() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_dest(link, 600) == OK);
	PRINT_TEST_RESULT(link_get_dest(link) == 600);
	link_destroy(link);
  }
  
  void test2_link_set_dest() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_dest(link, 700) == ERROR);
  }
  
  void test1_link_get_direction() {
	Link *link = link_create(1);
	link_set_direction(link, N);
	PRINT_TEST_RESULT(link_get_direction(link) == N);
	link_destroy(link);
  }
  
  void test2_link_get_direction() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_direction(link) == UNK_DIR);
  }
  
  void test1_link_set_direction() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_direction(link, E) == OK);
	PRINT_TEST_RESULT(link_get_direction(link) == E);
	link_destroy(link);
  }
  
  void test2_link_set_direction() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_direction(link, W) == ERROR);
  }
  
  void test1_link_get_open() {
	Link *link = link_create(1);
	Bool is_open;
	link_set_open(link, TRUE);
	PRINT_TEST_RESULT(link_get_open(link, &is_open) == OK && is_open == TRUE);
	link_destroy(link);
  }
  
  void test2_link_get_open() {
	Link *link = NULL;
	Bool is_open;
	PRINT_TEST_RESULT(link_get_open(link, &is_open) == ERROR);
  }
  
  void test1_link_set_open() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_open(link, FALSE) == OK);
	link_destroy(link);
  }
  
  void test2_link_set_open() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_open(link, TRUE) == ERROR);
  }
  
  void test1_link_get_locked() {
	Link *link = link_create(1);
	Bool is_locked;
	link_set_locked(link, TRUE);
	PRINT_TEST_RESULT(link_get_locked(link, &is_locked) == OK && is_locked == TRUE);
	link_destroy(link);
  }
  
  void test2_link_get_locked() {
	Link *link = NULL;
	Bool is_locked;
	PRINT_TEST_RESULT(link_get_locked(link, &is_locked) == ERROR);
  }
  
  void test1_link_set_locked() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_locked(link, FALSE) == OK);
	link_destroy(link);
  }
  
  void test2_link_set_locked() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_locked(link, TRUE) == ERROR);
  }
  
  void test1_link_get_connected() {
	Link *link = link_create(1);
	Bool is_connected;
	link_set_connected(link, TRUE);
	PRINT_TEST_RESULT(link_get_connected(link, &is_connected) == OK && is_connected == TRUE);
	link_destroy(link);
  }
  
  void test2_link_get_connected() {
	Link *link = NULL;
	Bool is_connected;
	PRINT_TEST_RESULT(link_get_connected(link, &is_connected) == ERROR);
  }
  
  void test1_link_set_connected() {
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_connected(link, FALSE) == OK);
	link_destroy(link);
  }
  
  void test2_link_set_connected() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_connected(link, TRUE) == ERROR);
  }
  
  void test1_link_get_open_role() {
	Link *link = link_create(1);
	link_set_open_role(link, MONSTER);
	PRINT_TEST_RESULT(link_get_open_role(link) == MONSTER);
	link_destroy(link);
  }
  
  void test2_link_get_open_role() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_open_role(link) == NO_ROLE);
  }
  
  void test1_link_set_open_role() {
	Link *link = link_create(1);
	link_set_open_role(link, TEAM1);
	PRINT_TEST_RESULT(link_get_open_role(link) == TEAM1);
	link_destroy(link);
  }
  
  void test2_link_set_open_role() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_open_role(link, NO_ROLE) == ERROR);
  }
  
  void test1_link_get_use_role() {
	Link *link = link_create(1);
	link_set_use_role(link, MONSTER);
	PRINT_TEST_RESULT(link_get_use_role(link) == MONSTER);
	link_destroy(link);
  }
  
  void test2_link_get_use_role() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_use_role(link) == NO_ROLE);
  }
  
  void test1_link_set_use_role() {
	Link *link = link_create(1);
	link_set_use_role(link, TEAM2);
	PRINT_TEST_RESULT(link_get_use_role(link) == TEAM2);
	link_destroy(link);
  }
  
  void test2_link_set_use_role() {
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_use_role(link, NO_ROLE) == ERROR);
  }
  