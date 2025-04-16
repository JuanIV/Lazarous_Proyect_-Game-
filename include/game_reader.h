/**
 * @brief It allows to load games saved from files
 *
 * @file game_reader.h
 * @author Juan Ibáñez
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief function used in game_create_from_file to load the links from
 * a file to a game
 *
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the links loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_links(Game *game, char *filename);

/**
 * @brief Loads the classes from a file to a game
 * 
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file with the data
 * @return OK if the classes loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_classes(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the objects from
 * a file to a game
 *
 * @param game Pointer to the game where the objects will be stored
 * @param filename Name of the file
 * @return OK if the objects loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_objects(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the players from
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the players will be stored
 * @param filename Name of the file
 * @return OK if the players loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_players(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the characters from
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the characters will be stored
 * @param filename Name of the file
 * @return OK if the characters loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_characters(Game *game, char *filename);


/**
 * @brief function used in game_create_from_file to load the space from 
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the space loaded correctly, ERROR if there was any mistake
 */
Status game_reader_load_spaces(Game *game, char *filename);
#endif