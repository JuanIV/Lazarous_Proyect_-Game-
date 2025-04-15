/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief It defines the length for strings in the project
 *
 */
#define WORD_SIZE 1000

/**
 * @brief Defines the value associated as a non existing id
 *
 */
#define NO_ID -1

/**
 * @brief Defines the type Id as a long
 *
 */
typedef long Id;

/**
 * @brief Defines a boolean type of variable with two possible states (True,
 * False)
 *
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief It has two possible states, ERROR or OK, and will be used for checking
 * errors on functions
 *
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Defines all four possible directions
 *
 */
typedef enum { UNK_DIR = -1, N, S, E, W, U, D } Direction;

#endif
