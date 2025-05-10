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

/*############################ GAME LOADING FUNCTIONS ############################*/

/*Function used in game_create_from_file to load the space from a file to a game*/
Status game_management_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[SPACE_LINE +1] = "";
  char name[WORD_SIZE + 1] = "";
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
  while (fgets(line, SPACE_LINE, file)) {
    if (strncmp("#s:", line, 3) != 0) continue;
    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    trap_id = atol(toks);
    toks = strtok(NULL, "|");
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
      break;
    }

    if (game_add_space(game, space) == ERROR) {
      space_destroy(space);
      st = ERROR;
      break;
    }
  }
  
  fclose(file);
  
  if (game_get_n_spaces(game) <= 0) st = ERROR;

  return st;
}

Status game_management_load_minimap(Game *game, const char *filename) {
  FILE *file = NULL;
  char line[SPACE_LINE];
  char *toks = NULL;
  int floor = 0, i = 0;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, SPACE_LINE, file)) {
    if (strncmp("#v:", line, 3) != 0) continue;
    toks = strtok(line + 3, "!");
    floor = atol(toks);

    if (floor < 0) {
      st = ERROR;
      break;
    }

    i = 0;

    while (toks && st == OK) {
      toks = strtok(NULL, "!");

      if (toks) {
        if (game_set_minimap_at(game, toks, i, floor) == ERROR) st = ERROR;
      } else {
        if (game_set_minimap_at(game, " ", i, floor) == ERROR) st = ERROR;
      }

      i++;
    }  
  }

  fclose(file);
  return st;
}

/*Function used in game_create_from_file to load the links from a file to a game*/
Status game_management_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[LINK_LINE + 1] = "";
  char name[WORD_SIZE + 1] = "";
  char *toks = NULL;
  Id id = NO_ID, orig = NO_ID, dest = NO_ID;
  Direction dir = UNK_DIR;
  Bool open = FALSE, locked = TRUE, connected = FALSE;
  Role use_role = NO_ROLE, open_role = NO_ROLE;
  Link *link = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #l:<id>|<name>|<origin id>|<destination id>|<direction>|<open or closed>|<open_role>|<use_role>|
  */
  while (fgets(line, LINK_LINE, file)) {
    if (strncmp("#l:", line, 3) != 0) continue;
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
    toks = strtok(NULL, "|");
    locked = atol(toks);
    toks = strtok(NULL, "|");
    connected = atol(toks);
    toks = strtok(NULL, "|");
    open_role = atol(toks);
    toks = strtok(NULL, "|");
    use_role = atol(toks);

    /*creates a new link with the read data and adds it to the game links list*/
    link = link_create(id);
    if (!link) return ERROR;
    if (link_set_name(link, name) == ERROR) st = ERROR;
    if (link_set_orig(link, orig) == ERROR) st = ERROR;
    if (link_set_dest(link, dest) == ERROR) st = ERROR;
    if (link_set_direction(link, dir) == ERROR) st = ERROR;
    if (link_set_open(link, open) == ERROR) st = ERROR;
    if (link_set_locked(link, locked) == ERROR) st = ERROR;
    if (link_set_connected(link, connected) == ERROR) st = ERROR;
    if (link_set_open_role(link, open_role) == ERROR) st = ERROR;
    if (link_set_use_role(link, use_role) == ERROR) st = ERROR;

    if (st == ERROR) {
      link_destroy(link);
      break;
    }

    if (game_add_link(game, link) == ERROR) {
      link_destroy(link);
      st = ERROR;
      break;
    }
  }

  fclose(file);

  if (game_get_n_links(game) < 0) st = ERROR;

  return st;
}

/*Loads the classes from a file to a game*/
Status game_management_load_classes(Game *game, char *filename){
  FILE *file = NULL;
  char line[CLASS_LINE + 1] = "";
  char name[WORD_SIZE + 1] = "";
  char desc[OBJ_DESC_MX + 1] = "";
  char *toks = NULL;
  Tag tag;
  Bool movable;
  Id class_id, dependency, open;
  Class *class = NULL;
  int i, luck;
  Status st = OK;

  if(!game || !filename) return ERROR;

  if(!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #k:<id>|<tag>|<name>|<description>|<movable>|<dependency>|<open>|<luck>|<close_up> 
  */
  while(fgets(line, CLASS_LINE, file)){
    if (strncmp("#k:", line, 3) != 0) continue;
    toks = strtok(line + 3, "|");
    class_id = atol(toks);
    toks = strtok(NULL, "|");
    tag = atol(toks);
    toks = strtok(NULL, "|");
    sprintf(name, "%.*s", WORD_SIZE, toks);
    toks = strtok(NULL, "|");
    sprintf(desc, "%.*s", OBJ_DESC_MX, toks);
    toks = strtok(NULL, "|");
    movable = atol(toks);
    toks = strtok(NULL, "|");
    dependency = atol(toks);
    toks = strtok(NULL, "|");
    open = atol(toks);
    toks = strtok(NULL, "|");
    luck = atol(toks);

    if (!(class = class_create(class_id))) {
      fclose(file);
      return ERROR;
    }

    if (class_set_tag(class, tag) == ERROR) st = ERROR;
    if (class_set_name(class, name) == ERROR) st = ERROR;
    if (class_set_desc(class, desc) == ERROR) st = ERROR;
    if (class_set_movable(class, movable) == ERROR) st = ERROR;
    if (class_set_dependency(class, dependency) == ERROR) st = ERROR;
    if (class_set_open(class, open) == ERROR) st = ERROR;
    if (class_set_luck(class, luck) == ERROR) st = ERROR;

    for (i = 0; i < POV_HGHT && st == OK; i++) {
      toks = strtok(NULL, "|");

      if (toks) {
        if (class_set_closeup_at_pos(class, i, toks) == ERROR) st = ERROR;
      } else {
        if (class_set_closeup_at_pos(class, i, " ") == ERROR) st = ERROR;
      }
    }

    if (st == ERROR) {
      class_destroy(class);
      break;
    }

    if (game_add_class(game, class) == ERROR) {
      class_destroy(class);
      st = ERROR;
      break;
    }
  }

  fclose(file);

  if (game_get_n_classes(game) < 0) st = ERROR;

  return st;
}

/*Function used in game_create_from_file to load the objects from a file to a game*/
Status game_management_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[OBJECT_LINE + 1] = "";
  char *toks = NULL;
  Id obj_id, class_id, location_id;
  Status st = OK;
  Role role = NO_ROLE;
  Class *class = NULL;
  Object *object = NULL;
  Space *space = NULL;
  int use_value;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #o:<id>|<class_id>|<initial pos>|<role>|<use_value>|
  */
  while (fgets(line, OBJECT_LINE, file)) {
    if (strncmp("#o:", line, 3) != 0) continue;
    toks = strtok(line + 3, "|");
    obj_id = atol(toks);
    toks = strtok(NULL, "|");
    class_id = atol(toks);
    toks = strtok(NULL, "|");
    location_id = atol(toks);
    toks = strtok(NULL, "|");
    role = atoi(toks);
    toks = strtok(NULL, "|");
    use_value = atoi(toks);

    /*creates a new object with the read data, adds it to the array of objects
    and to the set of objects inside its corresponding space */

    if (!(object = object_create(obj_id))) {
      fclose(file);
      return ERROR;
    }

    if (!(class = game_get_class(game, class_id))) st = ERROR;
    if (object_set_class_id(object, class_id) == ERROR) st = ERROR;
    if (location_id != NO_ID) {
      if (!(space = game_get_space(game, location_id))) st = ERROR;
      if (space_add_object(space, obj_id) == ERROR) st = ERROR;
    }
    if(object_set_role(object, role) == ERROR) st = ERROR;
    if (object_set_use_value(object, use_value) == ERROR) st = ERROR;
    
    if (st == ERROR) {
      object_destroy(object);
      break;
    }
    
    if (game_add_object(game, object) == ERROR) {
      object_destroy(object);
      st = ERROR;
      break;
    }
    
  }

  fclose(file);

  if (game_get_n_objects(game) < 0) st = ERROR;

  return st;
}

/*Function used in game_create_from_file to load the characters from a file to a game*/
Status game_management_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[CHARACTER_LINE + 1] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id_charr = NO_ID, id_location = NO_ID, following = NO_ID, armor = NO_ID, weapon = NO_ID;
  int i, health = 0, damage = 0;
  Role role = NO_ROLE;
  Character *charr = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #c:<id>|<name>|<role>|<graphic description>|<location>|<health>|<damage>|<following>|<weapon>|<armor>|<message>|<closeup>
  */
  while (fgets(line, CHARACTER_LINE, file)) {
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
      damage = atoi(toks);
      toks = strtok(NULL, "|");
      following = atol(toks);
      toks = strtok(NULL, "|");
      weapon = atol(toks);
      toks = strtok(NULL, "|");
      armor = atol(toks);
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
      if (character_set_damage(charr, damage) == ERROR) st = ERROR;
      if (character_set_role(charr, role) == ERROR) st = ERROR;
      if (character_set_following(charr, following) == ERROR) st = ERROR;
      if (character_set_armor(charr, armor) == ERROR) st = ERROR;
      if (character_set_weapon(charr, weapon) == ERROR) st = ERROR;
      if (character_set_message(charr, message) == ERROR) st = ERROR;

      /*Sets the close up of the character*/
      for (i = 0; i < POV_HGHT && st == OK; i++) {
        toks = strtok(NULL, "|");
  
        if (toks) {
          if (character_set_closeup_at_pos(charr, i, toks) == ERROR) st = ERROR;
        } else {
          if (character_set_closeup_at_pos(charr, i, " ") == ERROR) st = ERROR;
        }
      }
      
      if(st == ERROR) {
        character_destroy(charr);
        break;
      }

      if (game_add_character(game, charr, id_location) == ERROR) {
        character_destroy(charr);
        st = ERROR;
        break;
      }
    }
  }

  fclose(file);

  if (game_get_n_characters(game) < 0) st = ERROR;

  return st;
}

/*Function used in game_create_from_file to load the players from a file to a game*/
Status game_management_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[PLAYER_LINE + 1] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = ""; 
  char objective[WORD_SIZE + 1];
  char *toks = NULL;
  Id id_play = NO_ID, id_location = NO_ID, obj_id = NO_ID, armor_id = NO_ID, weapon_id = NO_ID;
  Role role = NO_ROLE;
  int health = 0, inventory_size = 0, num_objs, i, n_players = 0;
  Player *play = NULL;
  Space *space = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  /*
  reads data from the file acording to the next structure:
  #p:<id>|<name>|<role>|<graphic description>|<objective>|<location>|<health>|<armor>|<weapon>|<backpack size>|<num backpack items>|<item1>|<item2>|...|<close up>|
  */
  while (fgets(line, PLAYER_LINE, file)) {
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
    strcpy(objective, toks);
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
    if (player_set_objective(play, objective) == ERROR) st = ERROR;
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

    n_players++;

    for (i = 0; i < POV_HGHT && st == OK; i++) {
      toks = strtok(NULL, "|");

      if (toks) {
        if (player_set_closeup_at(play, i, toks) == ERROR) st = ERROR;
      } else {
        if (player_set_closeup_at(play, i, " ") == ERROR) st = ERROR;
      }
    }

    game_set_last_close_up_at_pos(game, player_get_closeup_at(play, i), n_players - 1, i);
  }

  fclose(file);

  if (game_get_n_players(game) <= 0) st = ERROR;

  return st;
}

Status game_management_load_turn(Game *game, char *filename) {
  FILE *file = NULL;
  int turn = 0, round = 0;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  Status st = OK;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  while(fgets(line, WORD_SIZE, file)) {
    if (strncmp("#t:", line, 3) != 0) continue; 
    toks = strtok(line + 3, "|");
    turn = atoi(toks);
    toks = strtok(NULL, "|");
    round = atoi(toks);

    if(game_set_turn(game, turn) == ERROR) st = ERROR;
    if(game_set_round(game, round) == ERROR) st = ERROR;

    fclose(file);
    
    return st;
  }

  fclose(file);

  return ERROR;
}

Status game_management_load_mode(Game *game, char *filename) {
  FILE *file = NULL;
  Bool deterministic = FALSE;
  char line[WORD_SIZE] = "";
  char *toks = NULL;

  if (!filename || !game) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  while(fgets(line, WORD_SIZE, file)) {
    if (strncmp("#m:", line, 3) != 0) continue; 
    toks = strtok(line + 3, "|");
    deterministic = atoi(toks);

    fclose(file);
    return game_set_deterministic(game, deterministic);
  }

  fclose(file);

  return ERROR;
}

/*############################ GAME SAVING FUNCTIONS ############################*/

Status game_management_save_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Space *space = NULL;
  Id space_id = NO_ID, trap_id = NO_ID;
  Bool discovered = FALSE;
  char line[SPACE_LINE], *name = NULL, *gdesc_line = NULL;
  int i = 0, j = 0, num_spaces = -1, len = 0;

  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_spaces = game_get_n_spaces(game)) == -1) st = ERROR;

  for(i = 0; i < num_spaces && st == OK; i++) {
    if (!(space = game_get_space_at_pos(game, i))) st = ERROR;
    if ((space_id = space_get_id(space)) == NO_ID) st = ERROR;
    if (!(name = space_get_name(space))) st = ERROR;
    if (space_get_trap(space, &trap_id) == ERROR) st = ERROR;
    if (space_get_discovered(space, &discovered) == ERROR) st = ERROR;
    if(st == ERROR) break;

    /*Saved as #s:<id>|<name>|<trap_id>|<discovered>|<gdesc>|*/
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
    len = 0;
  }

  fprintf(file, "\n");

  fclose(file);

  return st;
}

Status game_management_save_minimap(Game *game, const char *filename) {
  FILE *file = NULL;
  Status st = OK;
  char line[SPACE_LINE], *gdesc_line = NULL;
  int i = 0, j = 0;
  int len = 0;

  if (!(file = fopen(filename, "a"))) return ERROR;

  for (i = 0; i < NUM_FLOORS; i++) {
    len += sprintf(line, "#v:%d!", i);

    for (j = 0; j < MINIMAP_HEIGHT; j++) {
      if (!(gdesc_line = game_get_minimap_at(game, j, i))) {
        st = ERROR;
        break;
      }

      len += sprintf(line + len, "%s!", gdesc_line);
    }

    fprintf(file, "%s\n", line);

    len = 0;
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
  Role use_role = NO_ROLE, open_role = NO_ROLE;
  Direction dir;
  char line[LINK_LINE], *name = NULL;
  int i = 0, num_links = -1, len = 0;

  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_links = game_get_n_links(game)) == -1) st = ERROR;

  /*#l:<id>|<name>|<origin id>|<destination id>|<direction>|<open or closed>|*/
  for(i = 0; i < num_links && st == OK; i++) {
    if (!(link = game_get_link_at_pos(game, i))) st = ERROR;
    if ((link_id = link_get_id(link)) == NO_ID) st = ERROR;
    if (!(name = link_get_name(link))) st = ERROR;
    if ((orig_id = link_get_orig(link)) == NO_ID) st = ERROR;
    if ((dest_id = link_get_dest(link)) == NO_ID) st = ERROR;
    if ((dir = link_get_direction(link)) == UNK_DIR) st = ERROR;
    if (link_get_open(link, &open) == ERROR) st = ERROR;
    if ((open_role = link_get_open_role(link)) == NO_ROLE) st = ERROR;
    if ((use_role = link_get_use_role(link)) == NO_ROLE) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#l:");
    len += sprintf(line + len, "%ld|", link_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%ld|", orig_id);
    len += sprintf(line + len, "%ld|", dest_id);
    len += sprintf(line + len, "%d|", dir);
    len += sprintf(line + len, "%d|", open);
    len += sprintf(line + len, "%d|", open_role);
    len += sprintf(line + len, "%d|", use_role);

    fprintf(file, "%s\n", line);
    len = 0;
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
  char line[PLAYER_LINE], *name = NULL, *gdesc = NULL, *objective = NULL, *closeup = NULL;
  int i = 0, j = 0, num_players = -1, len = 0, health = -1, 
  max_back_size = -1, back_n_objs = -1;

  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_players = game_get_n_players(game)) == -1) st = ERROR;

  /*#p:<id>|<name>|<role>|<graphic description>|<location>|<health>|<armor>|<weapon>|<backpack size>|<num backpack items>|<item1>|<item2>|...*/
  for(i = 0; i < num_players && st == OK; i++) {
    if (!(player = game_get_player_at(game, i))) st = ERROR;
    if ((player_id = player_get_id(player)) == NO_ID) st = ERROR;
    if (!(name = player_get_name(player))) st = ERROR;
    if ((role = player_get_role(player)) == NO_ROLE) st = ERROR;
    if (!(gdesc = player_get_gdesc(player))) st = ERROR;
    if (!(objective = player_get_objective(player))) st = ERROR;
    if ((location = player_get_location(player)) == NO_ID) st = ERROR;
    if (player_get_weapon(player, &weapon_id) == ERROR) st = ERROR;
    if (player_get_armor(player, &armor_id) == ERROR) st = ERROR;
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
    len += sprintf(line + len, "%s|", objective);
    len += sprintf(line + len, "%ld|", location);
    len += sprintf(line + len, "%d|", health);
    len += sprintf(line + len, "%ld|", weapon_id);
    len += sprintf(line + len, "%ld|", armor_id);
    len += sprintf(line + len, "%d|", max_back_size);
    len += sprintf(line + len, "%d|", back_n_objs);

    for(j = 0; j < back_n_objs; j++) {
      if ((obj_id = inventory_get_object_at_pos(backpack, j)) == NO_ID) {
        st = ERROR;
        break;
      }
      len += sprintf(line + len, "%ld|", obj_id);
    }

    for (j = 0; j < POV_HGHT && st == OK; j++) {
      if (!(closeup = player_get_closeup_at(player, j))) st = ERROR;

      len += sprintf(line + len, "%s|", closeup);
    }

    fprintf(file, "%s\n", line);
    len = 0;
  }

  fprintf(file, "\n");
  
  fclose(file);

  if (num_players <= 0) st = ERROR;

  return st;
}

Status game_management_save_classes(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Class *class = NULL;
  Tag tag = NO_TAG;
  Id class_id = NO_ID, dependency = NO_ID, open = NO_ID;
  char line[CLASS_LINE], *name = NULL, *desc = NULL, *closeup = NULL;
  int i = 0, j = 0, num_classes = -1, len = 0, luck = -1;
  Bool movable = FALSE;


  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_classes = game_get_n_classes(game)) == -1) st = ERROR;

  /*#k:<id>|<tag>|<name>|<description>|<use_value>|<movable>|<dependency>|<open>|<luck>*/
  for(i = 0; i < num_classes && st == OK; i++) {
    if (!(class = game_get_class_at_pos(game, i))) st = ERROR;
    if ((class_id = class_get_id(class)) == NO_ID) st = ERROR;
    if ((tag = class_get_tag(class)) == NO_TAG) st = ERROR;
    if (!(name = class_get_name(class))) st = ERROR;
    if (!(desc = class_get_desc(class))) st = ERROR;
    if (class_get_movable(class, &movable) == ERROR) st = ERROR;
    if (class_get_dependency(class, &dependency) == ERROR) st = ERROR;
    if (class_get_open(class, &open) == ERROR) st = ERROR;
    if ((luck = class_get_luck(class)) == -1) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#k:");
    len += sprintf(line + len, "%ld|", class_id);
    len += sprintf(line + len, "%d|", tag);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%s|", desc);
    len += sprintf(line + len, "%d|", movable);
    len += sprintf(line + len, "%ld|", dependency);
    len += sprintf(line + len, "%ld|", open);
    len += sprintf(line + len, "%d|", luck); 

    for (j = 0; j < POV_HGHT && st == OK; j++) {
      if (!(closeup = class_get_closeup_at_pos(class, j))) st = ERROR;

      len += sprintf(line + len, "%s|", closeup);
    }

    fprintf(file, "%s\n", line);
    len = 0;
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_objects(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Object *obj = NULL;
  Role role = NO_ROLE;
  Id obj_id = NO_ID, class_id = NO_ID, loc = NO_ID;
  char line[OBJECT_LINE];
  int i = 0, num_objects = -1, use_value = -1, len = 0;


  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_objects = game_get_n_objects(game)) == -1) st = ERROR;

  /*#o:<id>|<class_id>|<initial pos>|<role>*/
  for(i = 0; i < num_objects && st == OK; i++) {
    if (!(obj = game_get_object_at_pos(game, i))) st = ERROR;
    if ((obj_id = object_get_id(obj)) == NO_ID) st = ERROR;
    if ((class_id = object_get_class_id(obj)) == NO_ID) st = ERROR;
    loc = game_get_object_location(game, obj_id);
    if ((role = object_get_role(obj)) == NO_ROLE) st = ERROR;
    if ((use_value = object_get_use_value(obj)) == -1) st = ERROR;

    if(st == ERROR) break;

    len += sprintf(line, "#o:");
    len += sprintf(line + len, "%ld|", obj_id);
    len += sprintf(line + len, "%ld|", class_id);
    len += sprintf(line + len, "%ld|", loc);
    len += sprintf(line + len, "%d|", role);
    len += sprintf(line + len, "%d|", use_value);

    fprintf(file, "%s\n", line);
    len = 0;
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
  Id charr_id = NO_ID, location = NO_ID, weapon_id = NO_ID, armor_id = NO_ID, following = NO_ID;
  char line[CHARACTER_LINE], *name = NULL, *gdesc = NULL, *msg = NULL, *closeup = NULL;
  int i = 0, j = 0, num_characters = -1, len = 0, health = -1, damage = -1;

  if(!(file = fopen(filename, "a"))) return ERROR;
  if((num_characters = game_get_n_characters(game)) == -1) st = ERROR;
  
  /*#c:<id>|<name>|<role>|<graphic description>|<location>|<health>|<damage>|<following>|<weapon>|<armor>|<message>*/
  for(i = 0; i < num_characters && st == OK; i++) {
    if (!(character = game_get_character_at_pos(game, i))) st = ERROR;
    if ((charr_id = character_get_id(character)) == NO_ID) st = ERROR;
    if (!(name = character_get_name(character))) st = ERROR;
    if ((role = character_get_role(character)) == NO_ROLE) st = ERROR;
    if (!(gdesc = character_get_gdesc(character))) st = ERROR;
    if ((location = game_get_character_location(game, charr_id)) == NO_ID) st = ERROR;
    if (character_get_following(character, &following) == ERROR) st = ERROR;
    if ((health = character_get_health(character)) == -1) st = ERROR;
    if ((damage = character_get_damage(character)) == -1) st = ERROR;
    if (character_get_weapon(character, &weapon_id) == ERROR) st = ERROR;
    if (character_get_armor(character, &armor_id) == ERROR) st = ERROR;
    if (!(msg = character_get_message(character))) st = ERROR;
    
    if(st == ERROR) break;

    len += sprintf(line, "#c:");
    len += sprintf(line + len, "%ld|", charr_id);
    len += sprintf(line + len, "%s|", name);
    len += sprintf(line + len, "%d|", role);
    len += sprintf(line + len, "%s|", gdesc);
    len += sprintf(line + len, "%ld|", location);
    len += sprintf(line + len, "%d|", health);
    len += sprintf(line + len, "%d|", damage);
    len += sprintf(line + len, "%ld|", following);
    len += sprintf(line + len, "%ld|", weapon_id);
    len += sprintf(line + len, "%ld|", armor_id);
    len += sprintf(line + len, "%s|", msg);    

    for (j = 0; j < POV_HGHT && st == OK; j++) {
      if (!(closeup = character_get_closeup_at_pos(character, j))) st = ERROR;

      len += sprintf(line + len, "%s|", closeup);
    }

    fprintf(file, "%s\n", line);
    len = 0;
  }

  fprintf(file, "\n");
  
  fclose(file);

  return st;
}

Status game_management_save_turn(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  int turn = 0;

  if(!game || !filename) return ERROR;

  if(!(file = fopen(filename, "a"))) return ERROR;

  if ((turn = game_get_turn(game)) == -1) st = ERROR;

  if (st == OK) fprintf(file, "#t:%d|\n\n", turn);

  fclose(file);

  return st;
}

Status game_management_save_mode(Game *game, char *filename) {
  FILE *file = NULL;
  Status st = OK;
  Bool deterministic = FALSE;

  if (!game || !filename) return ERROR;

  if (!(file = fopen(filename, "a"))) return ERROR;

  if (game_get_deterministic(game, &deterministic) == ERROR) st = ERROR;

  if (st == OK) fprintf(file, "#m:%d|\n\n", deterministic);

  fclose(file);

  return st;
}

Status game_management_load_interface_data(Game *game, char *filename) {
  FILE *file = NULL;
  char line[MESG_SIZE + EXTRAS + 1] = "";
  char *token = NULL;
  int i = 0, j = 0;
  char *closeup = NULL;
  char msg[MESG_SIZE + EXTRAS];
  Command *cmd = NULL;
  CommandCode cmd_code = NO_CMD;
  Status cmd_status = ERROR, st = OK;
  Bool visibility = FALSE;
  Id sender = NO_ID;
  Type type = NO_TYPE;

  if (!game || !filename) return ERROR;

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, MESG_SIZE + EXTRAS, file) && st == OK) {
    if (strncmp("#i:", line, 4) == 0) {
      if((token = strtok(line + 3, "|"))) i = atoi(token);
      else st = ERROR;
      
      /*Close ups*/
      for (j = 0; j < POV_HGHT && st == OK; j++) {
        if (!(token = strtok(NULL, "|"))) st = ERROR;
        closeup = token;
        if (game_set_last_close_up_at_pos(game, closeup, i, j) == ERROR) st = ERROR;
      }

      /*Commands*/
      for (j = 0; j < NUM_CMDS && st == OK; j++) {
        if ((token = strtok(NULL, "|"))) cmd_code = atoi(token);
        else st = ERROR;

        if (((token = strtok(NULL, "|")))) cmd_status = atoi(token);
        else st = ERROR;

        if (!(cmd = game_get_command_at_pos(game, i, j))) {
          st = ERROR;
          continue;
        }
        if (!cmd || command_set_code(cmd, cmd_code) == ERROR ||
            command_set_status(cmd, cmd_status) == ERROR) st = ERROR;
      }

      if (st == ERROR) break;
      /*#msg: <pos_player>|<pos_message>|<visibility>|<sender>|<type>|<message>|*/
    } else if (strncmp("#msg:", line, 5) == 0) {
      if ((token = strtok(line + 5, "|"))) i = atoi(token);
      else st = ERROR;

      if ((token = strtok(NULL, "|"))) j = atoi(token);
      else st = ERROR;

      if ((token = strtok(NULL, "|"))) visibility = atoi(token);
      else st = ERROR;

      if ((token = strtok(NULL, "|"))) sender = atoi(token);
      else st = ERROR;

      if ((token = strtok(NULL, "|"))) type = (Type) atoi(token);
      else st = ERROR;

      if((token = strtok(NULL, "|"))) strncpy(msg, token, MESG_SIZE);
      else st = ERROR;

      if (st == OK) {
        if (game_set_last_message_at_pos_with_info(game, i, msg, sender, type) == ERROR || 
          game_set_last_message_visibility_at_pos(game, i, j, visibility) == ERROR) st = ERROR;
      }

      if (st == ERROR) break;
    }
  }

  fclose(file);
  return st;
}

Status game_management_save_interface_data(Game *game, char *filename) {
  FILE *file = NULL;
  int num_players = 0, i = 0, j = 0, len = 0;
  char line[MESG_SIZE + EXTRAS] = "";
  char *closeup = NULL;
  char *msg = NULL;
  Command *cmd = NULL;
  CommandCode cmd_code = NO_CMD;
  Status cmd_status = ERROR, st = OK;
  Bool visibility = FALSE;
  Id sender = NO_ID;
  Type type = NO_TYPE;

  if (!game || !filename) return ERROR;

  if (!(file = fopen(filename, "a"))) return ERROR;

  if ((num_players = game_get_n_players(game)) <= 0) {
    fclose(file);
    return ERROR;
  }
  /*#i:<pos in player array>|<close_up>|<command_code>|<command_status>|<command_code>|<command_status>...*/
  for (i = 0; i < num_players && st == OK; i++, len = 0) {
    len = 0;
    len += sprintf(line, "#i:%d|", i);

    for (j = 0; j < POV_HGHT; j++) {
      closeup = game_get_last_close_up_at(game, j);
      len += sprintf(line + len, "%s|", closeup ? closeup : " ");
    }

    for (j = 0; j < NUM_CMDS; j++) {
      cmd = game_get_command_at_pos(game, i, j);
      if (cmd) {
        cmd_code = command_get_code(cmd);
        cmd_status = command_get_status(cmd);
        len += sprintf(line + len, "%d|%d|", cmd_code, cmd_status);
      } else {
        len += sprintf(line + len, "-1|0|"); /*NO_CMD|ERROR|*/
      }
    }

    fprintf(file, "%s\n", line);
  
    /*#msg: <pos_player>|<pos_message>|<visibility>|<sender>|<type>|<message>|*/
  
    for (j = 0; j < NUM_MSGS; j++, len = 0) {
      if (!(msg = game_get_last_message_at_pos(game, i, j))) st = ERROR;
      if ((visibility = game_get_last_message_visibility_at_pos(game, i, j)) == FALSE) {
        len = 0;
        continue;
      }
      if ((sender = game_get_last_message_sender_at_pos(game, i, j)) == NO_ID) st = ERROR;
      type = game_get_last_message_sender_type_at_pos(game, i, j);

      if (st == OK) {
        len += sprintf(line + len, "#msg:%d|%d|%d|%ld|%d|%s|", i, j, visibility, sender, type, msg);
        fprintf(file, "%s\n", line);
      }
    }
  }

  fclose(file);
  return OK;
}
