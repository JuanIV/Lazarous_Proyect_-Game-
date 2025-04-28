/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "character.h"
#include "link.h"

/**
 * @brief Maximum amount of spaces that a game can have
 *
 */
#define MAX_SPACES 100

/**
 * @brief Maximum amount of links that a game can have, 4 times the number of spaces
 *
 */
#define MAX_LINKS (4 * MAX_SPACES)

/**
 * @brief Maximum ammount of classes of objects for a game
 * 
 */
#define MAX_CLASS 100

/**
 * @brief Maximum amount of objects that a game can have
 * 
 */
#define MAX_OBJ 100

/**
 * @brief Maximum amount of characters that a game can have
 * 
 */
#define MAX_CHARR 100

/**
 * @brief Maximum amount of players that a game can have
 * 
 */
#define MAX_PLAY 8

/**
 * @brief Number of last commands that are saved in order to print them in the feedback region of graphic engine
 * 
 */
#define NUM_CMDS 3

/**
 * @brief Number of messages that are saved in order to print them in the messages region of graphic engine
 * 
 */
#define NUM_MSGS 4

/**
 * @brief It stores the game information
 *
 */
typedef struct _Game Game;



/**
 * @brief It creates a new game, initializing the spaces and its other members
 * @author Tiago Oselka
 *
 * @return said game, initialized
 */
Game *game_create();

/**
 * @brief It reads a games data from a file
 * @author Alina Datsko Yaskerska
 *
 * @param game
 * @param position
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief It destroys a game freeing every allocated data (destroys space data
 * and the last command)
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_destroy(Game *game);



/**
 * @brief Gets a pointer to the player who has the turn
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @return a pointer to the player 
 */
Player *game_get_player(Game *game);

/**
 * @brief Gets a specific player of the game 
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param pos Position of the player in the array of players
 * @return Pointer to the desired player or NULL in case of a mistake
 */
Player *game_get_player_at(Game *game, int pos);

/**
 * @brief Gets the pointer to a player from its name
 * @author Alina Datsko
 * 
 * @param game Pointer to the game
 * @param name Name of the player
 * @return Pointer to the wanted player
 */
Player *game_get_player_from_name(Game *game, char *name);

/**
 * @brief Gets the player turn from the name of the player
 * @author Alina Datsko
 * 
 * @param game Pointer to the game
 * @param name Name of the player whose turn is looked for
 * @return Turn of the player or -1 if there was an error
 */
int game_get_player_pos_from_name(Game *game, char *name);

/**
 * @brief Gets the number of players in the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return Number of players in the game
 */
int game_get_n_players(Game *game);

/**
 * @brief It gets the player position from the game struct
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @return player´s location id
 */
Id game_get_player_location(Game *game);

/**
 * @brief Sets the player position to a given id
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param id the id of the space where the player position will be set
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Add a new player to the game
 * @author Lucas Blanco Rodríguez
 *
 * @param game pointer to the game
 * @param play a pointer to the game that is going to be added
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_add_player (Game *game, Player *play);

/**
 * @brief Gets the number of characters that follow a player
 * 
 * @param game Pointer to the game
 * @param player Pointer to the player
 * @return The number of followers and -1 in case of error
 */
int game_get_num_followers(Game *game, Player *player);

/**
 * @brief Gets a set with the Ids of the followers that a player has
 * 
 * @param game Pointer to the game
 * @param player Pointer to the player
 * @return A set with the ids and NULL in case of error
 */
Set *game_get_followers(Game *game, Player *player);

/**
 * @brief Gets an object with a certain name from the players backpack
 * 
 * @param game Pointer to the game
 * @param name Name of the object wanted
 * @return Id of the object if it is found, NO_ID if it is not found
 */
Id game_get_object_from_player(Game *game, char *name);

/**
 * @brief Gets the position of the player who has the turn of the game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game
 * @return Returns number of the turn
 */
int game_get_turn(Game *game);

/**
 * @brief Sets the position of the player who has the turn of the game
 * 
 * @param game Pointer to the game
 * @param turn Turn to be set
 * @return Ok if everything went well, ERROR if there was any mistake 
 */
Status game_set_turn(Game *game, int turn);

/**
 * @brief Sets the next turn
 * @author Alina Datsko Yaskerska
 *
 * @param game pointer to the game
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_next_turn(Game *game);



/**
 * @brief Given an id, returns a pointer to the space that matches that id
 * @author Profesores PPROG
 *
 * @param game pointer to the game
 * @param id id of the space wanted
 * @return a pointer to the space with the given id
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets a space in a position of the array of spaces
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param pos desired position inside the array of spaces
 * @return A pointer to the desired space 
 */
Space *game_get_space_at_pos(Game *game, int pos);

/**
 * @brief Gets the number of spaces in a game
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @return Number of spaces in the game
 */
int game_get_n_spaces(Game *game);

/** 
 * @brief It sets the number of spaces in a game
 * @author Juan Ibáñez  
 * 
 * @param game Pointer to the game
 * @param n_spaces Number of spaces to be set
 * @return OK if everything went well, ERROR if there was a mistake
 */
Status game_set_n_spaces(Game *game, int n_spaces);

/**
 * @brief Adds a space to the game
 * @author Tiago Oselka
 *
 * @param game Pointer to the game where the space will be added
 * @param space Pointer to the space being added
 * @return OK if the space was added correctly, ERROR if the game is full or the
 * space does not exist
 */
Status game_add_space(Game *game, Space *space);



/**
 * @brief Adds a class to the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param class Pointer to the class being added
 * @return OK if the class was added correctly, ERROR otherwise
 */
Status game_add_class(Game *game, Class *class);

/**
 * @brief Gets the pointer to a class
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param id Id of the class wanted
 * @return Pointer to the class wanted
 */
Class *game_get_class(Game *game, Id id);

/**
 * @brief Gets the number of classes of a game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return Int number of classes in the game
 */
int game_get_n_classes(Game *game);

/**
 * @brief It gets the class in a position of the array of classes
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param pos Position in the array
 * @return Pointer to the class in that position
 */
Class *game_get_class_at_pos(Game *game, int pos);



/**
 * @brief Adds an object to the array of objects of the game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object
 * @return OK if the object was added correctly, ERROR if there was any mistake
 */
Status game_add_object(Game *game, Object *obj);

/**
 * @brief Gets the pointer to an object
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param id Id of the object wanted
 * @return Pointer to the object wanted
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief Gets the number of objects in a game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return Number of objects in the game
 */
int game_get_n_objects(Game *game);

/**
 * @brief It gets an object's name from its id
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param id Id of the object
 * @return object´s name or NULL pointer if there was any mistake
 */
char *game_get_obj_name_from_id(Game *game, Id id);

/**
 * @brief It gets an object's id from its name
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param name name of the object
 * @return object´s id or NO_ID if there was any mistake
 */
Id game_get_obj_id_from_name(Game *game, char *obj_name);

/**
 * @brief it gets an object's position from a game
 * @author Juan Ibáñez
 *
 * @param game pointer to the game
 * @param id Id of the object
 * @return object´s location id
 */
Id game_get_object_location(Game *game, Id id);

/**
 * @brief Declares the position of an object if posible
 * @author Juan Ibáñez
 *
 * @param game pointer to the game
 * @param obj Id of the object being placed
 * @param pos the id of the space where the object will be placed
 * @return Ok if everything went well, ERROR if the space is full or there was a mistake
 */
Status game_set_object_location(Game *game, Id obj, Id pos);

/**
 * @brief Gets the object in a position of the array of objects
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param pos Position in the array
 * @return Pointer to the desired object
 */
Object *game_get_object_at_pos(Game *game, int pos);



/**
 * @brief Adds a character to the game and sets its location
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param charr Pointer to the character
 * @param location Id of the location to be set
 * @return Ok if everything went well, ERROR if the space is full or there was a mistake
 */
Status game_add_character(Game *game, Character *charr, Id location);

/**
 * @brief Gets the pointer to a character from its Id
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param id Id of the character
 * @return Pointer to the wanted character 
 */
Character *game_get_character_from_id(Game *game, Id id);

/**
 * @brief Gets the pointer to a character from its name
 * @author Tiago oselka
 * 
 * @param game Pointer to the game
 * @param name Name of the character
 * @return Pointer to the wanted character
 */
Character *game_get_character_from_name(Game *game, char *name);


/**
 * @brief Gets the number of characters in a game
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return Number of character in the game
 */
int game_get_n_characters(Game *game);

/**
 * @brief Gets the location of a character
 * @author Juan Ibáñez
 * 
 * @param game Pointert to the game
 * @param id Id of the character
 * @return Id of the space in which the character is
 */
Id game_get_character_location(Game *game, Id id);

/**
 * @brief Sets a character to a certain space
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param charr Id of the character being set
 * @param pos Id of the space where the character will be set
 * @return Ok if everything went well, ERROR if the space is full or there was a mistake
 */
Status game_set_character_location(Game *game, Id charr, Id loc);

/**
 * @brief It gets a character's id from its name
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param name Name of the character
 * @return Id of the character or NO_ID if it wasnt found
 */
Id game_get_charr_id_from_name(Game *game, char *name);

/**
 * @brief Gets the character in a position of the array of objects
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param pos Position in the array
 * @return Pointer to the desired character
 */
Character *game_get_character_at_pos(Game *game, int pos);


/**
 * @brief Given two roles in the game, returns wether their relationship is friendly or not
 * 
 * @param role1 a rola
 * @param role2 another role with which we want to see the relationship 
 * @param relationship Pointer to a bool 
 * @return Ok if everything went well, ERROR if the space is full or there was a mistake
 *  exit value of relationship: TRUE if their relationship is friendly and FALSE otherwise
 */
Status game_get_friendly(Role role1, Role role2, Bool *relationship); 


/**
 * @brief Adds a link to the game
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param link Pointer to the link
 * @return Ok if everything went well, ERROR if the space is full or there was a mistake
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief It gets a link in a position of the array of links
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param pos desired position inside the array of links
 * @return A pointer to the desired space 
 */
Link *game_get_link_at_pos(Game *game, int pos);

/**
 * @brief Gets the number of links in a game
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @return Number of links in the game
 */
int game_get_n_links(Game *game);

/**
 * @brief Given the Id of a space and a direction returns the Id of the space linked in that direction
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param cur_space Id of a space
 * @param dir The direction of the link
 * @return The id of the space located in the desired direction or NO_ID if there was a mistake
 */
Id game_get_connection(Game *game, Id cur_space, Direction dir);

/**
 * @brief Gets a link from a origin space and a direction
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param orig_space Origin space of the link
 * @param dir Direction of the desired link
 * @return Pointer to the link if it exists, NULL if it doesnt
 */
Link *game_get_link(Game *game, Id orig_space, Direction dir);

/**
 * @brief Checks wether a connection is opened given a space and a desired direction
 * @author Tiago Oselka
 * 
 * @param game pointer to the game
 * @param cur_space the id of the origin spce
 * @param dir direction to be followed
 * @param bool pointer to a Bool where the function will store the result 
 * @return OK if everything went well, ERROR if there was a mistake
 * bool: TRUE if the connection is opened or FALSE if it isn't opened
 */
Status game_connection_is_open(Game *game, Id cur_space, Direction dir, Bool *bool);

/**
 * @brief It gets a command from a desided position of the interface data of a player at a desired position
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param cmd_pos Desired position inside interfaceData array of commands
 * @return Pointer to said command
 */
Command *game_get_command_at_pos(Game *game, int play_pos, int cmd_pos);

/**
 * @brief It gets the last message of the interface data of a player at a desired position
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @return Pointer to said command
 */
char *game_get_last_message_msg_at_pos(Game *game, int play_pos);

/**
 * @brief Gets the last message displayed by a chat
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @return String of the message
 */
char *game_get_last_message(Game *game);

/**
 * @brief It gets a message from a desided position of the interface data of a player at a desired position
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param msg_pos Desired position from the array of msg_pos
 * @return Pointer to said command
 */
char *game_get_last_message_at_pos(Game *game, int play_pos, int msg_pos);

/**
 * @brief Sets the last displayed message
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param message String of the message
 * @return OK if everything went well, ERROR if there was a mistake
 */
Status game_set_last_message(Game *game, char *message);

/**
 * @brief Sets the last displayed message at a desired position 
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param message String to be set as the message
 * @return OK if the last_cmd was successfull, ERROR otherwise 
 */
Status game_set_last_message_at_pos(Game *game, int play_pos, char *message);

Bool game_get_last_message_visibility_at_pos(Game *game, int play_pos, int msg_pos);

Status game_set_last_message_visibility_at_pos(Game *game, int play_pos, int msg_pos, Bool visibility);

/**
 * @brief Gets the last message sender type at a postion from the array of players
 * @author Lucas Blanco
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param msg_pos Desired postion from the array of messages
 * @return Type of the sender of the last message
 */
Type game_get_last_message_sender_type_at_pos(Game *game, int play_pos, int msg_pos);

/**
 * @brief Sets the sender type from a pos
 * @author Lucas Blanco
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param msg_pos Desired postion from the array of messages
 * @param type Type of the sender to be set
 * @return OK if everything went well, ERROR if there was a mistake
 */
Status game_set_last_message_sender_type_at_pos(Game *game, int play_pos, int msg_pos, Type type);

/**
 * @brief Sets the sender from a pos
 * @author Lucas Blanco
 * 
 * @param game Pointer to the game
 * @param play_pos Desired position from the array of players
 * @param msg_pos Desired postion from the array of players
 * @param sender Id of the sender to be set
 * @return OK if everything went well, ERROR if there was a mistake
 */
Status game_set_last_message_sender_at_pos(Game *game, int play_pos, int msg_pos, Id sender);


/**
 * @brief Gets a line from the last close up shown
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param pos Position of the line wanted
 * @return String with the line wanted
 */
char *game_get_last_close_up_at(Game *game, int pos);

/**
 * @brief Sets the last close up
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param closeup New line of the last close up 
 * @param pos Position of the new line
 * @return ERROR if there was any mistake, OK otherwise
 */
Status game_set_last_close_up(Game *game, char *closeup, int pos);

/**
 * @brief Sets the last close up of a specific player
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param closeup New line of the last close up 
 * @param pos Position of the array of players
 * @param line Position of the new line
 * @return ERROR if there was any mistake, OK otherwise
 */
Status game_set_last_close_up_at_pos(Game *game, char *closeup, int pos, int line);

/**
 * @brief It gets the last command from the game struct
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @return a pointer to the last command
 */
Command *game_get_last_command(Game *game);

/**
 * @brief It gets the last command at a desired position from the game struct
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param pos position to be searched
 * @return a pointer to the command at position pos from the interface data command array of the 
 * current player
 */
Command *game_get_last_command_at_pos(Game *game, int pos);

/**
 * @brief Given a command, the function sets it as the last one
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param command pointer to the received command
 * @return ERROR if game or command is null, OK otherwise
 */
Status game_set_last_command(Game *game, Command *command);


/**
 * @brief It gets the status of the last command at a desired position
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @return OK if the last_cmd was successfull, ERROR otherwise
 */
Status game_get_last_status(Game *game);

/**
 * @brief It gets the status of the last command
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param pos position to be searched
 * @return OK if the last_cmd was successfull, ERROR otherwise
 */
Status game_get_last_status_at_pos(Game *game, int pos);

/**
 * @brief Given the status of the last command, the function sets it as the last one
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param status the status of the last command
 * @return ERROR if game is null, OK otherwise
 */
Status game_set_last_status(Game *game, Status status);

/**
 * @brief It sets the mode of the game (deterministic or not)
 * @author Lucas Blanco Rodríguez
 *
 * @param game pointer to the game
 * @param deterministic the mode of the game (deterministic or not)
 * @return  ERROR if game is null, OK otherwise
 */
Status game_set_deterministic(Game *game, Bool deterministic);

/**
 * @brief Gets the deterministic value of the game
 * @author Lucas Blanco Rodríguez
 *
 * @param game pointer to the game
 * @param deterministic the mode of the game (deterministic or not)
 * @return ERROR if game is null, OK otherwise
 */
Status game_get_deterministic(Game *game, Bool *deterministic);

/**
 * @brief Checks if the game is finished
 * @author Profesores PPROG
 *
 * @param game pointer to the game
 * @return TRUE if the game is finished, FALSE if not
 */
Bool game_get_finished(Game *game);

/**
 * @brief Updates the status of the game (finished or not)
 * @author Profesores PPROG
 *
 * @param game pointer to the game
 * @param finished TRUE if the game is finished, FALSE if not
 * @return Ok when finished, ERROR if game pointer is null
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Saves the game to a file
 * @author Alina Datsko
 *
 * @param game pointer to the game
 * @param filename name of the file where the game will be saved
 * @return OK if everything went well, ERROR if there was any mistake
 */
Status game_save(Game *game, char *filename);

/**
 * @brief Loads a game from a file
 * @author Tiago Oselka
 *
 * @param game Double pointer to the game
 * @param filename name of the file where the game will be loaded from
 * @return OK if everything went well, ERROR if there was any mistake
 */
Status game_load(Game **game, char *filename);

/**
 * @brief Prints information about every space in the game and the object and
 * player's location
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 */
Status game_print(Game *game);

#endif
