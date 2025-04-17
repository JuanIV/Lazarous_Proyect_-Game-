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
 * @param gengine pointer to the graphic engine
 * @param log_file the file where the log is going to be printed
 * @param log_implemented 1 if there should be a log 0 if not
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file, int log_implemented);

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
  FILE *log_file = NULL, *load_file = NULL;
  int log_implemented = 0, load_implemented = 0;
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

  if (argc == 4 && strcmp(argv[2], "-lo") == 0) {
    strcpy(filename, argv[3]);
    strcat(filename, ".dat");
    load_file = fopen(filename, "r");
    if (!load_file) {
      fprintf(stderr, "Error opening the saved file.\n");
      return 1;
    }
    load_implemented = 1;
  }

  if ((game = game_create()) == NULL) {
    if (log_file) fclose(log_file);
    if (load_file) fclose(load_file);
    return -1;
  }

  if (load_implemented == 1) {
    if (!game_loop_init(game, &gengine, filename)) {
      game_loop_run(game, gengine, log_file, log_implemented);
      game_loop_cleanup(game, gengine);
    }
  }
  else {
    if (!game_loop_init(game, &gengine, argv[1])) {
      game_loop_run(game, gengine, log_file, log_implemented);
      game_loop_cleanup(game, gengine);
    }
  }

  if (log_file) fclose(log_file);
  if (load_file) fclose(load_file);

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

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file, int log_implemented) {
  Command *last_cmd;
  CommandCode last_cmd_code;
  Status last_status;
  char last_desc[WORD_SIZE];
  Player *player = NULL;
  char *name = NULL, message[MESG_SIZE], save_file[WORD_SIZE];
  int turn;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  if (!gengine) return;

  if (game_get_finished(game) == TRUE) return;
  message[0] = '\0';

  do {
    graphic_engine_paint_game(gengine, game);

    last_cmd = game_get_last_command_at_pos(game, NUM_CMDS - 1);

    if (game_set_last_command(game, last_cmd) == ERROR) return;
    command_get_user_input(last_cmd);

    player = game_get_player(game);
    if (!player) return;
    if (player_get_health(player) <= 0) return;

    game_actions_update(game, last_cmd);

    if (player_get_health(player) <= 0) {
      name = player_get_name(player);
      if (!name) return;
      turn = game_get_turn(game) + 1;
      if (turn == 0) return;
      sprintf(message, "Heaven or hell? What will my future       depare%36sSadly Player %d: %s passed away           End of the game", "", turn, name);
      game_set_last_message(game, message);
      graphic_engine_paint_game(gengine, game);
      return;
    }
    /*If the LOG is enabled it prints the last action and status*/
    if (log_implemented == 1 && log_file) {
      last_cmd_code = command_get_code(last_cmd);
      if (last_cmd_code == NO_CMD) return;
      last_status = game_get_last_status(game);
      strcpy(last_desc, command_get_desc(last_cmd));
      if (last_desc[0] != '\0') {
        if (last_status == OK) {
          fprintf(log_file, "%s (%s): OK\n", cmd_to_str[last_cmd_code - NO_CMD][CMDL], last_desc);
        } else {
          fprintf(log_file, "%s (%s): ERROR\n", cmd_to_str[last_cmd_code - NO_CMD][CMDL], last_desc);
        }
      } else {
        if (last_status == OK) {
          fprintf(log_file, "%s: OK\n", cmd_to_str[last_cmd_code - NO_CMD][CMDL]);
        } else {
          fprintf(log_file, "%s: ERROR\n", cmd_to_str[last_cmd_code - NO_CMD][CMDL]);
        }
      }
    }

    if (command_get_code(last_cmd) == SAVE) {
      strcpy(save_file, command_get_desc(last_cmd));
      strcat(save_file, ".dat");
      if (game_save(game, save_file) == ERROR) return;
      sprintf(message, "Game saved in %s", save_file);
      game_set_last_message(game, message);
    }

    if (game_get_n_players(game) > 1) {
      graphic_engine_paint_game(gengine, game);
      if (command_get_code(last_cmd) != EXIT) sleep(3);
      /*We pass to the next turn*/
      game_next_turn(game);
    }

  } while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE));
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}
