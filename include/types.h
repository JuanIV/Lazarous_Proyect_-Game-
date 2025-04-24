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
 * @brief Size in characters of the visible POV of the player
 * 
 */
#define POV_WDTH 25

/**
 * @brief Size in lines of the visible POV of the player
 * 
 */
#define POV_HGHT 10

/**
 * @brief Defines the value associated as a non existing id
 *
 */
#define NO_ID -1

/**
 * @brief Defines the number of roles in the game
 *
 */
#define N_ROLES 8

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

/**
 * @brief Defines all possible teams. This replaces friendly
 *
 */
typedef enum {
  NO_ROLE = -1, /*We define this as the error role*/
  UNDEFINED,    /*Predefined team*/
  SCIENTIST,    /*Part of the scientists*/
  MONSTER,      /*Part of the monsters*/
  PEACEFUL,     /*Peaceful towards everyone*/
  HOSTILE,      /*Hostile towards everyone*/
  DEFECTOR1,    /*Scientists rebeled against their own*/
  DEFECTOR2     /*Monsters rebeled against their own*/
} Role;


#endif
