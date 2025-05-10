/**
 * @brief It defines the game rules module interface
 *
 * @file game_rules.h
 * @author Tiago Oselka
 * @version 0
 * @date 02-05-2025
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"
#include "types.h"

/**
 * @brief Runs all the needed game rules BEFORE player's action has been updated this turn
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_run(Game *game);

/**
 * @brief Function that gets if the game actions should be updated
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @param bool Boolean value whose value is updated to true if the game actions
 * should be updated
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_update_actions(Game *game, Bool *bool);

/**
 * @brief Function that gets if the turn should be updated
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @param bool Boolean value whose value is updated to true if the turn should
 * be updated
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_update_turn(Game *game, Bool *bool);

/**
 * @brief Gets what should be printed in the map region of the graphic engine
 * depending on the state of the game
 * 
 * @param game Pointer to the game
 * @return The information that should be printed 
 */
Screen game_rules_get_screen (Game *game);

/**
 * @brief Does all the checkings necessary and the respective responses AFTER player's action has been updated this turn
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_update_states_after_action(Game *game);

#endif