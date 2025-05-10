/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief It stores all areas of the screen: map, description, banner, help and
 * feedback
 *
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Creates a new graphic engine initializing all screen areas according
 * to their area resolution
 *
 * @return initialized graphic engine
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destroys a graphic engine destroying each dedicated area and freeing
 * allocated memory
 *
 * @param ge pointer to the graphic engine to be destroyed
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Paints each area according to its function with the necessary
 * information
 *
 * @param ge pointer to the graphic engine where the areas of the screen are
 * stored
 * @param game pointer to the game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Screen print);

#endif
