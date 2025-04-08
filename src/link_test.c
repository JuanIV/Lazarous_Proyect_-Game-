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

#define MAX_TESTS 21


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

	if (all || test == 7) test1_link_set_name();
	if (all || test == 8) test2_link_set_name();

	if (all || test == 9) test1_link_get_name();

	if (all || test == 10) test1_link_set_origin();
	if (all || test == 11) test2_link_set_origin();

	if (all || test == 12) test1_link_get_orig();

	if (all || test == 13) test1_link_set_destination();
	if (all || test == 14) test2_link_set_destination();

	if (all || test == 15) test1_link_get_dest();

	if (all || test == 16) test1_link_set_direction();
	if (all || test == 17) test2_link_set_direction();

	if (all || test == 18) test1_link_get_direction();

	if (all || test == 19) test1_link_set_open();
	if (all || test == 20) test2_link_set_open();
	
	if (all || test == 21) test1_link_get_open();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_link_create() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(l != NULL);
	link_destroy(l);
}

void test2_link_create() {
	Link *l = link_create(0);
	PRINT_TEST_RESULT(link_get_id(l) == 0);
	link_destroy(l);
}

void test1_link_destroy() {
	Link *l = link_create(0);
	PRINT_TEST_RESULT(link_destroy(l) == OK);
}

void test2_link_destroy() {
	Link *l = NULL;
	PRINT_TEST_RESULT(link_destroy(l) == ERROR);
}

void test1_link_get_id() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_get_id(l) == 1);
	link_destroy(l);
}

void test2_link_get_id() {
	Link *l = link_create(NO_ID);
	PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
	link_destroy(l);
}

void test1_link_set_name() {
	Link *l = link_create(1);
	link_set_name(l, "Link1");
	PRINT_TEST_RESULT(strcmp(link_get_name(l), "Link1") == 0);
	link_destroy(l);
}

void test2_link_set_name() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
	link_destroy(l);
}

void test1_link_get_name() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(strcmp(link_get_name(l), "") == 0);
	link_destroy(l);
}

void test1_link_set_origin() {
	Link *l = link_create(1);
	link_set_orig(l, 100);
	PRINT_TEST_RESULT(link_get_orig(l) == 100);
	link_destroy(l);
}

void test2_link_set_origin() {
	Link *l = link_create(1);
	link_set_orig(l, NO_ID);
	PRINT_TEST_RESULT(link_get_orig(l) == NO_ID);
	link_destroy(l);
}

void test1_link_get_orig() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_get_orig(l) == NO_ID);
	link_destroy(l);
}

void test1_link_set_destination() {
	Link *l = link_create(1);
	link_set_dest(l, 200);
	PRINT_TEST_RESULT(link_get_dest(l) == 200);
	link_destroy(l);
}

void test2_link_set_destination() {
	Link *l = link_create(1);
	link_set_dest(l, NO_ID);
	PRINT_TEST_RESULT(link_get_dest(l) == NO_ID);
	link_destroy(l);
}

void test1_link_get_dest() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_get_dest(l) == NO_ID);
	link_destroy(l);
}

void test1_link_set_direction() {
	Link *l = link_create(1);
	link_set_direction(l, N);
	PRINT_TEST_RESULT(link_get_direction(l) == N);
	link_destroy(l);
}

void test2_link_set_direction() {
	Link *l = link_create(1);
	link_set_direction(l, UNK_DIR);
	PRINT_TEST_RESULT(link_get_direction(l) == UNK_DIR);
	link_destroy(l);
}

void test1_link_get_direction() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_get_direction(l) == UNK_DIR);
	link_destroy(l);
}

void test1_link_set_open() {
	Link *l = link_create(1);
	link_set_open(l, TRUE);
	PRINT_TEST_RESULT(link_get_open(l) == TRUE);
	link_destroy(l);
}

void test2_link_set_open() {
	Link *l = link_create(1);
	link_set_open(l, FALSE);
	PRINT_TEST_RESULT(link_get_open(l) == FALSE);
	link_destroy(l);
}

void test1_link_get_open() {
	Link *l = link_create(1);
	PRINT_TEST_RESULT(link_get_open(l) == FALSE);
	link_destroy(l);
}