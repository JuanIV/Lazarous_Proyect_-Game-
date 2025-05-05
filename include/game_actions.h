/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "game.h"
#include "types.h"

/**
 * @brief Defines the range of results you can get when attacking an enemy
 *
 */
#define ATK_RNG 100

/**
 * @brief Defines the minimum number you have to get to land an attack
 *
 */
#define ATK_WIN 20

/**
 * @brief Defines the range of results for an accident to happen
 * 
 */
#define ATK_ACC_RNG 1000

/**
 * @brief Defines the minimum number you have to get for an accident to happen while attacking
 * 
 */
#define ATK_ACCIDENT 950

/**
 * @brief Base damage that a player deals when attacking
 * 
 */
#define PLY_BASE_DMG 5

/**
 * @brief Sets a given command as last command and executes its corresponding
 * action
 * @author Profesores PPROG
 *
 * @param game double pointer to the game
 * @param cmd command of the desired action
 * @param cmd_code the code of the command entered
 * @return ERROR if there is any mistake while executing the action or setting
 * the last command, OK if everything goes well
 */
Status game_actions_update(Game **game, Command *cmd, CommandCode *cmd_code);

#endif
