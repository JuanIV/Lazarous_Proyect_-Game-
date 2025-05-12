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
* @brief Defines the movement of the characters
* @author Juan Ibáñez
* 
* @param game Pointer to the game
* @return OK, if everything goes well or ERROR if there was some mistake
*/
Status game_rules_enemies_move(Game *game);

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
 * @brief Gets the animation that needs to be printed at any given moment
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param path A string where the relative path to the animation will be stored 
 * @return TRUE if an animation is shown, FALSE otherwise
 */
Bool game_rules_get_animation(Game *game, char *path);

/**
 * @brief Does all the checkings necessary and the respective responses AFTER player's action has been updated this turn
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_rules_update_states_after_action(Game *game);

/**
 * @brief Does all the necessary checkings to see if the game can run 
 * (Check number of players and if their IDs coincide with the ones inside game_rule)
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @return OK, if the game is ready to be started or ERROR otherwise
 */
Status game_rules_check_start(Game *game);

#endif