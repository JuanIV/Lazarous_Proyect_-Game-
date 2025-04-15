/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

/**
* Private functions
*/

/**
 * @brief It defines the action that the "Unknown" command executes
 * @author Profesores PProg
 *
 * @param game pointer to the game
 */
void game_actions_unknown(Game *game);

/**
 * @brief It defines the action that the "Exit" command executes
 * @author Profesores PProg
 *
 * @param game pointer to the game
 */
void game_actions_exit(Game *game);

/**
 * @brief It defines the action that the "Move" command executes
 * 
 * @param game pointer to the game
 */
void game_actions_move(Game *game);

/**
 * @brief It defines the action that the "Next" command executes
 * @author Profesores PProg
 *
 * @param game pointer to the game
 */
void game_actions_next(Game *game);

/**
 * @brief It defines the action that the "Back" command executes
 * @author Profesores PProg
 *
 * @param game pointer to the game
 */
void game_actions_back(Game *game);

/**
 * @brief It defines the action of taking an object from the players current
 * space
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param name name of the object to take
 */
void game_actions_take(Game *game);

/**
 * @brief It defines the action of dropping an object on the players current
 * space
 * @author Tiago Oselka
 *
 * @param game pointer to the game
 * @param name name of the object to drop
 */
void game_actions_drop(Game *game);

/**
 * @brief It defines the action of going to the east space
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 */
void game_actions_right(Game *game);

/**
 * @brief It defines the action of going to the west space
 * @author Juan Ibáñez
 *
 * @param game Pointer tp the game
 */
void game_actions_left(Game *game);

/**
 * @brief It defines the action of attacking an enemy on your space
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 */
void game_actions_attack(Game *game);

/**
 * @brief It defines the action of chatting with a friendly character
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 */
void game_actions_chat(Game *game);

/**
 * @brief It defines the action of inspecting an object
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 */
void game_actions_inspect(Game *game);

/**
 * @brief It defines the action of using an object
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 */
void game_actions_use(Game *game);

/**
 * @brief Action of using a healing item
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object that is the healer
 * @param trg Pointer to the character being healed
 */
void game_actions_use_healer(Game *game, Object *obj, Character *trg);

/**
 * @brief Action of equipping an armor
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object that is the armor
 * @param trg Pointer to the character that will have the armor
 */
void game_actions_equip_armor(Game *game, Object *obj, Character *trg);

/**
 * @brief Action of equipping a weapon
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object that is the weapon
 * @param trg Pointer to the character that will have the weapon
 */
void game_actions_equip_weapon(Game *game, Object *obj, Character *trg);

/**
 * @brief Action of setting a trap on current space
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object that is the trap
 */
void game_actions_set_trap(Game *game, Object *obj);

/**
     Game actions implementation
*/

/*Sets a given command as last command and executes its corresponding action*/
Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  if(!game || !command) return ERROR;

  /*The message shown must be blank except in case it is required by the last command*/
  if (game_set_last_message(game, " ") == ERROR) return ERROR;

  if (game_set_last_status(game, ERROR) == ERROR) return ERROR;

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case MOVE:
      game_actions_move(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;

    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;

    case CHAT:
      game_actions_chat(game);
      break;
    
    case INSPECT:
      game_actions_inspect(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
* Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

/*The action of exitting is already defined in game_loop*/
void game_actions_exit(Game *game) {
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_move(Game *game) {
  Command *last_cmd = NULL;
  Player *player = NULL;
  Direction direction = UNK_DIR;
  Id cur_space = NO_ID, dest_space = NO_ID;
  Space *space = NULL;
  Object *trap = NULL;
  int curr_health, new_health;
  extern char *dir_to_str[N_DIR][N_DIRT];
  char *dir = NULL;
  int i = 0;

  if(!game) return;

  if(!(last_cmd = game_get_last_command(game))) return;
  dir = command_get_desc(last_cmd);
  if(dir[0] == '\0') return;

  /* compares the command description to any known directions */
  while(direction == UNK_DIR && i < N_DIR) {
    if(!strcasecmp(dir, dir_to_str[i][DIRS]) || 
       !strcasecmp(dir, dir_to_str[i][DIRL])) {
      direction = i + UNK_DIR;
    }else {
      i++;
    }
  }
  /* if no valid direction is found, the function returns */
  if(direction == UNK_DIR) return;

  if(!(player = game_get_player(game))) return;
  if((cur_space = player_get_location(player)) == NO_ID) return;

  /* checks if the connection exists and then whether it's opened  */
  dest_space = game_get_connection(game, cur_space, direction);
  if(dest_space == NO_ID) return;
  if(game_connection_is_open(game, cur_space, direction) == FALSE) {
    game_set_last_message(game, "The path is blocked...");
    return;
  }

  /* moves the player to the destination */
  if(player_set_location(player, dest_space) == ERROR) return;

  space = game_get_space(game, game_get_player_location(game));
  space_set_discovered(space, TRUE);

  /*Explode the trap if there is one*/
  if(space_get_trap(space) != NO_ID){
    trap = game_get_object(game, space_get_trap(space));
  } if(trap && /*ACTIVAR SOLO SI LA TRAMPA ES DEL EQUIPO OPUESTO(FALTA IMPLEMENTACION DE EQUIPOS)*/){
    curr_health = player_get_health(player);
    new_health = curr_health - object_get_use_value(trap);

    if(new_health <= 0) player_set_health(player, 0);
    else player_set_health(player,new_health);

    game_set_last_message(game, "A trap was activated! Ouch!");
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_take(Game *game) {
  Id obj_id = NO_ID, obj_location = NO_ID;
  Id play_location = NO_ID;
  Player *player = NULL;
  Space *cur_space = NULL;
  Command *last_cmd = NULL;
  char *name = NULL;

  if (!game) return; 
  
  /*Gets the name of the object to take from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(name = command_get_desc(last_cmd))) return;

  /*Checks wheter the inventory of the player is full or not*/
  if (!(player = game_get_player(game))) return;
  if (player_inventory_is_full(player) == TRUE) return;

  obj_id = game_get_obj_id_from_name(game, name);
  if (obj_id == NO_ID) return;
  

  /*Gets their location*/
  play_location = game_get_player_location(game);
  obj_location = game_get_object_location(game, obj_id);

  if (play_location == NO_ID || obj_location == NO_ID) return;

  if (play_location != obj_location) return;

  cur_space = game_get_space(game, play_location);
  if (!cur_space) return;
  
  if (player_add_object(player, obj_id) == ERROR) return;

  if (space_remove_object(cur_space, obj_id) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_drop(Game *game) {
  Command *last_cmd = NULL;
  char *name = NULL;
  Id obj_id;
  Id player_location;
  Player *player = NULL;
  Space *cur_space = NULL;

  if (!game) return;

  /*Gets the name of the object to drop from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(name = command_get_desc(last_cmd))) return;

  /*Get the object from the given name*/
  obj_id = game_get_obj_id_from_name(game, name);
  if (obj_id == NO_ID) return;

  /*Get the player*/
  player = game_get_player(game);
  if (!player) return;

  /*If the player does not posses that object, nothig happens*/
  if(player_has_object(player,obj_id) == FALSE) return;

  /*Get the space in which the player stands*/
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return;

  cur_space = game_get_space(game, player_location);
  if (!cur_space) return;


  if (space_is_full(cur_space) == TRUE) return;
  if (space_add_object(cur_space, obj_id) == ERROR) return;
  if (player_delete_object(player,obj_id) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_attack(Game *game) {
  Space *current_space = NULL;
  Character *charr = NULL;
  Player *play = NULL;
  int dice, charr_health, player_health;

  if (!game) return;

  /*Error checking inside game_get_space and game_get_player_location*/
  current_space = game_get_space(game, game_get_player_location(game));
  if (!current_space) return;

  /*Cheking for NO_ID character or any error inside game_get_character*/
  /*If there si no character at the players location nothing happens*/
  charr = game_get_character(game, space_get_character(current_space));
  if (!charr) return;

  /*Error check inside game_get_player*/
  play = game_get_player(game);
  if (!play) return;

  /*Attack happens only if the character is not friendly and alive*/

  if (character_get_friendly(charr) == TRUE) {
    game_set_last_message(game, "It seems friendly. No reason to fight.");
    return;
  }

  if (character_get_health(charr) <= 0) return;

  dice = rand() % ATK_RNG;

  /*If we get a number high enough, the character gets damaged. Else, the
   * player does*/
  if (dice >= ATK_WIN) {
    if((charr_health = character_get_health(charr)) == -1) return;
    if (character_set_health(charr, charr_health - 1) == ERROR) return;
    if(character_get_health(charr) > 0) {
      switch (rand() % 4){
      case 0:
        if(game_set_last_message(game, "I got your head, next you will be dead")== ERROR) return;
        break;
      case 1:
        if(game_set_last_message(game, "I made you bleed, in a moment you will    be buried deep")== ERROR) return;
        break;
      case 2:
        if(game_set_last_message(game, "I attacked you just beacause, so don't    have remorse")== ERROR) return;
        break;
      case 3:
        if(game_set_last_message(game, "I saw you future, it's filled with        torture")== ERROR) return;
        break;
      default:
        break;
      }
    }else {
      switch (rand() % 4){
      case 0:
        if(game_set_last_message(game, "Aw! You are dead, with your body the      worms will be fed'")== ERROR) return;
        break;
      case 1:
        if(game_set_last_message(game, "Your miserable life is over, but still    no one bother")== ERROR) return;
        break;
      case 2:
        if(game_set_last_message(game, "I killed you so easily, you're welcome    for finishing your misery")== ERROR) return;
        break;
      case 3:
        if(game_set_last_message(game, "You died by my hand, you were a loser     with no friends")== ERROR) return;
        break;
      default:
        break;
      }
    }

  } else {
    if((player_health = player_get_health(play)) == -1) return;
    if (player_set_health(play, player_health - 1) == ERROR) return;

    if(player_get_health(play) > 0) {
      switch (rand() % 2){
      case 0:
        if(game_set_last_message(game, "You got attacked by something strange...  Try to get revenge!!")== ERROR) return;
        break;
      case 1:
        if(game_set_last_message(game, "You just took a blow, it seems that you   were too slow")== ERROR) return;
      default:
        break;
      }
    }      
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_chat(Game *game) {
  Space *current_space = NULL;
  Character *charr = NULL;

  if (!game) return;

  /*Error checking inside game_get_space and game_get_player_location*/
  current_space = game_get_space(game, game_get_player_location(game));
  if (!current_space) return;

  /*Cheking for NO_ID character or any error inside game_get_character*/
  /*If there si no character at the players location nothing happens*/
  charr = game_get_character(game, space_get_character(current_space));
  if (!charr) return;

  /*Something happens only if the character is friendly*/
  if (character_get_friendly(charr) == FALSE) {
    game_set_last_message(game, "I dont think its friendly...");
    return;
  }

  if (game_set_last_message(game, character_get_message(charr)) == ERROR)
    return;
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_inspect(Game *game){
  Command *last_cmd = NULL;
  char *name = NULL;
  Id obj_id = NO_ID;
  Object *obj = NULL;
  char *desc = NULL;

  if (!game) return; 
  
  /*Gets the name of the object to inspect from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(name = command_get_desc(last_cmd))) return;

  /*Get the object from the given name*/
  obj_id = game_get_obj_id_from_name(game, name);
  if (obj_id == NO_ID) return;

  obj = game_get_object(game, obj_id);
  if(!obj) return;

  desc = object_get_desc(obj);
  if(!desc) return;

  game_set_last_message(game, desc);

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_use(Game *game){
  Command *last_cmd = NULL;
  char *cmd_desc = NULL, *toks = NULL;
  char *name = NULL, *target = NULL;
  Id obj_id = NO_ID, charr_id = NO_ID;
  Tag obj_tag = NORMAL;
  Character *charr = NULL;
  Object *obj = NULL;

  if (!game) return; 
  
  /*Gets the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  toks = strtok(cmd_desc," \r\n");
  if(!toks) return;
  name = toks;

  toks = strtok(cmd_desc," \r\n");
  if(toks){
    if(strcmp(toks,"over")){
      toks = strtok(cmd_desc," \r\n");
      if(!toks) return;
      target = toks;
    }
  }

  /*Get the object from the given name*/
  obj_id = game_get_obj_id_from_name(game, name);
  if (obj_id == NO_ID) return;

  obj = game_get_object(game, obj_id);
  if(!obj) return;

  obj_tag = object_get_tag(obj);

  /*Get the character if a name is given*/
  if(target){
    charr_id = game_get_charr_id_from_name(game,target);
    if(charr_id == NO_ID) return;

    charr = game_get_character(game, charr_id);
    if(!charr) return;
  }

  switch(obj_tag){
    case NORMAL:
      break;
    case HEALER:
      game_actions_use_healer(game,obj,charr);
      break;
    case WEAPON:
      game_actions_equip_weapon(game,obj,charr);
      break;
    case ARMOR:
      game_actions_equip_armor(game,obj,charr);
      break;
    case TRAP:
      game_actions_set_trap(game,obj);
      break;
    default:
      break;
  }
}

void game_actions_use_healer(Game *game, Object *obj, Character *trg){
  int current_health = 0, new_health = 0;
  Player *player = NULL;

  if(!game || !obj) return;

  if(trg){
    current_health = character_get_health(trg);

    if(current_health <= 0) return;

    new_health = current_health + object_get_use_value(obj);
    if(new_health <= 0) character_set_health(trg, 0);
    else character_set_health(trg, new_health);
  } else {
    player = game_get_player(game);
    if(!player) return;

    current_health = player_get_health(player);

    if(current_health <= 0) return;

    new_health = current_health + object_get_use_value(obj);
    if(new_health <= 0) player_set_health(player, 0);
    else player_set_health(player, new_health);
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_equip_armor(Game *game, Object *obj, Character *trg){
  Id obj_id = NO_ID;
  Player *player = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  if(!player || obj_id == NO_ID) return;

  if(trg){
    if(character_set_armor(trg,obj_id)==ERROR) return;
    if(player_delete_object(player,obj_id) == ERROR) return;
  } else {
    if(player_set_armor(player,obj_id)==ERROR) return;
    if(player_delete_object(player,obj_id) == ERROR) return;
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_equip_weapon(Game *game, Object *obj, Character *trg){
  Id obj_id = NO_ID;
  Player *player = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  if(!player || obj_id == NO_ID) return;

  if(trg){
    if(character_set_weapon(trg,obj_id)==ERROR) return;
    if(player_delete_object(player,obj_id) == ERROR) return;
  } else {
    if(player_set_weapon(player,obj_id)==ERROR) return;
    if(player_delete_object(player,obj_id) == ERROR) return;
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_set_trap(Game *game, Object *obj){
  Id obj_id = NO_ID;
  Player *player = NULL;
  Space *curr_sp = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  curr_sp = game_get_space(game, game_get_player_location(game));
  if(!player || obj_id == NO_ID || !curr_sp) return;

  /*If there is already a trap, we cant set another one*/
  if(space_get_trap(curr_sp) != NO_ID) return;

  if(space_set_trap(curr_sp,obj_id) == ERROR) return;
  if(player_delete_object(player,obj_id) == ERROR) return;
  
  if (game_set_last_status(game, OK) == ERROR) return;
}
