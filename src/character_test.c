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

#define MAX_TESTS 23

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
    if (all || test == 3) test3_character_create();

    if (all || test == 4) test1_character_destroy();
    if (all || test == 5) test2_character_destroy();

    if (all || test == 6) test1_character_get_id();
    if (all || test == 7) test2_character_get_id();

    if (all || test == 8) test1_character_set_id();

    if (all || test == 9) test1_character_get_name();
    if (all || test == 10) test2_character_get_name();

    if (all || test == 11) test1_character_set_name();

    if (all || test == 12) test1_character_get_gdesc();
    if (all || test == 13) test2_character_get_gdesc();

    if (all || test == 14) test1_character_set_gdesc();

    if (all || test == 15) test1_character_get_message();
    if (all || test == 16) test2_character_get_message();

    if (all || test == 17) test1_character_set_message();

    if (all || test == 18) test1_character_get_health();
    if (all || test == 19) test2_character_get_health();

    if (all || test == 20) test1_character_set_health();

    if (all || test == 21) test1_character_get_friendly();
    if (all || test == 22) test2_character_get_friendly();
    if (all || test == 23) test3_character_get_friendly();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}


void test1_character_create() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(charr != NULL);
    character_destroy(charr);
}

void test2_character_create() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT(character_get_id(charr) == 1);
    character_destroy(charr);
}

void test3_character_create() {
    Character *charr = character_create(1);
    PRINT_TEST_RESULT((strlen(character_get_name(charr))+strlen(character_get_gdesc(charr))+strlen(character_get_message(charr))) == 0);
    character_destroy(charr);
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

void test1_character_get_name() {
    Character *charr = character_create(1);
    character_set_name(charr, "Test");
    PRINT_TEST_RESULT(strcmp(character_get_name(charr), "Test") == 0);
    character_destroy(charr);
}

void test2_character_get_name() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_name(charr) == NULL);
}

void test1_character_set_name() {
    Character *charr = character_create(1);
    character_set_name(charr,"Test");
    PRINT_TEST_RESULT(strcmp(character_get_name(charr),"Test") == 0);
    character_destroy(charr);
}

void test1_character_get_gdesc() {
    Character *charr = character_create(1);
    character_set_gdesc(charr, "Test");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(charr), "Test") == 0);
    character_destroy(charr);
}

void test2_character_get_gdesc() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_gdesc(charr) == NULL);
}

void test1_character_set_gdesc() {
    Character *charr = character_create(1);
    character_set_gdesc(charr, "Test");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(charr),"Test") == 0);
    character_destroy(charr);
}

void test1_character_get_message() {
    Character *charr = character_create(1);
    character_set_message(charr, "Test");
    PRINT_TEST_RESULT(strcmp(character_get_message(charr), "Test") == 0);
    character_destroy(charr);
}

void test2_character_get_message() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_message(charr) == NULL);
}

void test1_character_set_message() {
    Character *charr = character_create(1);
    character_set_message(charr, "Test");
    PRINT_TEST_RESULT(!strcmp(character_get_message(charr),"Test"));
    character_destroy(charr);
}

void test1_character_get_health() {
    Character *charr = character_create(1);
    character_set_health(charr,5);
    PRINT_TEST_RESULT(character_get_health(charr) == 5);
    character_destroy(charr);
}

void test2_character_get_health() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_health(charr) == -1);
}

void test1_character_set_health() {
    Character *charr = character_create(1);
    character_set_health(charr, 5);
    PRINT_TEST_RESULT(character_get_health(charr) == 5);
    character_destroy(charr);
}

void test1_character_get_friendly() {
    Character *charr = character_create(1);
    character_set_friendly(charr,TRUE);
    PRINT_TEST_RESULT(character_get_friendly(charr) == TRUE);
    character_destroy(charr);
}

void test2_character_get_friendly() {
    Character *charr = character_create(1);
    character_set_friendly(charr, FALSE);
    PRINT_TEST_RESULT(character_get_friendly(charr) == FALSE);
    character_destroy(charr);
}

void test3_character_get_friendly() {
    Character *charr = NULL;
    PRINT_TEST_RESULT(character_get_friendly(charr) == FALSE);
}


