/**
 * @brief It allows to load games saved from files
 *
 * @file game_management.h
 * @author Juan Ibáñez
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "game.h"
#include "types.h"

/* #################### PUBLIC FUNCTIONS #################*/

/**
 * @brief Saves the game to a file
 * @author Alina Datsko
 *
 * @param game pointer to the game
 * @param filename name of the file where the game will be saved
 * @return OK if everything went well, ERROR if there was any mistake
 */
Status game_management_save(Game *game, char *filename);

/**
 * @brief Loads a game from a file
 * @author Tiago Oselka
 *
 * @param game Double pointer to the game
 * @param filename name of the file where the game will be loaded from
 * @return OK if everything went well, ERROR if there was any mistake
 */
Status game_management_load(Game **game, char *filename);

/**
 * @brief function used in game_create_from_file to load the links from
 * a file to a game
 *
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the links loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_links(Game *game, char *filename);

/**
 * @brief Loads the minimap from a file to a game
 * 
 * @param Pointer to the game which minimap will be loaded
 * @param filename Name of the file with the data
 * @return OK if the minimap loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_minimap(Game *game, const char *filename);

/**
 * @brief Loads the classes from a file to a game
 * 
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file with the data
 * @return OK if the classes loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_classes(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the objects from
 * a file to a game
 *
 * @param game Pointer to the game where the objects will be stored
 * @param filename Name of the file
 * @return OK if the objects loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_objects(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the players from
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the players will be stored
 * @param filename Name of the file
 * @return OK if the players loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_players(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the turn from
 * a file to a game
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game where the players will be stored
 * @param filename 
 * @return OK if the space saved correctly, ERROR if there was any mistake 
 */
Status game_management_load_turn(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the mode from
 * a file to a game
 * @author Lucas Blanco Rodriguez
 * 
 * @param game Pointer to the game where the players will be stored
 * @param filename Name of the file
 * @return OK if the space saved correctly, ERROR if there was any mistake 
 */
Status game_management_load_mode(Game *game, char *filename);
/**
 * @brief function used in game_create_from_file to load the characters from
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the characters will be stored
 * @param filename Name of the file
 * @return OK if the characters loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_characters(Game *game, char *filename);

/**
 * @brief function used in game_create_from_file to load the space from 
 * a file to a game
 * @author Alina Datsko Yaskerska
 *
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the space loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_spaces(Game *game, char *filename);

/**
 * @brief Loads the minimap from a file to a game
 * 
 * @param Pointer to the game which minimap will be loaded
 * @param filename Name of the file with the data
 * @return OK if the minimap loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_minimap(Game *game, const char *filename);

/**
 * @brief function used in game_create_from_file to load the players information (interface data) from
 * a file to a game
 * @author Lucas Blanco
 *
 * @param game Pointer to the game where the players will be stored
 * @param filename Name of the file
 * @return OK if the players info was loaded correctly, ERROR if there was any mistake
 */
Status game_management_load_interface_data(Game *game, char *filename);

/**
 * @brief function used in game_save to save the links from a game to a file
 * @author Tiago Oselka
 *
 * @param game Pointer to the game where the spaces are currently stored
 * @param filename Name of the file
 * @return OK if the links saved correctly, ERROR if there was any mistake
 */
Status game_management_save_links(Game *game, char *filename);

/**
 * @brief function used in game_save to save the minimap from a game to a file
 * @author Alina Datsko
 * 
 * @param game Pointer to the game where the minimap is currently stored
 * @param filename Name of the file
 * @return OK if the minimap saved correctly, ERROR if there was any mistake
 */ 
Status game_management_save_minimap(Game *game, const char *filename);

/**
 * @brief function used in game_save to save the classes from a game to a file
 * @author Alina Datsko
 *
 * @param game Pointer to the game where the spaces are currently stored
 * @param filename Name of the file
 * @return OK if the classes saved correctly, ERROR if there was any mistake
 */
Status game_management_save_classes(Game *game, char *filename);

/**
 * @brief function used in game_save to save the objects from a game to a file
 * @author Alina Datsko
 *
 * @param game Pointer to the game where the spaces are currently stored
 * @param filename Name of the file
 * @return OK if the objects saved correctly, ERROR if there was any mistake
 */
Status game_management_save_objects(Game *game, char *filename);

/**
 * @brief function used in game_save to save the players from a game to a file
 * @author Tiago Oselka
 *
 * @param game Pointer to the game where the players are currently stored
 * @param filename Name of the file
 * @return OK if the players saved correctly, ERROR if there was any mistake
 */
Status game_management_save_players(Game *game, char *filename);

/**
 * @brief function used in game_save to save the characters from a game to a file
 * @author Alina Datsko 
 *
 * @param game Pointer to the game where the characters are currently stored
 * @param filename Name of the file
 * @return OK if the characters saved correctly, ERROR if there was any mistake
 */
Status game_management_save_characters(Game *game, char *filename);

/**
 * @brief function used in game_save to save the space from a game to a file
 * @author Tiago Oselka
 *
 * @param game Pointer to the game where the spaces are currently stored
 * @param filename Name of the file
 * @return OK if the space saved correctly, ERROR if there was any mistake
 */
Status game_management_save_spaces(Game *game, char *filename);

/**
 * @brief function used in game_save to save the current turn from a game to a file
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the space saved correctly, ERROR if there was any mistake 
 */
Status game_management_save_turn(Game *game, char *filename);

/**
 * @brief function used in game_save to save the current mode from a game to a file
 * @author Lucas Blanco Rodriguez
 * 
 * @param game Pointer to the game where the spaces will be stored
 * @param filename Name of the file
 * @return OK if the space saved correctly, ERROR if there was any mistake 
 */
Status game_management_save_mode(Game *game, char *filename);

/**
 * @brief function used in game_save to save the minimap from a game to a file
 * @author Alina Datsko
 * 
 * @param game Pointer to the game where the minimap is currently stored
 * @param filename Name of the file
 * @return OK if the minimap saved correctly, ERROR if there was any mistake
 */ 
Status game_management_save_minimap(Game *game, const char *filename);

/**
 * @brief function used in game_save to save the players info (interface data) from a game to a file
 * @author Lucas Blanco
 *
 * @param game Pointer to the game where the players are currently stored
 * @param filename Name of the file
 * @return OK if the players info was saved correctly, ERROR if there was any mistake
 */
Status game_management_save_interface_data(Game *game, char *filename);

#endif