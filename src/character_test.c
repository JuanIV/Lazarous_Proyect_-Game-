/**
 * @brief It tests the character module
 * 
 * @file character_test.c
 * @author Juan Ibañez
 * @version 1.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

#define MAX_TESTS 48

/**
 * @brief Main function for CHARACTER unit tests.
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
        printf("Running all test for module Character:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_character_create();
    if (all || test == 2) test2_character_create();

    if (all || test == 3) test1_character_destroy();
    if (all || test == 4) test2_character_destroy();

    if (all || test == 5) test1_character_get_id();
    if (all || test == 6) test2_character_get_id();

    if (all || test == 7) test1_character_set_id();
    if (all || test == 8) test2_character_set_id();

    if (all || test == 9) test1_character_get_role();
    if (all || test == 10) test2_character_get_role();

    if (all || test == 11) test1_character_set_role();
    if (all || test == 12) test2_character_set_role();

    if (all || test == 13) test1_character_get_name();
    if (all || test == 14) test2_character_get_name();

    if (all || test == 15) test1_character_set_name();
    if (all || test == 16) test2_character_set_name();

    if (all || test == 17) test1_character_get_gdesc();
    if (all || test == 18) test2_character_get_gdesc();

    if (all || test == 19) test1_character_set_gdesc();
    if (all || test == 20) test2_character_set_gdesc();

    if (all || test == 21) test1_character_get_closeup_at_pos();
    if (all || test == 22) test2_character_get_closeup_at_pos();

    if (all || test == 23) test1_character_set_closeup_at_pos();
    if (all || test == 24) test2_character_set_closeup_at_pos();

    if (all || test == 25) test1_character_get_following();
    if (all || test == 26) test2_character_get_following();

    if (all || test == 27) test1_character_set_following();
    if (all || test == 28) test2_character_set_following();

    if (all || test == 29) test1_character_get_message();
    if (all || test == 30) test2_character_get_message();

    if (all || test == 31) test1_character_set_message();
    if (all || test == 32) test2_character_set_message();

    if (all || test == 33) test1_character_get_weapon();
    if (all || test == 34) test2_character_get_weapon();

    if (all || test == 35) test1_character_set_weapon();
    if (all || test == 36) test2_character_set_weapon();

    if (all || test == 37) test1_character_get_armor();
    if (all || test == 38) test2_character_get_armor();

    if (all || test == 39) test1_character_set_armor();
    if (all || test == 40) test2_character_set_armor();

    if (all || test == 41) test1_character_get_health();
    if (all || test == 42) test2_character_get_health();

    if (all || test == 43) test1_character_set_health();
    if (all || test == 44) test2_character_set_health();

    if (all || test == 45) test1_character_get_damage();
    if (all || test == 46) test2_character_get_damage();

    if (all || test == 47) test1_character_set_damage();
    if (all || test == 48) test2_character_set_damage();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_character_create() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(charr != NULL);
    character_destroy(charr);
}

void test2_character_create() {
    Character *charr = character_create(NO_ID);
    PRINT_TEST_RESULT(charr == NULL);
}

void test1_character_destroy() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(character_destroy(charr) == OK);
}

void test2_character_destroy() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_destroy(charr) == ERROR);
}

void test1_character_get_id() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(character_get_id(charr) == 1);
    character_destroy(charr);
}

void test2_character_get_id() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_id(charr) == NO_ID);
}

void test1_character_set_id() {
    Character *charr = character_create(1);
    character_set_id(charr, 5);
    PRINT_TEST_RESULT(character_get_id(charr) == 5);
    character_destroy(charr);
}

void test2_character_set_id() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_id(charr, 5) == ERROR);
}

void test1_character_get_role() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(character_get_role(charr) == UNDEFINED);
    character_destroy(charr);
}

void test2_character_get_role() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_role(charr) == NO_ROLE);
}

void test1_character_set_role() {
    Character *charr = character_create(1);
    character_set_role(charr, MONSTER);
    PRINT_TEST_RESULT(character_get_role(charr) == MONSTER);
    character_destroy(charr);
}

void test2_character_set_role() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_role(charr, MONSTER) == ERROR);
}

void test1_character_get_name() {
    Character *charr = character_create(1);
    character_set_name(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_name(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_get_name() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_name(charr) == NULL);
}

void test1_character_set_name() {
    Character *charr = character_create(1);
    character_set_name(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_name(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_set_name() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_name(charr, "Prueba") == ERROR);
}

void test1_character_get_gdesc() {
    Character *charr = character_create(1);
    character_set_gdesc(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_get_gdesc() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_gdesc(charr) == NULL);
}

void test1_character_set_gdesc() {
    Character *charr = character_create(1);
    character_set_gdesc(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_set_gdesc() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_gdesc(charr, "Prueba") == ERROR);
}

void test1_character_get_closeup_at_pos() {
    Character *charr = character_create(1);
    character_set_closeup_at_pos(charr, 0, "1");
    PRINT_TEST_RESULT(strncmp(character_get_closeup_at_pos(charr, 0), "1", 1) == 0);
    character_destroy(charr);
}

void test2_character_get_closeup_at_pos() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_closeup_at_pos(charr, 0) == NULL);
}

void test1_character_set_closeup_at_pos() {
    Character *charr = character_create(1);
    character_set_closeup_at_pos(charr, 0, "1");
    PRINT_TEST_RESULT(strncmp(character_get_closeup_at_pos(charr, 0), "1", 1) == 0);
    character_destroy(charr);
}

void test2_character_set_closeup_at_pos() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_closeup_at_pos(charr, 0, "Prueba") == ERROR);
}

void test1_character_get_following() {
    Character *charr = character_create(1);
    Id following;
    character_set_following(charr, 2);
   character_get_following(charr, &following);
    PRINT_TEST_RESULT(following == 2);
    character_destroy(charr);
}

void test2_character_get_following() {
    Character *charr = NULL;
    Id following;
    PRINT_TEST_RESULT(character_get_following(charr, &following) == ERROR);
}

void test1_character_set_following() {
    Character *charr = character_create(1);
    Id following;
    character_set_following(charr, 2);
    character_get_following(charr, &following);
    PRINT_TEST_RESULT(following == 2);
    character_destroy(charr);
}

void test2_character_set_following() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_following(charr, 2) == ERROR);
}

void test1_character_get_message() {
    Character *charr = character_create(1);
    character_set_message(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_message(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_get_message() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_message(charr) == NULL);
}

void test1_character_set_message() {
    Character *charr = character_create(1);
    character_set_message(charr, "Prueba");
    PRINT_TEST_RESULT(strcmp(character_get_message(charr), "Prueba") == 0);
    character_destroy(charr);
}

void test2_character_set_message() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_message(charr, "Prueba") == ERROR);
}

void test1_character_get_weapon() {
    Character *charr = character_create(1);
    Id weapon;
    character_set_weapon(charr, 10);
    character_get_weapon(charr, &weapon);
    PRINT_TEST_RESULT(weapon == 10);
    character_destroy(charr);
}

void test2_character_get_weapon() {
    Character *charr = NULL;
    Id weapon;
    PRINT_TEST_RESULT(character_get_weapon(charr, &weapon) == ERROR);
}

void test1_character_set_weapon() {
    Character *charr = character_create(1);
    Id weapon;
    character_set_weapon(charr, 10);
    character_get_weapon(charr, &weapon);
    PRINT_TEST_RESULT(weapon == 10);
    character_destroy(charr);
}

void test2_character_set_weapon() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_weapon(charr, 10) == ERROR);
}

void test1_character_get_armor() {
    Character *charr = character_create(1);
    Id armor;
    character_set_armor(charr, 20);
    character_get_armor(charr, &armor);
    PRINT_TEST_RESULT(armor == 20);
    character_destroy(charr);
}

void test2_character_get_armor() {
    Character *charr = NULL;
    Id armor;
    PRINT_TEST_RESULT(character_get_armor(charr, &armor) == ERROR);
}

void test1_character_set_armor() {
    Character *charr = character_create(1);
    Id armor;
    character_set_armor(charr, 20);
    character_get_armor(charr, &armor);
    PRINT_TEST_RESULT(armor == 20);
    character_destroy(charr);
}

void test2_character_set_armor() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_armor(charr, 20) == ERROR);
}

void test1_character_get_health() {
    Character *charr = character_create(1);
    character_set_health(charr, 100);
    PRINT_TEST_RESULT(character_get_health(charr) == 100);
    character_destroy(charr);
}

void test2_character_get_health() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_health(charr) == -1);
}

void test1_character_set_health() {
    Character *charr = character_create(1);
    character_set_health(charr, 100);
    PRINT_TEST_RESULT(character_get_health(charr) == 100);
    character_destroy(charr);
}

void test2_character_set_health() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_health(charr, 100) == ERROR);
}

void test1_character_get_damage() {
    Character *charr = character_create(1);
    character_set_damage(charr, 50);
    PRINT_TEST_RESULT(character_get_damage(charr) == 50);
    character_destroy(charr);
}

void test2_character_get_damage() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_damage(charr) == -1);
}

void test1_character_set_damage() {
    Character *charr = character_create(1);
    character_set_damage(charr, 50);
    PRINT_TEST_RESULT(character_get_damage(charr) == 50);
    character_destroy(charr);
}

void test2_character_set_damage() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_set_damage(charr, 50) == ERROR);
}


