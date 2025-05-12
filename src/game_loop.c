/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_management.h"
#include "graphic_engine.h"
#include "game_rules.h"

/**
 * @brief initialazes a game loop creating a new game from a file and a new
 * graphic engine
 *
 * @param game pointer to the game
 * @param gengine pointer to the graphic engine
 * @param file_name name of the file with the starting game data
 * @return 0 if the game and graphic engine initialize propertly, 1 if there is
 * any error
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief runs the game by painting the game screen, getting an user input and
 * updating game action
 *
 * @param game double pointer to the game
 * @param gengine pointer to the graphic engine
 * @param log_file the file where the log is going to be printed
 * @param log_implemented 1 if there should be a log 0 if not
 */
void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file, int log_implemented, Bool deterministic);

/**
 * @brief runs an animation from a file by painting the game screen, getting an user input and
 * updating game action
 * 
 * @param game double pointer to the game
 * @param gengine pointer to the graphic engine
 * @param filename name of the file where the imput will be taken from
 */
void game_loop_run_animation (Game **game, Graphic_engine *gengine, char *filename);

/**
 * @brief destroys both the game and the graphic engine
 *
 * @param game game that will be destroyed
 * @param gengine pointer to the graphic engine being destroyed
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief Counts the lines of an animation file
 * 
 * @param filename name of/ path to the file
 * @return name of lines to be read or -1 in case of error
 */
int game_loop_count_lines(char *filename);

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  int log_implemented = 0;
  Bool deterministic = FALSE;
  char filename[WORD_SIZE];
  srand(time(NULL));

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log_filename>] \n", argv[0]);
    return 1;
  }

  if (argc == 4 && strcmp(argv[2], "-l") == 0) {
    strcpy(filename, argv[3]);
    strcat(filename, ".log");
    log_file = fopen(filename, "w");
    if (!log_file) {
        fprintf(stderr, "Error opening the log file.\n");
        return 1;
    }
    log_implemented = 1;
  }

  if (argc == 4 && strcmp(argv[2], "-d") == 0) {
    deterministic = TRUE;
  }

  if (argc == 5 && 
    ((strcmp(argv[2], "-d") == 0 && strcmp(argv[3], "-l") == 0) || 
     (strcmp(argv[3], "-d") == 0 && strcmp(argv[2], "-l") == 0))) {
    
    strcpy(filename, argv[4]);
    strcat(filename, ".log");
    log_file = fopen(filename, "w");
    if (!log_file) {
        fprintf(stderr, "Error opening the log file.\n");
        return 1;
    }
    deterministic = TRUE;
    log_implemented = 1;
  }

  if (!(game = game_create())) {
    if (log_file) fclose(log_file);
    return -1;
  }

  if (!game_loop_init(game, &gengine, argv[1])) {
    game_loop_run(&game, gengine, log_file, log_implemented, deterministic);
    game_loop_cleanup(game, gengine);
  }

  if (log_file) fclose(log_file);

  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    fprintf(stderr, "Error while initializing game.\n");
    game_destroy(game);
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

int game_loop_count_lines(char *filename) {
  FILE *file = NULL;
  int count = 0;
  char msg[MESG_SIZE + 1];

  if (!(file = fopen(filename, "r"))) return -1;

  while(fgets(msg, MESG_SIZE, file)) count++;

  fclose(file);

  return count;
}

void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file, int log_implemented, Bool deterministic) {
  Command *last_cmd = NULL;
  CommandCode last_cmd_code = NO_CMD;
  Status last_status = ERROR;
  char last_desc[WORD_SIZE + 1], path[WORD_SIZE + 1] = "", aux_path[WORD_SIZE + 1] = "";
  Player *player = NULL;
  Screen printed_screen = NO_SCREEN;
  int turn;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Id id_player;
  Bool update_ga = FALSE, update_turn = FALSE;

  if (!gengine) return;

  if (game_get_finished(*game) == TRUE) return;

  if (game_rules_check_start(*game) == ERROR) {
    fprintf(stdout, "The data file does not comply with the requirements\n");
    return;
  }

  if(deterministic == TRUE) game_set_deterministic(*game, deterministic);
  
  graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));

  do {
    if (last_cmd_code == LOAD) {
      if (game_rules_check_start(*game) == ERROR) {
        fprintf(stdout, "The data file does not comply with the requirements\n");
        return;
      }
    }

    if (game_rules_get_animation(*game, path) == TRUE) {
      if (strcmp(path, aux_path) != 0) {
        strcpy(aux_path, path);
        game_loop_run_animation(game, gengine, path);
        continue;
      }
    }

    if (last_cmd_code == INSPECT) {
      if(game_erase_all_messages(*game) == ERROR) return;
    }

    last_cmd = game_get_last_command_at_pos(*game, NUM_CMDS - 1);

    if (game_set_last_command(*game, last_cmd) == ERROR) return;
    if (command_get_user_input(last_cmd, stdin) == ERROR) return;

    player = game_get_player(*game);
    if (!player) return;

    /*Updating the actions af states of multiple assets*/
    if(game_rules_update_actions(*game, &update_ga) == ERROR) return;
    printf("%d", update_ga);
    if(game_actions_update(game, last_cmd, &last_cmd_code, update_ga) == ERROR) return;
    if(game_rules_update_states_after_action(*game) == ERROR) return;

    /*If the LOG is enabled it prints the last action and status*/
    if (log_implemented == 1 && log_file) {
      last_status = game_get_last_status(*game);
      strcpy(last_desc, command_get_desc(last_cmd));
      turn =game_get_turn(*game);
      if (turn < 0) return;
      player = game_get_player(*game);
      if (!player) return;
      id_player = player_get_id(player);
      if (id_player == NO_ID) return;

      if (last_desc[0] != '\0') {
        if (last_status == OK) {
          fprintf(log_file, "%s %s: OK (P%ld)\n",cmd_to_str[last_cmd_code - NO_CMD][CMDL], last_desc, id_player);
        } else {
          fprintf(log_file, "%s %s: ERROR (P%ld)\n",cmd_to_str[last_cmd_code - NO_CMD][CMDL], last_desc, id_player);
        }
      } else {
        if (last_status == OK) {
          fprintf(log_file, "%s: OK (P%ld)\n",cmd_to_str[last_cmd_code - NO_CMD][CMDL], id_player);
        } else {
          fprintf(log_file, "%s: ERROR (P%ld)\n",cmd_to_str[last_cmd_code - NO_CMD][CMDL], id_player);
        }
      }
    }

    if (last_cmd_code == LOAD) {
      graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
      continue;
    }

    if (game_rules_update_turn(*game, &update_turn) == ERROR) break;
    if ((printed_screen = game_rules_get_screen(*game)) == NO_SCREEN) break;

    if (update_turn == TRUE) {
      if (last_cmd_code != EXIT) 
      if ((last_cmd_code != EXIT) && (last_cmd_code != SKIP)) {
        graphic_engine_paint_game(gengine, *game, printed_screen);
        sleep(1);
      }
      game_next_turn(*game);
      graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
      if (last_cmd_code == SKIP) graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
    } else {
      graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
      if ((((last_cmd_code == CHAT) || (last_cmd_code == INSPECT) || (last_cmd_code == VIEW))) && 
        (command_get_status(last_cmd) == OK)) {
      }
    }

  } while ((last_cmd_code != EXIT) && (game_get_finished(*game) == FALSE));
}

void game_loop_run_animation (Game **game, Graphic_engine *gengine, char *filename) {
  Command *last_cmd;
  CommandCode last_cmd_code = NO_CMD;
  Player *player2 = NULL;
  FILE *file = NULL;
  int lines, i = 0, j = 0;
  long file_pos = 0;
  char line[MESG_SIZE + 1], *msg = NULL, *tok = NULL, *closeup = NULL;
  Id sender_id = NO_ID;
  Bool update_turn = FALSE;
  Type sender_type = NO_TYPE;

  if ((lines = game_loop_count_lines(filename)) == -1) return;
  
  if (!(file = fopen(filename, "r"))) return;

  for (i = 0; (i < lines) && (last_cmd_code != EXIT) &&(game_get_finished(*game) == FALSE); i++) {
    /* We store the position of the previous read. If the read line is not a message,
    we go back and execute it as a player command*/
    file_pos = ftell(file);
    if(!fgets(line, MESG_SIZE, file)) break;

    if (strncmp(line, "#msg:", 5) == 0) {
      if(!(tok = strtok(line + 5, "|"))) break;
      sender_type = (Type) atoi (tok);
      if(!(tok = strtok(NULL, "|"))) break;
      sender_id = (Id) atol (tok);
      if(!(tok = strtok(NULL, "|"))) break;
      msg = tok;

      if (!(player2 = game_get_player_from_id(*game, sender_id))) break;
      game_set_last_message_at_pos_with_info(*game, game_get_turn(*game), msg, sender_id, sender_type);
      if ((sender_type == PLAYER) || (sender_type == THOUGHTS)) {
        for (j = 0; j < POV_HGHT; j++) {
          if(!(closeup = player_get_closeup_at(player2, j))) break;
          game_set_last_close_up(*game, closeup, j);
        }
      }

      graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
      sleep(2);

    } else {
      if (!(last_cmd = game_get_last_command_at_pos(*game, NUM_CMDS - 1))) break;
      if (game_set_last_command(*game, last_cmd) == ERROR) break;

      fseek(file, file_pos, SEEK_SET);
      if (command_get_user_input(last_cmd, file) == ERROR) break;

      if(game_actions_update(game, last_cmd, &last_cmd_code, TRUE) == ERROR) break;
      if(game_rules_update_states_after_action(*game) == ERROR) break;

      if (last_cmd_code == LOAD) continue;

      if (game_rules_update_turn(*game, &update_turn) == ERROR) break;

      if (update_turn == TRUE) {
        if ((last_cmd_code != EXIT) && (last_cmd_code != SKIP)) {
          graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
          sleep(1);
          /*graphic_engine_paint_game(gengine, *game, INTERTURN);
          sleep(3);*/
        }
        game_next_turn(*game);
      } else {
        graphic_engine_paint_game(gengine, *game, game_rules_get_screen(*game));
        if ((((last_cmd_code == CHAT) || (last_cmd_code == INSPECT) || (last_cmd_code == VIEW))) && 
          (command_get_status(last_cmd) == OK)) {
          sleep(3);
        } else sleep(1);
      }
    }

  }
  


  fclose(file);
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
