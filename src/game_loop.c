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
 * @param game game struct being used
 * @param gengine double pointer to the graphic engine
 * @param log_file the file where the log is going to be printed
 * @param log_implemented 1 if there should be a log 0 if not
 */
void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file, int log_implemented, Bool deterministic);

/**
 * @brief destroys both the game and the graphic engine
 *
 * @param game game that will be destroyed
 * @param gengine pointer to the graphic engine being destroyed
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

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

void game_loop_run(Game **game, Graphic_engine *gengine, FILE *log_file, int log_implemented, Bool deterministic) {
  Command *last_cmd;
  CommandCode last_cmd_code;
  Status last_status;
  char last_desc[WORD_SIZE];
  Player *player = NULL;
  char *name = NULL, message[MESG_SIZE];
  int turn;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Id id_player;
  Bool update_ga = FALSE, update_turn = FALSE;

  if (!gengine) return;

  if (game_get_finished(*game) == TRUE) return;
  message[0] = '\0';

  if(deterministic == TRUE) game_set_deterministic(*game, deterministic);
  
  do {
    graphic_engine_paint_game(gengine, *game);

    last_cmd = game_get_last_command_at_pos(*game, NUM_CMDS - 1);

    if (game_set_last_command(*game, last_cmd) == ERROR) return;
    if (command_get_user_input(last_cmd) == ERROR) return;

    player = game_get_player(*game);
    if (!player) return;

    if(game_rules_update_actions(*game, &update_ga) == ERROR) return;
    if(game_actions_update(game, last_cmd, &last_cmd_code, update_ga) == ERROR) return;

    if (last_cmd_code == LOAD) continue;

    if (player_get_health(player) <= 0) {
      name = player_get_name(player);
      if (!name) return;
      turn = game_get_turn(*game) + 1;
      if (turn == 0) return;
      sprintf(message, "Heaven or hell? What will my future depare@Sadly Player %d: %s passed away@End of the game", turn, name);
      game_set_last_message(*game, message);
      graphic_engine_paint_game(gengine, *game);
      return;
    }

    /*If the LOG is enabled it prints the last action and status*/
    if (log_implemented == 1 && log_file) {
      last_cmd_code = command_get_code(last_cmd);
      if (last_cmd_code == NO_CMD) return;
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

    if (game_get_n_players(*game) > 1) {
      if(game_rules_update_turn(*game, &update_turn) == ERROR) return;
      if (update_turn == TRUE) {
        graphic_engine_paint_game(gengine, *game);
        if(game_erase_all_messages(*game) == ERROR) return;
        sleep(3);
        game_next_turn(*game);
      }
    }

  } while ((last_cmd_code != EXIT) && (game_get_finished(*game) == FALSE));
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
