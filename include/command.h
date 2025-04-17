/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief Number of ways a command can be written
 *
 */
#define N_CMDT 2

/**
 * @brief Total number of commands that can be executed
 *
 */
#define N_CMD 14

/**
 * @brief Defines the ways a command can be written (short, long)
 *
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * @brief Defines all possible commands
 *
 */
typedef enum {
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  MOVE,
  TAKE,
  DROP,
  ATTACK,
  CHAT,
  INSPECT,
  RECRUIT,
  ABANDON,
  USE,
  SAVE,
  LOAD
} CommandCode;

/**
 * @brief This struct stores all the information related to a command
 *
 */
typedef struct _Command Command;

/**
 * @brief It creates a new command, allocating memory and initializing its
 * members
 * @author Tiago Oselka
 *
 * @return a new command, initialized
 */
Command *command_create();

/**
 * @brief It destroys a command, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param command a pointer to the command that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_destroy(Command *command);

/**
 * @brief If command is not null, a code is asigned to it
 * @author Profesores PPROG
 *
 * @param command a pointer to the command to which the code will be asigned
 * @param code the function that the command will perform
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief It gets the code of a command
 * @author Profesores PPROG
 *
 * @param command a pointer to the command
 * @return NO_CMD if the command is null or its code otherwise
 */
CommandCode command_get_code(Command *command);

/**
 * @brief If command is not null, a description is asigned to it
 * @author Tiago Oselka
 *
 * @param command a pointer to the command to which the desccription will be
 * asigned
 * @param desc the description that the command will have
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_desc(Command *command, char *desc);

/**
 * @brief It gets the description of a command
 * @author Tiago Oselka
 *
 * @param command a pointer to the command
 * @return NULL if the command is null or its description otherwise
 */
char *command_get_desc(Command *command);

/**
 * @brief If command is not null, a status is asigned to it
 * @author Tiago Oselka
 *
 * @param command a pointer to the command to which the status will be
 * asigned
 * @param status the status that the command will have
 *
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_status(Command *command, Status status);

/**
 * @brief It gets the status of a command
 * @author Tiago Oselka
 *
 * @param command a pointer to the command
 * @return ERROR if the command is null or its status otherwise
 */
Status command_get_status(Command *command);

/**
 * @brief Interpretates the input from the user and asigns the propper command
 * @author Tiago Oselka
 *
 * @param command a pointer to the command where the user command will be stored
 * @return OK, if the command is correctly asigned or ERROR if there was some
 * mistake
 */
Status command_get_user_input(Command *command);

/**
 * @brief It prints the command information
 * @author Tiago Oselka
 * 
 * @param command a pointer to the command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_print(Command *command);
#endif
