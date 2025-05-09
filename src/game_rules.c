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
 #include <strings.h>

 /* Declaration of private functions */

 /**
  * @brief Forces the cooperation between players in the first round
  * @author Tiago Oselka
  * 
  * @param game Pointer to the game
  * @param bool Pointer to a boolean that represents whether the game actions update
  * should be updated
  * @return OK if everything went well and ERROR otherwise 
  */
 Status game_rules_force_cooperation (Game *game, Bool *bool);

 /**
  * @brief Move only updates the turn if the rooms are not connected
  * @author Tiago Oselka
  * 
  * @param game Pointer to the game
  * @param bool Pointer to a boolean that represents whether the turn should be updated
  * @return OK if everything went well and ERROR otherwise  
  */
 Status game_rules_connected_move (Game *game, Bool *bool);


 Status game_rules_connected_move (Game *game, Bool *bool) {
  char *desc = NULL;
  Command *cmd = NULL;
  Direction dir = UNK_DIR, opp_dir;
  Id cur_loc = NO_ID, prev_loc = NO_ID;
  Link *link = NULL;
  Bool connected = FALSE;
  extern char *dir_to_str[N_DIR][N_DIRT];
  int i = 0;

  if (!game || !bool) return ERROR;
  if (!(cmd = game_get_last_command_at_pos(game,0))) return ERROR;
  if (!(desc = command_get_desc(cmd))) {
    *bool = FALSE;
    return ERROR;
  }

  if(desc[0] == '\0') {
    *bool = FALSE;
    return OK;
  }

  /* compares the command description to any known directions */
  while(dir == UNK_DIR && i < N_DIR) {
    if(!strcasecmp(desc, dir_to_str[i][DIRS]) || 
       !strcasecmp(desc, dir_to_str[i][DIRL])) {
      dir = i + UNK_DIR;
    }else {
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

  if ((cur_loc = player_get_location(game_get_player(game))) == NO_ID) return ERROR;

  if ((prev_loc = game_get_connection(game, cur_loc, opp_dir)) == NO_ID) {
    *bool = TRUE;
    return OK;
  }

  if(!(link = game_get_link(game, prev_loc, dir))) {
    *bool = TRUE;
    return OK;
  }

  if(link_get_connected(link, &connected) == ERROR) return ERROR;

  if(connected == TRUE) {
    *bool = FALSE;
    return OK;
  }

  *bool = TRUE;

  return OK;  
 }

Status game_rules_force_cooperation (Game *game, Bool *bool) {
  Player *play1 = NULL, *play2 = NULL;
  Command *last_cmd;
  CommandCode code;
  int turn = 0;

  if ((turn = game_get_turn(game)) == -1) return ERROR;
  if (!(last_cmd = game_get_last_command(game))) return ERROR;
  if ((code = command_get_code(last_cmd)) == NO_CMD) return ERROR;

  switch (turn) {
  case 0:
    if(!(play1 = game_get_player_from_id(game, 1)) || !(play2 = game_get_player_from_id(game, 4))) return ERROR;
    if(player_get_role(play1) == TEAM1) {
      *bool = TRUE;
      return OK;
    } else if(code == COOPERATE || code == EXIT) {
      *bool = TRUE;
      return OK;
    } else {
      game_set_last_message_at_pos_with_info(game, turn, "We need to cooperate! @Suggested command: cooperate Sg.Rourke", 4, PLAYER);
      *bool = FALSE;
      return OK;
    }
    break;
  case 1:
  if(!(play1 = game_get_player_from_id(game, 2)) || !(play2 = game_get_player_from_id(game, 3))) return ERROR;
    if(player_get_role(play1) == TEAM2) {
      *bool = TRUE;
      return OK;
    } else if(code == COOPERATE || code == EXIT) {
      *bool = TRUE;
      return OK;
    } else {
      game_set_last_message_at_pos_with_info(game, turn, "We need to cooperate! @Suggested command: cooperate Kyle", 4, PLAYER);
      *bool = FALSE;
      return OK;
    }
    break;
  case 2:
    if(!(play1 = game_get_player_from_id(game, 2)) || !(play2 = game_get_player_from_id(game, 3))) return ERROR;
    if(player_get_role(play2) == TEAM2) {
      *bool = TRUE;
      return OK;
    } else if(code == ACCEPT || code == EXIT) {
      *bool = TRUE;
      return player_set_role(play2, TEAM2);
    } else {
      game_set_last_message_at_pos_with_info(game, turn, "Let's stick together! @Suggested command: Accept", 4, PLAYER);
      *bool = FALSE;
      return OK;
    }
    break;
  case 3:
    if(!(play1 = game_get_player_from_id(game, 1)) || !(play2 = game_get_player_from_id(game, 4))) return ERROR;
    if(player_get_role(play2) == TEAM1) {
      *bool = TRUE;
      return OK;
    } else if(code == ACCEPT || code == EXIT) {
      *bool = TRUE;
      return player_set_role(play2, TEAM1);
    } else {
      game_set_last_message_at_pos_with_info(game, turn, "Let's stick together! @Suggested command: Accept", 4, PLAYER);
      *bool = FALSE;
      return OK;
    }
    break;
  default:
    break;
  }

  return OK;
}


 /* Implementation of private functions */


Status game_rules_update_actions (Game *game, Bool *bool) {
  Id player_loc;
  int round = 0, turn = 0;

  if(!game || !bool) return ERROR;

  if ((round = game_get_round(game)) == -1) return ERROR;
  if ((turn = game_get_turn(game)) == -1) return ERROR;

  if (round == 0) return game_rules_force_cooperation(game, bool);

  if ((player_loc = game_get_player_location(game)) == NO_ID) return ERROR;

  return OK;
}
 
Status game_rules_update_turn (Game *game, Bool *bool) {
  Command *cmd = NULL;
  CommandCode code;

  if(!game || !bool) return ERROR;

  if (!(cmd = game_get_last_command_at_pos(game, 0))) return ERROR;
  if (command_get_status(cmd) == ERROR) {
    *bool = FALSE;
    return OK;
  }

  if ((code = command_get_code(cmd)) == NO_CMD) return ERROR;
  
  switch (code) {
  case MOVE:
    return game_rules_connected_move(game, bool);
    break;

  case EXIT:
    *bool = TRUE;
    return OK;

  default:
    *bool = FALSE;
    return OK;
    break;
  }
  
  return OK;
}

 

 Status game_rules_run(Game *game) { return OK; }