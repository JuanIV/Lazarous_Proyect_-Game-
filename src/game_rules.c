/**
 * @brief It implements the game rules module
 *
 * @file game_rules.c
 * @author Tiago Oselka
 * @version 0
 * @date 02-05-2025
 * @copyright GNU Public License
 */

#include "game_rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


/**
 * @brief Total number of keys in the game
 * 
 */
#define TOTAL_KEYS 16

/* Declaration of private functions */

/**
 * @brief Forces the cooperation between players in the first round
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @param bool Pointer to a boolean that represents whether the game actions
 * update should be updated
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_force_cooperation(Game *game, Bool *bool);

/**
 * @brief Forces the players to read a note/ inspect an object when it is at a space
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @param bool Pointer to a boolean that represents whether the game actions
 * update should be updated
 * @param id id of the object to be inspected
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_force_inspection(Game *game, Bool *bool, Id id);


/**
 * @brief Move only updates the turn if the rooms are not connected
 * @author Tiago Oselka
 *
 * @param game Pointer to the game
 * @param bool Pointer to a boolean that represents whether the turn should be
 * updated
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_connected_move(Game *game, Bool *bool);

/**
 * @brief Attack only updates the turn if you are attacking a player
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param bool Pointer to a boolean that represents whether the turn should be
 * updated
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_attacked_player(Game *game, Bool *bool);

/**
 * @brief Defines the functionallity of switch A from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_A_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch B from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_B_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch C from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_C_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch D from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_D_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch E from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_E_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch F from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_F_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch G from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_G_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch East from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_East_level_2(Game *game);

/**
 * @brief Defines the functionallity of switch West from level 2
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_West_level_2(Game *game);

/**
 * @brief Defines the functionallity of the switch on level 4
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_level_4(Game *game);

/**
 * @brief Defines the functionallity of switch A from level 7
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_A_level_7(Game *game);

/**
 * @brief Defines the functionallity of switch B from level 7
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_B_level_7(Game *game);

/**
 * @brief Defines the functionallity of switch C from level 7
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_C_level_7(Game *game);

/**
 * @brief Defines the functionallity of switch D from level 7
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_switch_D_level_7(Game *game);

/**
 * @brief Defines the way of completing the pressure plates puzzle
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_plates_puzzle(Game *game);

/**
 * @brief Defines the way of completing the balance puzzle
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_balance_puzzle(Game *game);

/**
 * @brief Errases unnecesary keys that have already been used
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_errase_used_keys(Game *game);

/**
 * @brief Defines the functionallity of the alchemy stand
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_alchemy_stand(Game *game);

/**
 * @brief Sets a new objective to a player when he reads a piece of information
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param player_id Id of the player affected
 * @param new_goal New objective for the player
 * @param note_id Id of the note that triggers the change
 */
void game_rules_objective_change_by_note(Game *game, Id player_id, char *new_goal, Id note_id);

/**
 * @brief Sets a new objective to a player when he reaches a certain location
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param player_id Id of the player affected
 * @param location Id of the space in whic the objective will change
 * @param new_goal New objective for the player
 */
void game_rules_objective_change_by_location(Game *game, Id player_id, Id location, char *new_goal);

/**
 * @brief Sets a new objective to a player when he obtains a certain object
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param player_id Id of the player affected
 * @param obj_id Id of the object that will trigger the change
 * @param new_goal New objective for the player
 */
void game_rules_objective_change_by_object(Game *game, Id player_id, Id obj_id, char *new_goal);

/**
 * @brief Defines the conditions for Alaric to win the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_win_condition_Alaric(Game *game);

/**
 * @brief Defines the conditions for Brannon to win the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_win_condition_Brannon(Game *game);

/**
 * @brief Defines the conditions for Kyle to win the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_win_condition_Kyle(Game *game);

/**
 * @brief Defines the conditions for Rourke to win the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return OK if everything went well and ERROR otherwise
 */
Status game_rules_win_condition_Rourke(Game *game);


/**
 * ********************************   SWITCHES AND PUZZLES   ***********************************
*/

Status game_rules_switch_A_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6201);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2016, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2015, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2015, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2014, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2016, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2015, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 2015, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2014, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_B_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6202);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2014, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 2009, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2008, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2014, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2009, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2008, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_C_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6203);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2001, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2008, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2002, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2001, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 2008, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2002, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_D_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6204);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2019, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2018, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2020, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2019, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2019, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2018, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 2020, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2019, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_E_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6205);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2011, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2011, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_F_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6206);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2020, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2013, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2020, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2013, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_G_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6207);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 2006, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 2006, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_West_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6208);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/

  } else {    /*Switch is on*/
    link = game_get_link(game, 2016, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2015, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2015, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2014, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2014, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2009, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2008, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2001, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2007, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2008, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2002, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_East_level_2(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6209);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/

  } else {    /*Switch is on*/
    link = game_get_link(game, 2019, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2018, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2020, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2019, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2011, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2020, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2013, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 2006, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 2005, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

  }
  return OK;
}

Status game_rules_switch_level_4(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6401);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 4018, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 4025, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 4018, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 4025, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_A_level_7(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6701);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 7031, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7030, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7030, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7020, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 7031, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7030, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7030, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7020, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_B_level_7(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6702);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 7022, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7021, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7021, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7011, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 7022, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7021, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7021, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7011, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_C_level_7(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6703);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 7013, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7012, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7012, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7004, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 7013, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7012, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7012, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7004, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_switch_D_level_7(Game *game){
  Object *obj = NULL;
  Link *link = NULL;
  int state = -1;

  if(!game) return ERROR;

  obj = game_get_object(game, 6704);

  state = object_get_use_value(obj);
  if(state == -1) return ERROR;

  if(!state){ /*Switch is off*/
    link = game_get_link(game, 7014, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7013, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7023, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7022, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7032, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7031, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7006, S);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7014, N);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

    link = game_get_link(game, 7044, W);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;
    link = game_get_link(game, 7043, E);
    if(link_set_open(link, FALSE) == ERROR) return ERROR;

  } else {    /*Switch is on*/
    link = game_get_link(game, 7014, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7013, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7023, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7022, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7032, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7031, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7006, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7014, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7044, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7043, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }
  return OK;
}

Status game_rules_plates_puzzle(Game *game){
  Player *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL;
  Id loc[4];
  Bool pressed[4] = {FALSE, FALSE, FALSE, FALSE};
  Link *link = NULL;
  int i=0;

  if(!game)return ERROR;

  p1 = game_get_player_from_id(game, 1);
  p2 = game_get_player_from_id(game, 2);
  p3 = game_get_player_from_id(game, 3);
  p4 = game_get_player_from_id(game, 4);

  if(!p1 | !p2 | !p3 | !p4) return ERROR;

  loc[0] = player_get_location(p1);
  loc[1] = player_get_location(p2);
  loc[2] = player_get_location(p3);
  loc[3] = player_get_location(p4);

  for(i=0;i<4;i++) if(loc[i]==7007) pressed[0] = TRUE;
  for(i=0;i<4;i++) if(loc[i]==7009) pressed[1] = TRUE;
  for(i=0;i<4;i++) if(loc[i]==7015) pressed[2] = TRUE;
  for(i=0;i<4;i++) if(loc[i]==7017) pressed[3] = TRUE;

  if(pressed[0] && pressed[1] && pressed[2] && pressed[3]){
    link = game_get_link(game, 7008, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7001, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7027, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7018, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }

  return OK;
}

Status game_rules_balance_puzzle(Game *game){
  Player *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL;
  Id loc[4];
  Bool activated = TRUE;
  Link *link = NULL;
  int i=0;

  if(!game)return ERROR;

  p1 = game_get_player_from_id(game, 1);
  p2 = game_get_player_from_id(game, 2);
  p3 = game_get_player_from_id(game, 3);
  p4 = game_get_player_from_id(game, 4);

  if(!p1 | !p2 | !p3 | !p4) return ERROR;

  loc[0] = player_get_location(p1);
  loc[1] = player_get_location(p2);
  loc[2] = player_get_location(p3);
  loc[3] = player_get_location(p4);

  for(i=0;i<4;i++) if(loc[i] != 7054) activated = FALSE;

  if(activated == TRUE){
    link = game_get_link(game, 7051, N);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7041, S);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;

    link = game_get_link(game, 7054, E);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
    link = game_get_link(game, 7055, W);
    if(link_set_open(link, TRUE) == ERROR) return ERROR;
  }

  return OK;
}

Status game_rules_alchemy_stand(Game *game){
  Player *pl[4] = {NULL, NULL, NULL, NULL};
  Object *stand = NULL, *compound1 = NULL, *compound2 = NULL;
  int use_value = -1, i;

  if(!game) return ERROR;

  pl[0] = game_get_player_from_id(game, 1);
  pl[1] = game_get_player_from_id(game, 2);
  pl[2] = game_get_player_from_id(game, 3);
  pl[3] = game_get_player_from_id(game, 4);
  stand = game_get_object(game, 6801);
  compound1 = game_get_object(game, 8001);
  compound2 = game_get_object(game, 8002);

  if(!pl[1] | !pl[2] | !pl[3] | !pl[0] | !stand | !compound1 | !compound2) return ERROR;

  use_value = object_get_use_value(stand);
  if(use_value == -1) return ERROR;

  if(use_value == 1){
    for(i=0;i<4;i++){
      if(player_get_location(pl[i]) == 8003) {
        if(player_has_object(pl[i],object_get_id(compound1)) && player_has_object(pl[i],object_get_id(compound2))){
          if(player_delete_object(pl[i],object_get_id(compound1)) == ERROR) return ERROR;
          if(player_delete_object(pl[i],object_get_id(compound2)) == ERROR) return ERROR;
          if(player_add_object(pl[i],8004) == ERROR) return ERROR;
          game_set_last_message(game, "*Blurp!* The new compound is now in your inventory.");
        }
      }
    }
  }

  if(object_set_use_value(stand, 0)==ERROR)return ERROR;
  return OK;  
}

Status game_rules_cure_Grendel(Game *game){
  Character *gr314 = NULL, *grendel = NULL;
  Id weapon = NO_ID, location = NO_ID;
  Space *current_sp = NULL, *hidden_sp = NULL;

  gr314 = game_get_character_from_id(game, 1601);
  grendel = game_get_character_from_id(game, 1602);
  hidden_sp = game_get_space(game, 11111);

  if(!grendel || !gr314 || !hidden_sp) return ERROR;

  if(character_get_weapon(gr314, &weapon) == ERROR) return ERROR;

  if(weapon == 8003) {
    character_set_following(gr314, NO_ID);
    character_set_weapon(gr314,NO_ID);

    if((location = game_get_character_location(game, 1601)) == NO_ID) return ERROR;
    if(!(current_sp = game_get_space(game, location))) return ERROR;

    space_remove_character(current_sp, 1601);
    space_add_character(hidden_sp, 1601);
    space_remove_character(hidden_sp, 1602);
    space_add_character(current_sp, 1602);

    game_set_last_message_at_pos_with_info(game, game_get_turn(game),"I...I'm human again...",1601,CHARACTER);
  }
  return OK;
}

/**
 * ********************************   OBJECTIVES   ***********************************
*/
void game_rules_objective_change_by_note(Game *game, Id player_id, char *new_goal, Id note_id){
  Command *cmd = NULL;
  Player *pl = NULL;
  char *desc = NULL, *name = NULL, *toks = NULL, *old_goal = NULL;
  Id obj_id = NO_ID;

  if(!game || (player_id == NO_ID) || (!new_goal) || (note_id == NO_ID))return;

  pl = game_get_player(game);
  if(!pl) return;

  if(player_get_id(pl) != player_id) return;

  old_goal = player_get_objective(pl);
  if(!old_goal) return;

  if(old_goal[0] > new_goal[0]) return;

  if (!(cmd = game_get_last_command(game))) return;

  if(command_get_code(cmd)==USE || command_get_code(cmd)==INSPECT){
    if (!(desc = command_get_desc(cmd))) return;

    toks = strtok(desc," \r\n");
    if(!toks) return;
    name = toks;
  
    obj_id = game_get_obj_id_from_name_at_space(game, name, game_get_player_location(game));
    if(obj_id == NO_ID) return;
  
    if(obj_id == note_id){
      if(game_get_last_status(game) == OK) {
        player_set_objective(pl, new_goal); 
      }
    }
  }  
}

void game_rules_objective_change_by_location(Game *game, Id player_id, Id location, char *new_goal){
  Player *pl = NULL;
  char *old_goal = NULL;

  if(!game || player_id == NO_ID || location == NO_ID || !new_goal) return;

  if(!(pl = game_get_player_from_id(game, player_id)))return;

  old_goal = player_get_objective(pl);
  if(!old_goal) return;

  if(old_goal[0] > new_goal[0]) return;

  if(player_get_location(pl) == location){
    if (player_set_objective(pl, new_goal) == ERROR) return;
  }
}

void game_rules_objective_change_by_object(Game *game, Id player_id, Id obj_id, char *new_goal){
  Player *pl = NULL;
  char *old_goal = NULL;

  if(!game || player_id == NO_ID || obj_id == NO_ID || !new_goal) return;

  if(!(pl = game_get_player_from_id(game, player_id)))return;

  old_goal = player_get_objective(pl);
  if(!old_goal) return;

  if(old_goal[0] > new_goal[0]) return;

  if(player_has_object(pl, obj_id) == TRUE){
    if (player_set_objective(pl, new_goal) == ERROR) return;
  }
}

Status game_rules_win_condition_Alaric(Game *game){
  Player *pl[4] = {NULL, NULL, NULL, NULL};
  Space *core = NULL;

  if(!game) return ERROR;

  pl[0] = game_get_player_from_id(game, 1);
  pl[1] = game_get_player_from_id(game, 2);
  pl[2] = game_get_player_from_id(game, 3);
  pl[3] = game_get_player_from_id(game, 4);

  if(!pl[1] | !pl[2] | !pl[3] | !pl[0]) return ERROR;

  core = game_get_space(game, 9006);
  if(!core) return ERROR;

  if(player_get_location(pl[0]) == 9008) game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I can't leave. I have to finish Project Lazarus and bring Evelyn back.",1,PLAYER);


  if(space_find_object(core, 8004)){
    if(player_get_health(pl[1]) <= 0 || player_get_health(pl[1]) <= 0 || player_get_health(pl[1]) <= 0 ){
      game_set_last_message(game, "As soon as Alaric starts the machine the floor starts to shake. A huge beam of light floods the room@As the light simmers down the eyes of death show themselves. @Alaric Wins! Game Over");
      game_set_finished(game, TRUE);
    } else if(player_get_location(pl[0]) == 9008) game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I still need a recently passed cadaver as a bridge between life and death.",1,PLAYER);
  }
  return OK;
}

Status game_rules_win_condition_Brannon(Game *game){
  Player *Brannon = NULL;
  Character *Grendel = NULL;
  Id following = NO_ID;

  if(!game) return ERROR;

  Brannon = game_get_player_from_id(game, 2);
  Grendel = game_get_character_from_id(game, 1602);

  if(!Brannon || !Grendel) return ERROR;

  if(character_get_following(Grendel, &following) == ERROR) return ERROR;

  if(player_get_location(Brannon) == 9008){
    if(following == 2){
      game_set_last_message(game, "Brannon and his son, finally reunited, flee the lab through the inestable tunnels causing the lab to collapse. @Brannon Wins! Game Over");
      game_set_finished(game, TRUE);
    } else {
      if(game_get_turn(game) == 1)
      game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I can't leave without my son",2,PLAYER);
    }
  }
  

  return OK;
}

Status game_rules_win_condition_Rourke(Game *game){
  Player *rourke = NULL;
  Player *alaric = NULL;
  Character *boss = NULL;

  if(!game) return ERROR;

  rourke = game_get_player_from_id(game, 4);
  alaric = game_get_player_from_id(game, 1);
  boss = game_get_character_from_id(game, 2701);

  if((!boss) || (!rourke) || (!alaric)) return ERROR;

  if(player_get_location(rourke) == 9008){
    if(character_get_health(boss) < 0){
      if(player_get_health(alaric) < 0){
        game_set_last_message(game, "Sg. Rourke makes it to the exit of the lab after finally having unveiled the suspects he had been after for years. @Sg.Rourke Wins! Game Over");
        game_set_finished(game, TRUE);
      } else {
        if(game_get_turn(game) == 3)
        game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I must stop Alaric before leaving. Lethal force will be needed.",2,PLAYER);
      }
    } else {
      if(game_get_turn(game) == 3)
      game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I have to kill this monster before leaving. It will be a threat.",2,PLAYER);
    }
  }

  return OK;
}

Status game_rules_win_condition_Kyle(Game *game){
  Player *pl[4] = {NULL, NULL, NULL, NULL};
  Space *core = NULL;

  if(!game) return ERROR;

  pl[0] = game_get_player_from_id(game, 1);
  pl[1] = game_get_player_from_id(game, 2);
  pl[2] = game_get_player_from_id(game, 3);
  pl[3] = game_get_player_from_id(game, 4);

  if(!pl[1] | !pl[2] | !pl[3] | !pl[0]) return ERROR;

  core = game_get_space(game, 9006);
  if(!core) return ERROR;

  if(player_get_location(pl[3]) == 9008) game_set_last_message_at_pos_with_info(game,game_get_turn(game),"I can't leave. I must stop Alaric at any cost.",3,PLAYER);


  if(space_find_object(core, 8004)){
    game_set_last_message(game, "Kyle Reaches the CORE and destroys it along with the rest of the lab succesfully stoping Vexleigh's plan @Kyle Wins! Game Over");
    game_set_finished(game, TRUE);
  }
  return OK;
}






/**
 * ********************************   OTHERS   ***********************************
*/

Status game_rules_errase_used_keys(Game *game){
  Player *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL;
  int i = 0, use_value;
  Object *aux_obj = NULL;
  int keys[TOTAL_KEYS] = {9201,9202,9203,9301,9401,9402,9403,9501,9502,9601,9602,9603,9701,9702,9703,9801};

  if(!game) return ERROR;

  p1 = game_get_player_from_id(game, 1);
  p2 = game_get_player_from_id(game, 2);
  p3 = game_get_player_from_id(game, 3);
  p4 = game_get_player_from_id(game, 4);

  if(!p1 | !p2 | !p3 | !p4) return ERROR;

  for(i=0;i<TOTAL_KEYS;i++){
    aux_obj = game_get_object(game, keys[i]);
    if(!aux_obj) continue;

    use_value = object_get_use_value(aux_obj);
    if(use_value==1){
      if(player_has_object(p1, keys[i])) player_delete_object(p1, keys[i]);
      if(player_has_object(p2, keys[i])) player_delete_object(p2, keys[i]);
      if(player_has_object(p3, keys[i])) player_delete_object(p3, keys[i]);
      if(player_has_object(p4, keys[i])) player_delete_object(p4, keys[i]);
    }
  }
  return OK;
}

/*Defines the movement of the characters*/
Status game_rules_enemies_move(Game *game){
  Character *aux_chr = NULL;
  Id chr_id = NO_ID, loc = NO_ID, destin = NO_ID;
  Space *aux_sp = NULL, *dest_sp = NULL;
  Direction dir = UNK_DIR;
  Bool determ = FALSE, open = FALSE;
  Link *link = NULL;
  Role chr_role = NO_ROLE, use_role = NO_ROLE;
  int i=0, n_chrs = 0;

  if(!game) return ERROR;

  if(game_get_deterministic(game, &determ) == ERROR) return ERROR; 

  n_chrs = game_get_n_characters(game);

  for(i=0;i<n_chrs;i++){
    aux_chr = game_get_character_at_pos(game, i);
    if(!aux_chr) continue;

    chr_id = character_get_id(aux_chr);
    if(chr_id == NO_ID) continue;

    loc = game_get_character_location(game, chr_id);
    if(loc == NO_ID) continue;

    chr_role = character_get_role(aux_chr);
    if(chr_role != MONSTER) continue;

    /*If game is deterministic, characters just spin around*/
    if(determ == TRUE) dir = (game_get_round(game)%4);
    else dir = rand()%4;

    link = game_get_link(game, loc, dir);
    if(!link) continue;

    if(link_get_open(link, &open) == ERROR) continue;
    if(open == FALSE) continue;

    use_role = link_get_use_role(link);
    if(use_role == NO_ROLE) continue;

    if(use_role == UNDEFINED || use_role == chr_role) {
      destin = link_get_dest(link);
      if (destin == NO_ID) continue;

      if (!(dest_sp = game_get_space(game, destin))) continue;

      if (!(aux_sp = game_get_space(game, loc))) continue;

      if (space_remove_character(aux_sp, chr_id) == ERROR) continue;

      if (space_add_character(dest_sp, chr_id) == ERROR) continue;
    }
  }
  return OK;
}

Status game_rules_connected_move(Game *game, Bool *bool) {
  char *desc = NULL;
  Command *cmd = NULL;
  Direction dir = UNK_DIR, opp_dir;
  Id cur_loc = NO_ID, prev_loc = NO_ID;
  Link *link = NULL;
  Bool connected = FALSE;
  extern char *dir_to_str[N_DIR][N_DIRT];
  int i = 0;

  if (!game || !bool) return ERROR;
  if (!(cmd = game_get_last_command_at_pos(game, 0))) return ERROR;
  if (!(desc = command_get_desc(cmd))) {
    *bool = FALSE;
    return ERROR;
  }

  if (desc[0] == '\0') {
    *bool = FALSE;
    return OK;
  }

  /* compares the command description to any known directions */
  while (dir == UNK_DIR && i < N_DIR) {
    if (!strcasecmp(desc, dir_to_str[i][DIRS]) ||
        !strcasecmp(desc, dir_to_str[i][DIRL])) {
      dir = i + UNK_DIR;
    } else {
      i++;
    }
  }

  switch (dir) {
    case N:
      opp_dir = S;
      break;
    case S:
      opp_dir = N;
      break;
    case E:
      opp_dir = W;
      break;
    case W:
      opp_dir = E;
      break;
    default:
      *bool = TRUE;
      return OK;
      break;
  }

  if ((cur_loc = player_get_location(game_get_player(game))) == NO_ID)
    return ERROR;

  if ((prev_loc = game_get_connection(game, cur_loc, opp_dir)) == NO_ID) {
    *bool = TRUE;
    return OK;
  }

  if (!(link = game_get_link(game, prev_loc, dir))) {
    *bool = TRUE;
    return OK;
  }

  if (link_get_connected(link, &connected) == ERROR) return ERROR;

  if (connected == TRUE) {
    *bool = FALSE;
    return OK;
  }

  *bool = TRUE;

  return OK;
}

Status game_rules_attacked_player(Game *game, Bool *bool) {
  char *desc = NULL;
  Command *cmd = NULL;

  if (!game || !bool) return ERROR;
  if (!(cmd = game_get_last_command_at_pos(game, 0))) return ERROR;
  if (!(desc = command_get_desc(cmd))) {
    *bool = FALSE;
    return ERROR;
  }

  if (desc[0] == '\0') {
    *bool = FALSE;
    return OK;
  }

  if(game_get_player_from_name(game, desc)){
    *bool = TRUE;
    return OK;
  }

  *bool = FALSE;
  return OK;
}

Status game_rules_force_cooperation(Game *game, Bool *bool) {
  Player *play1 = NULL, *play2 = NULL;
  Command *last_cmd;
  CommandCode code;
  int turn = 0;

  if ((turn = game_get_turn(game)) == -1) return ERROR;
  if (!(last_cmd = game_get_last_command(game))) return ERROR;
  if ((code = command_get_code(last_cmd)) == NO_CMD) return ERROR;

  if (code == LOAD || code == SAVE || code == EXIT) {
    *bool = TRUE;
    return OK;
  }

  switch (turn) {
    case 0:
      if (!(play1 = game_get_player_from_id(game, 1)) ||
          !(play2 = game_get_player_from_id(game, 4)))
        return ERROR;
      if (player_get_role(play1) == TEAM1) {
        *bool = TRUE;
        return OK;
      } else if (code == COOPERATE) {
        *bool = TRUE;
        return OK;
      } else {
        game_set_last_message_at_pos_with_info(
            game, turn,
            "Wait! We barely know who we even are. We should stay together...@ "
            "Suggested command: cooperate Sg.Rourke @ ",
            4, PLAYER);
        *bool = FALSE;
        return OK;
      }
      break;
    case 1:
      if (!(play1 = game_get_player_from_id(game, 2)) ||
          !(play2 = game_get_player_from_id(game, 3)))
        return ERROR;
      if (player_get_role(play1) == TEAM2) {
        *bool = TRUE;
        return OK;
      } else if (code == COOPERATE) {
        *bool = TRUE;
        return OK;
      } else {
        game_set_last_message_at_pos_with_info(
            game, turn,
            "Wait! We don't know what is out there. Let's stay together.@ "
            "Suggested command: cooperate Kyle@ ",
            3, PLAYER);
        *bool = FALSE;
        return OK;
      }
      break;
    case 2:
      if (!(play1 = game_get_player_from_id(game, 2)) ||
          !(play2 = game_get_player_from_id(game, 3)))
        return ERROR;
      if (player_get_role(play2) == TEAM2) {
        *bool = TRUE;
        return OK;
      } else if (code == ACCEPT) {
        *bool = TRUE;
        return player_set_role(play2, TEAM2);
      } else {
        game_set_last_message_at_pos_with_info(
            game, turn, "Let's stick together! @Suggested command: Accept@ ", 2,
            PLAYER);
        *bool = FALSE;
        return OK;
      }
      break;
    case 3:
      if (!(play1 = game_get_player_from_id(game, 1)) ||
          !(play2 = game_get_player_from_id(game, 4)))
        return ERROR;
      if (player_get_role(play2) == TEAM1) {
        *bool = TRUE;
        return OK;
      } else if (code == ACCEPT) {
        *bool = TRUE;
        return player_set_role(play2, TEAM1);
      } else {
        game_set_last_message_at_pos_with_info(
            game, turn, "Let's stick together! @Suggested command: Accept@ ", 1,
            PLAYER);
        *bool = FALSE;
        return OK;
      }
      break;
    default:
      break;
  }

  return OK;
}

Status game_rules_force_inspection(Game *game, Bool *bool, Id id) {
  Player *player = NULL;
  Space *space = NULL;
  Class *class = NULL;
  Object *obj = NULL;
  Command *last_cmd;
  CommandCode code;
  Id obj_id = NO_ID, loc = NO_ID;
  Bool has_obj = FALSE;
  char *name = NULL, msg[MESG_SIZE] = "";
  int turn = 0, prime, use_value = -1, count = 0;

  if ((turn = game_get_turn(game)) == -1) return ERROR;
  if (!(last_cmd = game_get_last_command(game))) return ERROR;
  if ((code = command_get_code(last_cmd)) == NO_CMD) return ERROR;

  if (code == LOAD || code == SAVE || code == EXIT) {
    *bool = TRUE;
    return OK;
  }

  if (!(player = game_get_player(game))) return ERROR;
  if ((loc = player_get_location(player)) == NO_ID) return ERROR;
  if (!(space = game_get_space(game, loc))) return ERROR;
  if (!(class = game_get_class_from_id_obj(game, id))) return ERROR;
  if (!(obj = game_get_object(game, id))) return ERROR;
  if (((has_obj = player_has_object(player, id)) == FALSE) && (space_find_object(space, id) == FALSE)) {
    *bool = TRUE;
    return OK;
  }
  if ((use_value = object_get_use_value(obj)) == -1) return ERROR;
  if ((prime = game_get_prime_from_id(game, player_get_id(player))) == -1) return ERROR;

  if ((use_value % prime) == 0) {
    *bool = TRUE;
    return OK;
  } else if (code == INSPECT) {
    if (!(name = command_get_desc(last_cmd))) {
      *bool = FALSE;
      return OK;
    }

    obj_id = game_get_obj_id_from_name_at_space(game, name, loc);
    if (obj_id == NO_ID) {
      *bool = FALSE;
      return OK;
    }

    if (obj_id == id) {
      *bool = TRUE;
      return OK;
    }

  } else {
    if (!(name = class_get_name(class))) return ERROR;
    if(has_obj == TRUE) count = sprintf(msg, "What is this that I have?");
    else count = sprintf(msg, "What is this?");

    sprintf(msg + count, "@Suggested command: inspect %s", name);
    game_set_last_message_at_pos_with_info(game, turn, msg, turn + 1, THOUGHTS);
    *bool = FALSE;
    return OK;
  }

  return OK;
}
/* Implementation of private functions */

Screen game_rules_get_screen (Game *game) {
  Command *last_cmd = NULL;
  CommandCode code = NO_CMD;
  Player *player = NULL;

  if (!game) return NO_SCREEN;
  if (!(player = game_get_player(game))) return NO_SCREEN;

  if (player_get_health(player) <= 0) return LOSS;

  if (!(last_cmd = game_get_last_command(game))) return ERROR;
  if ((code = command_get_code(last_cmd)) == NO_CMD) return ERROR;

  switch (code) {
    case VIEW:
      return MINIMAP;
      break;
    case HELP:
      return INSTRUCTIONS;
      break;
    
    default:
      return MAP;
      break;
  }

  return MAP;
}

Status game_rules_update_actions(Game *game, Bool *bool) {
  Id player_loc;
  int round = 0, turn = 0;

  if (!game || !bool) return ERROR;

  if ((round = game_get_round(game)) == -1) return ERROR;
  if ((turn = game_get_turn(game)) == -1) return ERROR;

  if (round == 0) return game_rules_force_cooperation(game, bool);
  /* *bool = TRUE;*/
  if ((player_loc = game_get_player_location(game)) == NO_ID) return ERROR;

  switch (player_loc) {
  case 1006:
    game_rules_force_inspection(game, bool, 5101);
    break;

  case 1003:
    game_rules_force_inspection(game, bool, 5105);
    break;
    
  case 2017:
    game_rules_force_inspection(game, bool, 5203);
    break;

  case 4014:
    game_rules_force_inspection(game, bool, 5401);
    break;

  case 4017:
    game_rules_force_inspection(game, bool, 5402);
    break;

  case 6008:
    game_rules_force_inspection(game, bool, 5601);
    break;

  case 6009:
    game_rules_force_inspection(game, bool, 5602);
    break;

  case 7018:
    game_rules_force_inspection(game, bool, 5703);
    break;

  case 7048:
    game_rules_force_inspection(game, bool, 5704);
    break;

  case 7056:
    game_rules_force_inspection(game, bool, 5706);
    break;

  case 7045:
    game_rules_force_inspection(game, bool, 5705);
    break;

  case 7051:
    game_rules_force_inspection(game, bool, 5707);
    break;
  
  
  default:
    break;
  }

  return OK;
}

Status game_rules_update_turn(Game *game, Bool *bool) {
  Command *cmd = NULL;
  CommandCode code;
  Player *player = NULL;

  if (!game || !bool) return ERROR;

  if (!(cmd = game_get_last_command_at_pos(game, 0))) return ERROR;
  if (command_get_status(cmd) == ERROR) {
    *bool = FALSE;
    return OK;
  }

  if ((code = command_get_code(cmd)) == NO_CMD) return ERROR;
  if (!(player = game_get_player(game))) return ERROR;
  if (player_get_health(player) <= 0) {
    *bool = TRUE;
    return OK;
  }

  /* Enters cases once we know the */
  switch (code) {
    case MOVE:
      return game_rules_connected_move(game, bool);
      break;

    case ATTACK:
      return game_rules_attacked_player(game, bool);
      break;

    case EXIT:
      *bool = TRUE;
      break;

    case SKIP:
      *bool = TRUE;
      break;

    default:
      *bool = FALSE;
      return OK;
      break;
  }

  if ((game_get_turn(game) == TOT_PLAYERS - 1) && (*bool == TRUE)) {
    return game_rules_enemies_move(game);
  }

  return OK;
}

Bool game_rules_get_animation(Game *game, char *path) {
  int turn, round;
  if (!game || !path) return FALSE;

  if ((turn = game_get_turn(game)) == -1) return FALSE;
  if ((round = game_get_round(game)) == -1) return FALSE;

  if (round == 0) {
    switch (turn) {
      case 0:
        strncpy(path, "./anim/animation1.txt" , WORD_SIZE);
        return FALSE;
        break;
      case 1:
        strncpy(path, "./anim/animation2.txt" , WORD_SIZE);
        return FALSE;
        break;
      case 2:
        strncpy(path, "./anim/animation3.txt" , WORD_SIZE);
        return TRUE;
        break;
      case 3:
        strncpy(path, "./anim/animation4.txt" , WORD_SIZE);
        return TRUE;
        break;
      
      
      default:
        break;
    }
  }

  return FALSE;
}

Status game_rules_update_states_after_action(Game *game){
  Status st = OK;

  /*Update switches*/
  if(game_rules_switch_A_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_B_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_C_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_D_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_E_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_F_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_G_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_West_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_East_level_2(game) == ERROR) st = ERROR;
  if(game_rules_switch_level_4(game) == ERROR) st = ERROR;
  if(game_rules_switch_A_level_7(game) == ERROR) st = ERROR;
  if(game_rules_switch_B_level_7(game) == ERROR) st = ERROR;
  if(game_rules_switch_C_level_7(game) == ERROR) st = ERROR;
  if(game_rules_switch_D_level_7(game) == ERROR) st = ERROR;

  if(game_rules_alchemy_stand(game) == ERROR) st = ERROR;

  /*Update puzzles*/
  if(game_rules_plates_puzzle(game) == ERROR) st = ERROR;
  if(game_rules_balance_puzzle(game) == ERROR) st = ERROR;

  /*Other checkings*/
  if(game_rules_errase_used_keys(game) == ERROR) st = ERROR;
  if(game_rules_cure_Grendel(game) == ERROR) st = ERROR;

  /*Objectives*/
  game_rules_objective_change_by_note(game, 1, "1Head to level 3 for suplies", 5103);
  game_rules_objective_change_by_note(game, 2, "1Head to level 3 for suplies", 5103);
  game_rules_objective_change_by_note(game, 3, "1Head to level 3 for suplies", 5103);
  game_rules_objective_change_by_note(game, 4, "1Head to level 3 for suplies", 5103);

  game_rules_objective_change_by_location(game, 1, 3001, "2Investigate the lab further");
  game_rules_objective_change_by_location(game, 2, 3001, "2Investigate the lab further");
  game_rules_objective_change_by_location(game, 3, 3001, "2Investigate the lab further");
  game_rules_objective_change_by_location(game, 4, 3001, "2Investigate the lab further");

  game_rules_objective_change_by_note(game, 1, "3...", 5703);
  game_rules_objective_change_by_note(game, 1, "4Finish Project Lazarus@Don't let Kyle intervene@Get a corpse (kill a player)@Take Eve-9 from lvl 8@and pour it the CORE", 5707);

  game_rules_objective_change_by_note(game, 2, "3Find your lost son", 5601);
  game_rules_objective_change_by_note(game, 2, "4Get the key to cell 6005@and the cure to mutation@at the storage on level 8", 5705);
  game_rules_objective_change_by_object(game, 2, 9801, "5Rescue Grendel at lvl 6");
  game_rules_objective_change_by_location(game, 2, 6005, "6Cure Grendel and scape@the lab with him");

  game_rules_objective_change_by_note(game, 3, "3...", 5602);
  game_rules_objective_change_by_note(game, 3, "4Stop Alaric.@Make a corrosive solution@and destroy the lab", 5706);
  game_rules_objective_change_by_note(game, 3, "5Get Vexite_Nitrate and @FerroSilicate_Gel from the @storage and mix them at the@Alchemy Stand", 5801);
  game_rules_objective_change_by_object(game, 3, 8004, "6Pour the corrosive solution@to the CORE");

  game_rules_objective_change_by_note(game, 4, "3Find out what is going@ on at the lab", 5402);
  game_rules_objective_change_by_note(game, 4, "4Find the people responsable", 5703);
  game_rules_objective_change_by_note(game, 4, "5Stop Alaric", 5707);
  game_rules_objective_change_by_location(game, 4, 9001, "6Kill Alaric@Kill S0001 at lvl 9");

  /*Win conditions*/
  if(game_rules_win_condition_Alaric(game) == ERROR) st = ERROR;
  if(game_rules_win_condition_Kyle(game) == ERROR) st = ERROR;
  if(game_rules_win_condition_Brannon(game) == ERROR) st = ERROR;
  if(game_rules_win_condition_Rourke(game) == ERROR) st = ERROR;

  return st;
}