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

#include "command.h"
#include "game.h"
#include "character.h"
#include "types.h"

/**
 * @brief Defines the range of results you can get when attacking an enemy
 *
 */
#define ATK_RNG 10

/**
 * @brief Defines the minimum number you have to get to win an attack
 *
 */
#define ATK_WIN 5

/**
 * @brief Sets a given command as last command and executes its corresponding
 * action
 * @author Profesores PPROG
 *
 * @param game pointer to the game
 * @param cmd command of the desired action
 * @return ERROR if there is any mistake while executing the action or setting
 * the last command, OK if everything goes well
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
