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

#define MAX_TESTS 56

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

	if (all || test == 9) test1_player_get_role();
	if (all || test == 10) test2_player_get_role();

	if (all || test == 11) test1_player_set_role();
	if (all || test == 12) test2_player_set_role();

	if (all || test == 13) test1_player_get_name();
	if (all || test == 14) test2_player_get_name();

	if (all || test == 15) test1_player_set_name();
	if (all || test == 16) test2_player_set_name();
	if (all || test == 17) test3_player_set_name();

	if (all || test == 18) test1_player_get_weapon();
	if (all || test == 19) test2_player_get_weapon();
	if (all || test == 20) test3_player_get_weapon();

	if (all || test == 21) test1_player_set_weapon();
	if (all || test == 22) test2_player_set_weapon();

	if (all || test == 23) test1_player_get_backpack();
	if (all || test == 24) test2_player_get_backpack();

	if (all || test == 25) test1_player_add_object();
	if (all || test == 26) test2_player_add_object();

	if (all || test == 27) test1_player_delete_object();
	if (all || test == 28) test2_player_delete_object();

	if (all || test == 29) test1_player_has_object();
	if (all || test == 30) test2_player_has_object();

	if (all || test == 31) test1_player_inventory_is_full();
	if (all || test == 32) test2_player_inventory_is_full();

	if (all || test == 33) test1_player_set_inventory_size();
	if (all || test == 34) test2_player_set_inventory_size();

	if (all || test == 35) test1_player_get_health();
	if (all || test == 36) test2_player_get_health();

	if (all || test == 37) test1_player_set_health();
	if (all || test == 38) test2_player_set_health();

	if (all || test == 39) test1_player_get_location();
	if (all || test == 40) test2_player_get_location();

	if (all || test == 41) test1_player_set_location();
	if (all || test == 42) test2_player_set_location();

	if (all || test == 43) test1_player_get_gdesc();
	if (all || test == 44) test2_player_get_gdesc();

	if (all || test == 45) test1_player_set_gdesc();
	if (all || test == 46) test2_player_set_gdesc();

	if (all || test == 47) test1_player_get_closeup_at();
	if (all || test == 48) test2_player_get_closeup_at();

	if (all || test == 49) test1_player_get_closeup();
	if (all || test == 50) test2_player_get_closeup();

	if (all || test == 51) test1_player_set_closeup_at();
	if (all || test == 52) test2_player_set_closeup_at();

    if(all || test == 53) test1_player_get_armor();
	if(all || test == 54) test2_player_get_armor();

	if(all || test == 55) test1_player_set_armor();
	if(all || test == 56) test2_player_set_armor();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_player_create() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(p != NULL);
	player_destroy(p);
  }
  
  void test2_player_create() {
	Player *p = player_create(NO_ID);
	PRINT_TEST_RESULT(p == NULL);
  }
  
  void test1_player_destroy() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_destroy(p) == OK);
  }
  
  void test2_player_destroy() {
	Player *p = NULL;
	PRINT_TEST_RESULT(player_destroy(p) == ERROR);
  }
  
  void test1_player_get_id() {
	Player *p = player_create(22);
	PRINT_TEST_RESULT(player_get_id(p) == 22);
	player_destroy(p);
  }
  
  void test2_player_get_id() {
	Player *p = NULL;
	PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
  }
  
  void test1_player_set_id() {
	Player *p = player_create(1);
	player_set_id(p, 88);
	PRINT_TEST_RESULT(player_get_id(p) == 88);
	player_destroy(p);
  }
  
  void test2_player_set_id() {
	PRINT_TEST_RESULT(player_set_id(NULL, 50) == ERROR);
  }

  void test1_player_get_role() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_get_role(p) == UNDEFINED);
	player_destroy(p);
  }
  
  void test2_player_get_role() {
	PRINT_TEST_RESULT(player_get_role(NULL) == NO_ROLE);
  }
  
  void test1_player_set_role() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_role(p, MONSTER) == OK);
	player_destroy(p);
  }
  
  void test2_player_set_role() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_role(p, NO_ROLE) == ERROR);
	player_destroy(p);
  }

  void test1_player_get_name() {
	Player *p = player_create(1);
	player_set_name(p, "Hero");
	PRINT_TEST_RESULT(strcmp(player_get_name(p), "Hero") == 0);
	player_destroy(p);
  }
  
  void test2_player_get_name() {
	PRINT_TEST_RESULT(player_get_name(NULL) == NULL);
  }
  
  void test1_player_set_name() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_name(p, "Prueba") == OK);
	player_destroy(p);
  }
  
  void test2_player_set_name() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
	player_destroy(p);
  }
  
  void test3_player_set_name() {
	PRINT_TEST_RESULT(player_set_name(NULL, "Prueba") == ERROR);
  }

  void test1_player_get_weapon() {
	Player *p = player_create(1);
	Id id;
	player_set_weapon(p, 99);
	player_get_weapon(p, &id);
	PRINT_TEST_RESULT(id == 99);
	player_destroy(p);
  }
  
  void test2_player_get_weapon() {
	Id id = 0;
	PRINT_TEST_RESULT(player_get_weapon(NULL, &id) == ERROR);
  }
  
  void test3_player_get_weapon() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_get_weapon(p, NULL) == ERROR);
	player_destroy(p);
  }
  
  void test1_player_set_weapon() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_weapon(p, 77) == OK);
	player_destroy(p);
  }
  
  void test2_player_set_weapon() {
	PRINT_TEST_RESULT(player_set_weapon(NULL, 88) == ERROR);
  }

  void test1_player_get_backpack() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_get_backpack(p) != NULL);
	player_destroy(p);
  }
  
  void test2_player_get_backpack() {
	PRINT_TEST_RESULT(player_get_backpack(NULL) == NULL);
  }

  void test1_player_add_object() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_add_object(p, 100) == OK);
	player_destroy(p);
  }
  
  void test2_player_add_object() {
	PRINT_TEST_RESULT(player_add_object(NULL, 100) == ERROR);
  }
  
  void test1_player_delete_object() {
	Player *p = player_create(1);
	player_add_object(p, 200);
	PRINT_TEST_RESULT(player_delete_object(p, 200) == OK);
	player_destroy(p);
  }
  
  void test2_player_delete_object() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_delete_object(p, 300) == ERROR);
	player_destroy(p);
  }

  void test1_player_has_object() {
	Player *p = player_create(1);
	player_add_object(p, 101);
	PRINT_TEST_RESULT(player_has_object(p, 101) == TRUE);
	player_destroy(p);
  }
  
  void test2_player_has_object() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_has_object(p, 999) == FALSE);
	player_destroy(p);
  }

  void test1_player_inventory_is_full() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_inventory_is_full(p) == FALSE);
	player_destroy(p);
  }
  
  void test2_player_inventory_is_full() {
	Player *p = player_create(1);
	player_add_object(p, 1);
	PRINT_TEST_RESULT(player_inventory_is_full(p) == FALSE);
	player_destroy(p);
  }

  void test1_player_set_inventory_size() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_inventory_size(p, 5) == OK);
	player_destroy(p);
  }
  
  void test2_player_set_inventory_size() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_inventory_size(p, -1) == ERROR);
	player_destroy(p);
  }

  void test1_player_get_health() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_get_health(p) == 10);
	player_destroy(p);
  }
  
  void test2_player_get_health() {
	PRINT_TEST_RESULT(player_get_health(NULL) == -1);
  }

  void test1_player_set_health() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_health(p, 50) == OK);
	player_destroy(p);
  }
  
  void test2_player_set_health() {
	PRINT_TEST_RESULT(player_set_health(NULL, 50) == ERROR);
  }

  void test1_player_get_location() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
	player_destroy(p);
  }
  
  void test2_player_get_location() {
	PRINT_TEST_RESULT(player_get_location(NULL) == NO_ID);
  }

  void test1_player_set_location() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_location(p, 999) == OK);
	player_destroy(p);
  }
  
  void test2_player_set_location() {
	PRINT_TEST_RESULT(player_set_location(NULL, 999) == ERROR);
  }

  void test1_player_get_gdesc() {
	Player *p = player_create(1);
	player_set_gdesc(p, "1");
	PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "1") == 0);
	player_destroy(p);
  }
  
  void test2_player_get_gdesc() {
	PRINT_TEST_RESULT(player_get_gdesc(NULL) == NULL);
  }

  void test1_player_set_gdesc() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_gdesc(p, "Prueba") == OK);
	player_destroy(p);
  }
  
  void test2_player_set_gdesc() {
	PRINT_TEST_RESULT(player_set_gdesc(NULL, "Prueba") == ERROR);
  }

  void test1_player_get_closeup_at() {
	Player *p = player_create(1);
	player_set_closeup_at(p, 1, "2");
	PRINT_TEST_RESULT(strncmp(player_get_closeup_at(p, 1), "2", 1) == 0); 
	player_destroy(p);
  }
  
  void test2_player_get_closeup_at() {
	PRINT_TEST_RESULT(player_get_closeup_at(NULL, 1) == NULL);
  }

  void test1_player_get_closeup() {
	Player *p = player_create(1);
	char expected[POV_HGHT][POV_WDTH + 1];
	player_set_closeup_at(p, 0, "line0");
	player_set_closeup_at(p, 1, "line1");
	player_set_closeup_at(p, 2, "line2");
	PRINT_TEST_RESULT(player_get_closeup(p, expected) == OK);
	player_destroy(p);
  }
  
  void test2_player_get_closeup() {
	char copy[POV_HGHT][POV_WDTH + 1];
	PRINT_TEST_RESULT(player_get_closeup(NULL, copy) == ERROR);
  }

  void test1_player_set_closeup_at() {
	Player *p = player_create(1);
	PRINT_TEST_RESULT(player_set_closeup_at(p, 0, "HELLO") == OK);
	player_destroy(p);
  }
  
  void test2_player_set_closeup_at() {
	PRINT_TEST_RESULT(player_set_closeup_at(NULL, 0, "FAIL") == ERROR);
  }

  void test1_player_get_armor() {
	Player *p = player_create(1);
	Id id = 20;
	player_set_armor(p, 20);
	PRINT_TEST_RESULT(player_get_armor(p, &id) == OK);
	player_destroy(p);
  }

  void test2_player_get_armor() {
	Player *p = NULL;
	Id id = 20;
	PRINT_TEST_RESULT(player_get_armor(p, &id) == ERROR);
  }

  void test1_player_set_armor() {
	Player *p = player_create(1);
	Id id = 20;
	player_set_armor(p, 20);
	PRINT_TEST_RESULT(player_get_armor(p, &id) == OK);
	player_destroy(p);
  }

  void test2_player_set_armor() {
	Player *p = NULL;
	Id id = 20;
	PRINT_TEST_RESULT(player_set_armor(p, id) == ERROR);
  }
