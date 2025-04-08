/**
 * @brief It implements the game_reader module
 *
 * @file game_reader.c
 * @author Juan Ibáñez
 * @version 0
 * @date 03-02-2025
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************ Declaration of private functions *****************/

/**
 * Implementation of the private funtions
 */

/**
 * Implementation of the public funtions
 */

/*Function used in game_create_from_file to load the links from a file to a game*/
Status game_reader_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, orig = NO_ID, dest = NO_ID;
  Direction dir = UNK_DIR;
  Bool open = FALSE;
  Link *link = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #l:<id>|<name>|<origin id>|<destination id>|<direction>|<open or closed>|
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      orig = atol(toks);
      toks = strtok(NULL, "|");
      dest = atol(toks);
      toks = strtok(NULL, "|");
      dir = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);

      /*creates a new space with the read data and adds it to the game spaces
        list*/
      link = link_create(id);
      if (!link) return ERROR;
      if (link_set_name(link, name) == ERROR) st = ERROR;
      if (link_set_orig(link, orig) == ERROR) st = ERROR;
      if (link_set_dest(link, dest) == ERROR) st = ERROR;
      if (link_set_direction(link, dir) == ERROR) st = ERROR;
      if (link_set_open(link, open) == ERROR) st = ERROR;

      if (st == ERROR) {
        link_destroy(link);
        fclose(file);
        return ERROR;
      }

      if (game_add_link(game, link) == ERROR) return ERROR;
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the objects from a file to a game*/
Status game_reader_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char message[OBJ_DESC_MX + 1] = "";
  char *toks = NULL;
  Id id_obj, id_location;
  Object *object = NULL;
  Space *space = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #o:<id>|<name>|<initial pos>|<message>
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id_obj = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      sprintf(message,"%.*s", OBJ_DESC_MX, toks);

      /*creates a new object with the read data, adds it to the array of objects
      and to the set of objects inside its corresponding space */
      object = object_create(id_obj);
      if (!object) return ERROR;
      if (object_set_name(object, name) == ERROR) st = ERROR;
      if (object_set_desc(object, message) == ERROR) st = ERROR;

      if(st == ERROR) {
        object_destroy(object);
        fclose(file);
        return ERROR;
      }

      if (game_add_object(game, object) == ERROR) return ERROR;
      if (!(space = game_get_space(game, id_location))) return ERROR;
      if (space_add_object(space, id_obj) == ERROR) return ERROR;
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the players from a file to a game*/
Status game_reader_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char *toks = NULL;
  Id id_play = NO_ID, id_location = NO_ID;
  int health = 0, inventory_size = 0;
  Player *play = NULL;
  Space *space = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #p:<id>|<name>|<graphic description>|<location>|<health>|<backpack size>
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id_play = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks); 
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      inventory_size = atoi(toks);

      /*creates a new player with the read data, adds it to the array of players
      and sets its location to the corresponding space */
      play = player_create(id_play);
      if (!play) return ERROR;
      if (player_set_name(play, name) == ERROR) st = ERROR;
      if (player_set_gdesc(play, desc) == ERROR) st = ERROR;
      if (player_set_health(play, health) == ERROR) st = ERROR;
      if (player_set_inventory_size(play, inventory_size) == ERROR) st = ERROR;

      if(st == ERROR) {
        player_destroy(play);
        fclose(file);
        return ERROR;
      }

      if (game_add_player(game, play) == ERROR) return ERROR;
      if (!(space = game_get_space(game, id_location))) return ERROR;
      if (player_set_location(play, id_location) == ERROR) return ERROR;

      if(space_set_discovered(space, TRUE) == ERROR) return ERROR;
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the characters from a file to a game*/
Status game_reader_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id_charr = NO_ID, id_location = NO_ID;
  int health = 0;
  Bool friendly = FALSE;
  Character *charr = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #c:<id>|<name>|<graphic description>|<location>|<health>|<friendly or not>|<message>
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id_charr = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks); 
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);

      /*creates a new character with the read data, adds it to the array of characters
      and sets its location to the corresponding space */
      charr = character_create(id_charr);
      if (!charr) return ERROR;
      if (character_set_name(charr, name) == ERROR) st = ERROR;
      if (character_set_gdesc(charr, desc) == ERROR) st = ERROR;
      if (character_set_health(charr, health) == ERROR) st = ERROR;
      if (character_set_friendly(charr, friendly) == ERROR) st = ERROR;
      if (character_set_message(charr, message) == ERROR) st = ERROR;

      if(st == ERROR) {
        character_destroy(charr);
        fclose(file);
        return ERROR;
      }

      if (!game_get_space(game, id_location)) return ERROR;

      if (game_add_character(game, charr, id_location) == ERROR) return ERROR;
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the space from a file to a game*/
Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  int i = 0;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #s:<id>|<name>|<graphic description>|
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) != 0) continue;
    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
  
    /*creates a new space with the read data and adds it to the game spaces
    list*/
    space = space_create(id);
    if (!space) return ERROR;

    space_set_name(space, name);

    for (i = 0; i < SP_GD_HGHT; i++) {
      toks = strtok(NULL, "|");

      if (toks) {
        if (space_set_gdesc_at(space, toks, i) == ERROR) return ERROR;
      } else {
        if (space_set_gdesc_at(space, " ", i) == ERROR) return ERROR;
      }
    }
    

    if (game_add_space(game, space) == ERROR) return ERROR;
  }
  
  fclose(file);
  return OK;
}