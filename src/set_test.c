/**
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Tiago Oselka
 * @version 0.0
 * @date 24-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 20

/**
 * @brief Main function for SET unit tests.
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
        printf("Running all test for module Set:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_set_create();
    if (all || test == 2) test2_set_create();

    if (all || test == 3) test1_set_destroy();
    if (all || test == 4) test2_set_destroy();

    if (all || test == 5) test1_set_add();
    if (all || test == 6) test2_set_add();
    if (all || test == 7) test3_set_add();

    if (all || test == 8) test1_set_remove();
    if (all || test == 9) test2_set_remove();

    if (all || test == 10) test1_set_get_id_at_pos();
    if (all || test == 11) test2_set_get_id_at_pos();
    if (all || test == 12) test3_set_get_id_at_pos();

    if (all || test == 13) test1_set_find();
    if (all || test == 14) test2_set_find();
    if (all || test == 15) test3_set_find();

    if (all || test == 16) test1_set_is_full();
    if (all || test == 17) test2_set_is_full();
    if (all || test == 18) test3_set_is_full();

    if (all || test == 19) test1_set_get_num_ids();
    if (all || test == 20) test2_set_get_num_ids();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_set_create() {
    Set *s = NULL;
    s = set_create();
    PRINT_TEST_RESULT(s != NULL);
    set_destroy(s);
}

void test2_set_create() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, NO_ID) == FALSE);
    set_destroy(s);
}

void test1_set_destroy() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_destroy(s) == OK);
}

void test2_set_destroy() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_destroy(s) == ERROR);
}

void test1_set_add() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_add(s, 1) == OK);
    set_destroy(s);
}

void test2_set_add() {
    int i = 0;
    Set *s = set_create();

    for(i=0; i<SET_MX_CAP; i++)
    set_add(s, i);

    PRINT_TEST_RESULT(set_add(s, 5) == ERROR);
    set_destroy(s);
}

void test3_set_add() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_find(s, 1) == TRUE);
    set_destroy(s);
}

void test1_set_remove() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_remove(s, 1) == OK);
    set_destroy(s);
}

void test2_set_remove() {
    Set *s = set_create();
    set_add(s, 1);
    set_remove(s, 1);
    PRINT_TEST_RESULT(set_find(s, 1) == FALSE); /* Id should not be found */
    set_destroy(s);
}

void test1_set_get_id_at_pos() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_get_id_at_pos(s, 0) == 1);
    set_destroy(s);
}

void test2_set_get_id_at_pos() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_get_id_at_pos(s, -1) == NO_ID); /* Invalid position */
    set_destroy(s);
}

void test3_set_get_id_at_pos() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_get_id_at_pos(s, 0) == NO_ID);
}

void test1_set_find() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_find(s, 1) == TRUE);
    set_destroy(s);
}

void test2_set_find() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, 1) == FALSE); /* Id not found */
    set_destroy(s);
}

void test3_set_find() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_find(s, 1) == FALSE);
}

void test1_set_is_full() {
    int i = 0;
    
    Set *s = set_create();

    for(i=0; i<SET_MX_CAP; i++)
    set_add(s, i);

    PRINT_TEST_RESULT(set_is_full(s) == TRUE);
    set_destroy(s);
}

void test2_set_is_full() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_is_full(s) == FALSE);
    set_destroy(s);
}

void test3_set_is_full() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_is_full(s) == TRUE);
}

void test1_set_get_num_ids() {
    Set *s = set_create();
    set_add(s, 1);
    PRINT_TEST_RESULT(set_get_num_ids(s) == 1);
    set_destroy(s);
}

void test2_set_get_num_ids() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_get_num_ids(s) == -1);
}