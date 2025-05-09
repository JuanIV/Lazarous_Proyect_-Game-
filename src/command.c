/**
 * @brief It implements the command interpreter.
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
 * @brief Maximum lenght for the input command
 *
 */
#define CMD_LENGHT 500

char *cmd_to_str[N_CMD][N_CMDT] = {
  {"", "No command"}, {"", "Unknown"}, {"e", "exit"},   {"m", "move"},
  {"t", "take"},    {"dr", "drop"},  {"at", "attack"},   {"c", "chat"},
  {"i", "inspect"}, {"r", "recruit"},  {"ab", "abandon"}, {"u", "use"},
  {"s", "save"}, {"lo", "load"},    {"o", "open"},      {"cl", "close"},
  {"ac", "accept"}, {"de", "deny"}, {"co", "cooperate"}, {"b", "betray"}};

/**
 * @brief Struct that stores the information of a command: code, cmd_desc and
 * status
 * @author Tiago Oselka
 *
 */
struct _Command {
  CommandCode code;          /*!< Name of the command */
  char cmd_desc[CMD_LENGHT]; /*!< Information about the command */
  Status status;             /*!< Status of the command: OK if it went well, ERROR otherwise*/
};

/*It creates a new command, allocating memory and initializing its members*/
Command *command_create() {
  Command *newCommand = NULL;

  newCommand = (Command *)malloc(sizeof(Command));
  if (newCommand == NULL) return NULL;

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->status = ERROR;
  newCommand->cmd_desc[0] = '\0';

  return newCommand;
}

/*It destroys a command, freeing the allocated memory*/
Status command_destroy(Command *command) {
  if (!command) return ERROR;

  free(command);
  command = NULL;
  return OK;
}

/*If command is not null, a code is asigned to it*/
Status command_set_code(Command *command, CommandCode code) {
  if (!command) return ERROR;

  command->code = code;

  return OK;
}

/*It gets the code of a command*/
CommandCode command_get_code(Command *command) {
  if (!command) return NO_CMD;

  return command->code;
}

/*If command is not null, a description is asigned to it*/
Status command_set_desc(Command *command, char *desc) {
  int len;
  if (!command) return ERROR;

  if (!desc) {
    command->cmd_desc[0] = '\0';
    return OK;
  }

  if ((len = strlen(desc)) >= CMD_LENGHT) {
    command->cmd_desc[0] = '\0';
    return ERROR;
  }

  strcpy(command->cmd_desc, desc);

  return OK;
}

/*It gets the description of a command*/
char *command_get_desc(Command *command) {
  if (!command) return NULL;

  return command->cmd_desc;
}

Status command_set_status(Command *command, Status status) {
  if (!command) return ERROR;

  command->status = status;

  return OK;
}

Status command_get_status(Command *command) {
  if (!command) return ERROR;

  return command->status;
}

/*Interpretates the input from the user and asigns the propper command*/
Status command_get_user_input(Command *command) {
  char input[CMD_LENGHT] = "", *token = NULL, *cmd_desc = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) return ERROR;

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \r\n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    /*gets the description of the code that will be performed.
    This might be the name of an object to take/drop*/
    cmd_desc = strtok(NULL, "\r\n");
    if (command_set_desc(command, cmd_desc) == ERROR) return ERROR;


    /*compares the user input to any known command*/
    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) ||
          !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
        printf("%s", cmd_to_str[i][CMDL]);
      } else {
        i++;
      }
    }

    return command_set_code(command, cmd);
  } else {
    return command_set_code(command, EXIT);
  }
}

/*It prints the command information*/
Status command_print(Command *command) {
  if (!command) return ERROR;

  fprintf(stdout, "--> Command code: %s\n",
          cmd_to_str[command->code - NO_CMD][CMDL]);
  fprintf(stdout, "--> Command description: %s\n", command->cmd_desc);
  if (command->status == OK)
    fprintf(stdout, "--> Command last status: OK\n");
  else
    fprintf(stdout, "--> Command last status: ERROR\n");

  return OK;
}