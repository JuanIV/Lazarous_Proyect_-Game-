/**
 * @brief It implements the game management module
 *
 * @file game_management.c
 * @author Juan Ibáñez
 * @version 2
 * @date 17-04-2025
 * @copyright GNU Public License
 */

#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief space that will used for writing type identificator, id, use value, movable, role,... of any 
 * type being saved
 * 
 */
#define EXTRAS 50

/**
 * @brief length of the line printed while saving a space
 * 
 */
#define SPACE_LINE (EXTRAS + WORD_SIZE + SP_GD_HGHT * (SP_GD_WTH + 1))

/**
 * @brief length of the line printed while saving a link
 * 
 */
#define LINK_LINE (EXTRAS + WORD_SIZE)

/**
 * @brief length of the line printed while saving a class
 * 
 */
#define CLASS_LINE (EXTRAS + WORD_SIZE + OBJ_DESC_MX)

/**
 * @brief length of the line printed while saving a object
 * 
 */
#define OBJECT_LINE EXTRAS

/**
 * @brief length of the line printed while saving a character
 * 
 */
#define CHARACTER_LINE (EXTRAS + WORD_SIZE + CHR_GD_SZ + MESG_SIZE)

/**
 * @brief length of the line printed while saving a player
 * 
 */
#define PLAYER_LINE (EXTRAS + WORD_SIZE + (PLY_GD_SZ + 1) )

/*Function used in game_create_from_file to load the links from a file to a game*/
Status game_management_load_links(Game *game, char *filename) {
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

/*Loads the classes from a file to a game*/
Status game_management_load_classes(Game *game, char *filename){
  FILE *file = NULL;
  char line[WORD_SIZE + 1] = "";
  char name[WORD_SIZE + 1] = "";
  char desc[OBJ_DESC_MX + 1] = "";
  char *toks = NULL;
  Tag tag;
  Bool movable;
  Id class_id, dependency, open;
  Class *class = NULL;
  int use_value, luck;
  Status st = OK;

  if(!game || !filename) return ERROR;

  if(!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #k:<id>|<tag>|<name>|<description>|<use_value>|<movable>|<dependency>|<open>|<luck>
  */
  while(fgets(line, WORD_SIZE, file)){
    if(strncmp("#k:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      class_id = atol(toks);
      toks = strtok(NULL, "|");
      tag = atol(toks);
      toks = strtok(NULL, "|");
      sprintf(name, "%.*s",WORD_SIZE, toks);
      toks = strtok(NULL, "|");
      sprintf(desc, "%.*s",OBJ_DESC_MX, toks);
      toks = strtok(NULL, "|");
      use_value = atol(toks);
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      luck = atol(toks);

      class = object_class_create(class_id);
      if(!class){
        fclose(file);
        return ERROR;
      } 

      if(object_class_set_tag(class, tag) == ERROR) st = ERROR;
      if(object_class_set_name(class, name) == ERROR) st = ERROR;
      if(object_class_set_desc(class, desc) == ERROR) st = ERROR;
      if(object_class_set_use_value(class, use_value) == ERROR) st = ERROR;
      if(object_class_set_movable(class,movable) == ERROR) st = ERROR;
      if(object_class_set_dependency(class,dependency) == ERROR) st = ERROR;
      if(object_class_set_open(class, open) == ERROR) st = ERROR;
      if(object_class_set_luck(class, luck) == ERROR) st = ERROR;

      if(st == ERROR){
        object_class_destroy(class);
        fclose(file);
        return ERROR;
      }

      if(game_add_class(game, class) == ERROR){
        object_class_destroy(class);
        fclose(file);
        return ERROR;
      }
    }
  }
  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the objects from a file to a game*/
Status game_management_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Id obj_id, class_id, location_id;
  Class *class = NULL;
  Object *object = NULL;
  Space *space = NULL;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #o:<id>|<class_id>|<initial pos>
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      obj_id = atol(toks);
      toks = strtok(NULL, "|");
      class_id = atol(toks);
      toks = strtok(NULL, "|");
      location_id = atol(toks);

      /*creates a new object with the read data, adds it to the array of objects
      and to the set of objects inside its corresponding space */
      
      if (!(object = object_create(obj_id))){
        fclose(file);
        return ERROR;
      }
      if(!(class = game_get_class(game, class_id))){
        object_destroy(object);
        fclose(file);
        return ERROR;
      }
      if(object_set_class(object,class) == ERROR) {
        object_destroy(object);
        fclose(file);
        return ERROR;
      }

      if (game_add_object(game, object) == ERROR) {
        object_destroy(object);
        fclose(file);
        return ERROR;
      } 
      if (!(space = game_get_space(game, location_id))) {
        object_destroy(object);
        fclose(file);
        return ERROR;
      } 
      if (space_add_object(space, obj_id) == ERROR) {
        object_destroy(object);
        fclose(file);
        return ERROR;
      } 
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the players from a file to a game*/
Status game_management_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char *toks = NULL;
  Id id_play = NO_ID, id_location = NO_ID, obj_id = NO_ID, armor_id = NO_ID, weapon_id = NO_ID;
  Role role = NO_ROLE;
  int health = 0, inventory_size = 0, num_objs, i;
  Player *play = NULL;
  Space *space = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #p:<id>|<name>|<role>|<graphic description>|<location>|<health>|<armor>|<weapon>|<backpack size>|<num backpack items>|<item1>|<item2>|...
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) != 0) continue;
    toks = strtok(line + 3, "|");
    id_play = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    role = atoi(toks);
    toks = strtok(NULL, "|");
    strcpy(desc, toks);
    toks = strtok(NULL, "|");
    id_location = atol(toks);
    toks = strtok(NULL, "|");
    health = atoi(toks);
    toks = strtok(NULL, "|");
    armor_id = atol(toks);
    toks = strtok(NULL, "|");
    weapon_id = atol(toks);
    toks = strtok(NULL, "|");
    inventory_size = atoi(toks);
    toks = strtok(NULL, "|");
    num_objs = atoi(toks);

    /*creates a new player with the read data, adds it to the array of players
    and sets its location to the corresponding space */
    if (!(play = player_create(id_play))) break;

    /*We first check that the space we are adding the player to exists and set
     * it as discovered*/
    if (!(space = game_get_space(game, id_location))) st = ERROR;
    if (player_set_location(play, id_location) == ERROR) st = ERROR;
    if (space_set_discovered(space, TRUE) == ERROR) st = ERROR;

    if (st == ERROR) {
      player_destroy(play);
      break;
    }

    /*Now we set the parameters read from the file*/
    if (player_set_name(play, name) == ERROR) st = ERROR;
    if (player_set_role(play, role) == ERROR) st = ERROR;
    if (player_set_gdesc(play, desc) == ERROR) st = ERROR;
    if (player_set_health(play, health) == ERROR) st = ERROR;
    if (player_set_armor(play, armor_id) == ERROR) st = ERROR;
    if (player_set_weapon(play, weapon_id) == ERROR) st = ERROR;
    if (player_set_inventory_size(play, inventory_size) == ERROR) st = ERROR;

    /*Reads and adds the objects in the players inventory*/
    for (i = 0; i < num_objs; i++) {
      toks = strtok(NULL, "|");
      obj_id = atol(toks);
      /*Checks if the object exists and ads it to the player*/
      if (!game_get_object(game, obj_id)) st = ERROR;
      if (player_add_object(play, obj_id) == ERROR) st = ERROR;

      if (st == ERROR) break;
    }

    if (st == ERROR) {
      player_destroy(play);
      break;
    }

    if (game_add_player(game, play) == ERROR) {
      player_destroy(play);
      st = ERROR;
      break;
    }
  }

  fclose(file);

  return st;
}

/*Function used in game_create_from_file to load the characters from a file to a game*/
Status game_management_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id_charr = NO_ID, id_location = NO_ID;
  int health = 0;
  Role role = NO_ROLE;
  Character *charr = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #c:<id>|<name>|<role>|<graphic description>|<location>|<health>|<message>
  */
  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id_charr = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      role = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(desc, toks); 
      toks = strtok(NULL, "|");
      id_location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);

      /*creates a new character with the read data, adds it to the array of characters
      and sets its location to the corresponding space */
      charr = character_create(id_charr);
      if (!charr) {
        fclose(file);
        return ERROR;
      }
      if (character_set_name(charr, name) == ERROR) st = ERROR;
      if (character_set_gdesc(charr, desc) == ERROR) st = ERROR;
      if (character_set_health(charr, health) == ERROR) st = ERROR;
      if (character_set_role(charr, role) == ERROR) st = ERROR;
      if (character_set_message(charr, message) == ERROR) st = ERROR;

      if(st == ERROR) {
        character_destroy(charr);
        fclose(file);
        return ERROR;
      }

      if (!game_get_space(game, id_location)) {
        character_destroy(charr);
        fclose(file);
        return ERROR;
      }

      if (game_add_character(game, charr, id_location) == ERROR) {
        character_destroy(charr);
        fclose(file);
        return ERROR;
      }
    }
  }

  fclose(file);
  return OK;
}

/*Function used in game_create_from_file to load the space from a file to a game*/
Status game_management_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, trap_id = NO_ID;
  Bool discovered = FALSE;
  Space *space = NULL;
  Status st = OK; 
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
    toks = strtok(line + 3, "|");
    trap_id = atol(toks);
    toks = strtok(line + 3, "|");
    discovered = (Bool) atol(toks);
  
    /*atol returns 0 in case of error*/
    if(id == 0 || trap_id == 0) {
      st = ERROR;
      break;
    }

    /*creates a new space with the read data and adds it to the game spaces
    list*/
    if (!(space = space_create(id))) st = ERROR;
    if (space_set_name(space, name) == ERROR) st = ERROR;
    if (space_set_trap(space, trap_id) == ERROR) st = ERROR;
    if (space_set_discovered(space, discovered) == ERROR) st = ERROR;

    for (i = 0; i < SP_GD_HGHT && st == OK; i++) {
      toks = strtok(NULL, "|");

      if (toks) {
        if (space_set_gdesc_at(space, toks, i) == ERROR) st = ERROR;
      } else {
        if (space_set_gdesc_at(space, " ", i) == ERROR) st = ERROR;
      }
    }
    
    if(st == ERROR) {
      space_destroy(space);
      fclose(file);
      return ERROR;
    }

    if (game_add_space(game, space) == ERROR) {
      space_destroy(space);
      fclose(file);
      return ERROR;
    }
  }
  
  fclose(file);
  return OK;
}

Status game_management_save_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Space *space = NULL;
  Id space_id = NO_ID, trap_id = NO_ID;
  Bool discovered = FALSE;
  char line[SPACE_LINE], *name = NULL, *gdesc_line = NULL;
  int i = 0, j = 0, num_spaces = -1, len = 0;

  if(!(file = fopen(filename, "a"))) st = ERROR;
  if((num_spaces = game_get_n_spaces(game)) == -1) st = ERROR;

  for(i = 0; i < num_spaces && st == OK; i++) {
    if (!(space = game_get_space_at_pos(game, i))) st = ERROR;
    if ((space_id = space_get_id(space)) == NO_ID) st = ERROR;
    if (!(name = space_get_name(space))) st = ERROR;
    if ((trap_id = space_get_trap(space)) == NO_ID) st = ERROR;
    if (space_get_discovered(space, &discovered) == ERROR) st = ERROR;
    if(st == ERROR) break;

    if (st == ERROR) break;

    /*Saved as #s:<id>|<name>|<trap_id>|<discovered>|*/
    len += sprintf(line, "#s:");
    len += sprintf(line + len, "%ld|", space_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%ld|", trap_id);
    len += sprintf(line + len, "%d|", discovered);

    for(j = 0; j < SP_GD_HGHT; j++) {
      if (!(gdesc_line = space_get_gdesc_at(space, j))) {
        st = ERROR;
        break;
      }
      len += sprintf(line + len, "%s|", gdesc_line);
    }

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");

  fclose(file);

  return st;
}

Status game_management_save_links(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Link *link = NULL;
  Id link_id = NO_ID, orig_id = NO_ID, dest_id = NO_ID;
  Bool open = FALSE;
  Direction dir;
  char line[LINK_LINE], *name = NULL;
  int i = 0, num_links = -1, len = 0;

  if(!(file = fopen(filename, "a"))) st = ERROR;
  if((num_links = game_get_n_links(game)) == -1) st = ERROR;

  for(i = 0; i < num_links && st == OK; i++) {
    if (!(link = game_get_link_at_pos(game, i))) st = ERROR;
    if ((link_id = link_get_id(link)) == NO_ID) st = ERROR;
    if (!(name = link_get_name(link))) st = ERROR;
    if ((orig_id = link_get_orig(link)) == NO_ID) st = ERROR;
    if ((dest_id = link_get_dest(link)) == NO_ID) st = ERROR;
    if ((dir = link_get_direction(link)) == UNK_DIR) st = ERROR;
    if (link_get_open(link, &open) == ERROR) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#l:");
    len += sprintf(line + len, "%ld|", link_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%ld|", orig_id);
    len += sprintf(line + len, "%ld|", dest_id);
    len += sprintf(line + len, "%d|", dir);
    len += sprintf(line + len, "%d|", open);

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_players(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Player *player = NULL;
  Inventory *backpack = NULL;
  Role role = NO_ROLE;
  Id player_id = NO_ID, location = NO_ID, weapon_id = NO_ID, armor_id = NO_ID, obj_id = NO_ID;
  char line[PLAYER_LINE], *name = NULL, *gdesc = NULL;
  int i = 0, j = 0, num_players = -1, len = 0, health = -1, 
  max_back_size = -1, back_n_objs = -1;

  if(!(file = fopen(filename, "a"))) st = ERROR;
  if((num_players = game_get_n_players(game)) == -1) st = ERROR;

  /*#p:<id>|<name>|<role>|<graphic description>|<location>|<health>|<armor>|<weapon>|<backpack size>|<num backpack items>|<item1>|<item2>|...*/
  for(i = 0; i < num_players && st == OK; i++) {
    if (!(player = game_get_player_at(game, i))) st = ERROR;
    if ((player_id = player_get_id(player)) == NO_ID) st = ERROR;
    if (!(name = player_get_name(player))) st = ERROR;
    if ((role = player_get_role(player)) == NO_ROLE) st = ERROR;
    if (!(gdesc = player_get_gdesc(player))) st = ERROR;
    if ((location = player_get_location(player)) == NO_ID) st = ERROR;
    if ((weapon_id = player_get_weapon(player)) == NO_ID) st = ERROR;
    if ((armor_id = player_get_armor(player)) == NO_ID) st = ERROR;
    if ((health = player_get_health(player)) == -1) st = ERROR;
    if (!(backpack = player_get_backpack(player))) st = ERROR;
    if ((max_back_size = inventory_get_max_objects(backpack)) == -1) st = ERROR;
    if ((back_n_objs = inventory_get_num_objects(backpack)) == -1) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#p:");
    len += sprintf(line + len, "%ld|", player_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%d|", role);
    len += sprintf(line + len, "%s|", gdesc);
    len += sprintf(line + len, "%ld|", location);
    len += sprintf(line + len, "%ld|", weapon_id);
    len += sprintf(line + len, "%ld|", armor_id);
    len += sprintf(line + len, "%d|", health);
    len += sprintf(line + len, "%d|", max_back_size);
    len += sprintf(line + len, "%d|", back_n_objs);

    for(j = 0; j < back_n_objs; j++) {
      if ((obj_id = inventory_get_object_at_pos(backpack, j)) == NO_ID) {
        st = ERROR;
        break;
      }
      len += sprintf(line + len, "%ld|", obj_id);
    }

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_characters(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Character *character = NULL;
  Role role = NO_ROLE;
  Id character_id = NO_ID, location = NO_ID;
  char line[CHARACTER_LINE], *name = NULL, *gdesc = NULL, *message = NULL;
  int i = 0, num_characters = -1, len = 0, health = -1;

  if(!(file = fopen(filename, "a"))) st = ERROR;
  if((num_characters = game_get_n_characters(game)) == -1) st = ERROR;

  /*#c:<id>|<name>|<role>|<graphic description>|<location>|<health>|<message>*/
  for(i = 0; i < num_characters && st == OK; i++) {
    if (!(character = game_get_character_at_pos(game, i))) st = ERROR;
    if ((character_id = character_get_id(character)) == NO_ID) st = ERROR;
    if (!(name = character_get_name(character))) st = ERROR;
    if ((role = character_get_role(character)) == NO_ROLE) st = ERROR;
    if (!(gdesc = character_get_gdesc(character))) st = ERROR;
    if ((location = game_get_character_location(game, character_id)) == NO_ID) st = ERROR;
    if ((health = character_get_health(character)) == -1) st = ERROR;
    if (!(message = character_get_message(character))) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#c:");
    len += sprintf(line + len, "%ld|", character_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%d|", role);
    len += sprintf(line + len, "%s|", gdesc);
    len += sprintf(line + len, "%ld|", location);
    len += sprintf(line + len, "%d|", health);
    len += sprintf(line + len, "%s|", message);

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_objects(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Object *object = NULL;
  Id object_id = NO_ID, class_id = NO_ID, location_id = NO_ID;
  char line[OBJECT_LINE];
  int i = 0, num_objects = -1, len = 0;

  if(!(file = fopen(filename, "a"))) st = ERROR;
  if((num_objects = game_get_n_objects(game)) == -1) st = ERROR;

  /*#o:<id>|<class_id>|<initial pos>*/
  for(i = 0; i < num_objects && st == OK; i++) {
    if (!(object = game_get_object_at_pos(game, i))) st = ERROR;
    if ((object_id = object_get_id(object)) == NO_ID) st = ERROR;
    if ((class_id = object_get_class_id(object)) == NO_ID) st = ERROR;
    if ((location_id = game_get_object_location(game, object_id)) == NO_ID) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#o:");
    len += sprintf(line + len, "%ld|", object_id);
    len += sprintf(line + len, "%ld|", class_id);
    len += sprintf(line + len, "%ld|", location_id);

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_classes(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Class *class = NULL;
  Id class_id = NO_ID, dependency = NO_ID, open = NO_ID;
  char line[CLASS_LINE], *name = NULL, *desc = NULL;
  Tag tag;
  Bool movable = FALSE;
  int i = 0, num_classes = -1, len = 0, use_value = -1, luck = -1;

  if (!(file = fopen(filename, "a"))) st = ERROR;
  if ((num_classes = game_get_n_classes(game)) == -1) st = ERROR;

  /*#k:<id>|<tag>|<name>|<description>|<use_value>|<movable>|<dependency>|<open>|<luck>*/
  for (i = 0; i < num_classes && st == OK; i++) {
    if (!(class = game_get_class_at_pos(game, i))) st = ERROR;
    if ((class_id = object_class_get_id(class)) == NO_ID) st = ERROR;
    if ((tag = object_class_get_tag(class)) == NO_TAG) st = ERROR;
    if (!(name = object_class_get_name(class))) st = ERROR;
    if (!(desc = object_class_get_desc(class))) st = ERROR;
    if ((use_value = object_class_get_use_value(class)) == -1) st = ERROR;
    if ((movable = object_class_get_movable(class)) == FALSE && st == OK) st = OK;
    if ((dependency = object_class_get_dependency(class)) == NO_ID) st = ERROR;
    if ((open = object_class_get_open(class)) == NO_ID) st = ERROR;
    if ((luck = object_class_get_luck(class)) == -1) st = ERROR;

    if (st == ERROR) break;

    len += sprintf(line, "#k:");
    len += sprintf(line + len, "%ld|", class_id);
    len += sprintf(line + len, "%d|", tag);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%s|", desc);
    len += sprintf(line + len, "%d|", use_value);
    len += sprintf(line + len, "%d|", movable);
    len += sprintf(line + len, "%ld|", dependency);
    len += sprintf(line + len, "%ld|", open);
    len += sprintf(line + len, "%d|", luck);

    fprintf(file, "%s\n", line);
  }

  fprintf(file, "\n");

  fclose(file);

  return st;
}