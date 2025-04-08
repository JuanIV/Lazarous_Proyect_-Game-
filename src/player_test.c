/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Alina Datsko
 * @version 0.0
 * @date 04-04-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 34

/**
 * @brief Main function for PLAYER unit tests.
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
		printf("Running all tests for module Player:\n");
	} else {
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
		if (test < 1 || test > MAX_TESTS) {
			printf("Error: unknown test %d\t", test);
			exit(EXIT_SUCCESS);
		}
	}

	if (all || test == 1) test1_player_create();
	if (all || test == 2) test2_player_create();

	if (all || test == 3) test1_player_destroy();
	if (all || test == 4) test2_player_destroy();

	if (all || test == 5) test1_player_get_id();
	if (all || test == 6) test2_player_get_id();

	if (all || test == 7) test1_player_set_id();
	if (all || test == 8) test2_player_set_id();

	if (all || test == 9) test1_player_get_name();
	if (all || test == 10) test2_player_get_name();

	if (all || test == 11) test1_player_set_name();
	if (all || test == 12) test2_player_set_name();

	if (all || test == 13) test1_player_add_object();
	if (all || test == 14) test2_player_add_object();

	if (all || test == 15) test1_player_delete_object();
	if (all || test == 16) test2_player_delete_object();

	if (all || test == 17) test1_player_has_object();
	if (all || test == 18) test2_player_has_object();

	if (all || test == 19) test1_player_inventory_is_full();
	if (all || test == 20) test2_player_inventory_is_full();

	if (all || test == 21) test1_player_set_inventory_size();
	if (all || test == 22) test2_player_set_inventory_size();

	if (all || test == 23) test1_player_get_health();
	if (all || test == 24) test2_player_get_health();

	if (all || test == 25) test1_player_set_health();
	if (all || test == 26) test2_player_set_health();

	if (all || test == 27) test1_player_get_location();
	if (all || test == 28) test2_player_get_location();

	if (all || test == 29) test1_player_set_location();
	if (all || test == 30) test2_player_set_location();

	if (all || test == 31) test1_player_get_gdesc();
	if (all || test == 32) test2_player_get_gdesc();

	if (all || test == 33) test1_player_set_gdesc();
	if (all || test == 34)test2_player_set_gdesc();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_player_create() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(play != NULL);
	player_destroy(play);
}

void test2_player_create() {
	Player *play = player_create(NO_ID);
	PRINT_TEST_RESULT(play == NULL);
}

void test1_player_destroy() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(player_destroy(play) == OK);
}

void test2_player_destroy() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_destroy(play) == ERROR);
}

void test1_player_get_id() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(player_get_id(play) == 1);
	player_destroy(play);
}

void test2_player_get_id() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_get_id(play) == NO_ID);
}

void test1_player_set_id() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(player_set_id(play, 2) == OK);
	player_destroy(play);
}

void test2_player_set_id() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_id(play, 2) == ERROR);
}

void test1_player_get_name() {
	Player *play = player_create(1);
	player_set_name(play, "Hero");
	PRINT_TEST_RESULT(strcmp(player_get_name(play), "Hero") == 0);
	player_destroy(play);
}

void test2_player_get_name() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_get_name(play) == NULL);
}

void test1_player_set_name() {
	Player *play = player_create(1);
	player_set_name(play, "Hero");
	PRINT_TEST_RESULT(strcmp(player_get_name(play), "Hero") == 0);
	player_destroy(play);
}

void test2_player_set_name() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_name(play, "Hero") == ERROR);
}

void test1_player_add_object() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(player_add_object(play, 10) == OK);
	player_destroy(play);
}

void test2_player_add_object() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_add_object(play, 10) == ERROR);
}

void test1_player_delete_object() {
	Player *play = player_create(1);
	player_add_object(play, 10);
	PRINT_TEST_RESULT(player_delete_object(play, 10) == OK);
	player_destroy(play);
}

void test2_player_delete_object() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_delete_object(play, 10) == ERROR);
}

void test1_player_has_object() {
	Player *play = player_create(1);
	player_add_object(play, 10);
	PRINT_TEST_RESULT(player_has_object(play, 10) == TRUE);
	player_destroy(play);
}

void test2_player_has_object() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_has_object(play, 10) == FALSE);
}

void test1_player_inventory_is_full() {
	Player *play = player_create(1);
	player_set_inventory_size(play, 1);
	player_add_object(play, 10);
	PRINT_TEST_RESULT(player_inventory_is_full(play) == TRUE);
	player_destroy(play);
}

void test2_player_inventory_is_full() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_inventory_is_full(play) == FALSE);
}

void test1_player_set_inventory_size() {
	Player *play = player_create(1);
	PRINT_TEST_RESULT(player_set_inventory_size(play, 5) == OK);
	player_destroy(play);
}

void test2_player_set_inventory_size() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_inventory_size(play, 5) == ERROR);
}

void test1_player_get_health() {
	Player *play = player_create(1);
	player_set_health(play, 100);
	PRINT_TEST_RESULT(player_get_health(play) == 100);
	player_destroy(play);
}

void test2_player_get_health() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_get_health(play) == -1); 
}

void test1_player_set_health() {
	Player *play = player_create(1);
	player_set_health(play, 100);
	PRINT_TEST_RESULT(player_get_health(play) == 100);
	player_destroy(play);
}

void test2_player_set_health() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_health(play, 100) == ERROR);
}

void test1_player_get_location() {
	Player *play = player_create(1);
	player_set_location(play, 5);
	PRINT_TEST_RESULT(player_get_location(play) == 5);
	player_destroy(play);
}

void test2_player_get_location() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_get_location(play) == NO_ID);
}

void test1_player_set_location() {
	Player *play = player_create(1);
	player_set_location(play, 5);
	PRINT_TEST_RESULT(player_get_location(play) == 5);
	player_destroy(play);
}

void test2_player_set_location() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_location(play, 5) == ERROR);
}

void test1_player_get_gdesc() {
	Player *play = player_create(1);
	player_set_gdesc(play, "Paint");
	PRINT_TEST_RESULT(strcmp(player_get_gdesc(play), "Paint") == 0);
	player_destroy(play);
}

void test2_player_get_gdesc() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_get_gdesc(play) == NULL);
}

void test1_player_set_gdesc() {
	Player *play = player_create(1);
	player_set_gdesc(play, "Paint");
	PRINT_TEST_RESULT(strcmp(player_get_gdesc(play), "Paint") == 0);
	player_destroy(play);
}

void test2_player_set_gdesc() {
	Player *play = NULL;
	PRINT_TEST_RESULT(player_set_gdesc(play, "Paint") == ERROR);
}