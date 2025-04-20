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
 * @brief It defines the action of recruiting a character
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_recruit(Game *game);

/**
 * @brief It defines the action of abandoning a character
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_abandon(Game *game);

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
 * @brief It defines the action of saving the game
 * @author Alina Datsko
 *
 * @param game Pointer to the game
 */
void game_actions_save(Game *game);

/**
 * @brief It defines the action of loading a game
 * @author Alina Datsko
 *
 * @param game Pointer to the game
 */
void game_actions_load(Game *game);

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

    case RECRUIT:
      game_actions_recruit(game);
      break;

    case ABANDON:
      game_actions_abandon(game);
      break;

    case USE:
      game_actions_use(game);
      break;

    case SAVE:
      game_actions_save(game);
      break;

    case LOAD:
      game_actions_load(game);
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
  Object *trap = NULL;
  Set *followers = NULL;
  Bool open = FALSE;
  Id cur_id = NO_ID, dest_id = NO_ID, player_id = NO_ID, charr_id = NO_ID;
  Space *cur_space = NULL, *dest_space = NULL;
  extern char *dir_to_str[N_DIR][N_DIRT];
  char *dir = NULL;
  int i = 0, n_followers = -1, cur_health = -1, new_health;

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
  if((player_id = player_get_id(player)) == NO_ID) return;
  if((cur_id = player_get_location(player)) == NO_ID) return;

  /* checks if the connection exists and then whether it's opened  */
  dest_id = game_get_connection(game, cur_id, direction);
  if(dest_id == NO_ID) return;
  if(game_connection_is_open(game, cur_id, direction, &open) == ERROR) return;
  if(open == FALSE) {
    game_set_last_message(game, "The path is blocked...");
    return;
  }

  if(!(dest_space = game_get_space(game, dest_id))) return;
  if(space_set_discovered(dest_space, TRUE) == ERROR) return;

  /* moves the player to the destination */
  if(player_set_location(player, dest_id) == ERROR) return;
  /* moves the characters that follow the player if there are any*/
  if((n_followers = game_get_num_followers(game, game_get_player(game))) == -1) return;
  if(n_followers == 0) {
    if (game_set_last_status(game, OK) == ERROR) return;
    return;
  }

  if(!(cur_space = game_get_space(game, cur_id))) return;
  if(!(followers = game_get_followers(game, player))) return;
  if((n_followers = set_get_num_ids(followers)) == -1) {
    set_destroy(followers);
    return;
  }

  for(i = 0; i < n_followers; i++) {
    if((charr_id = set_get_id_at_pos(followers, i)) == NO_ID) {
      set_destroy(followers);
      return;
    }
    if(space_remove_character(cur_space, charr_id) == ERROR) {
      set_destroy(followers);
      return;
    }
    if(space_add_character(dest_space, charr_id) == ERROR) {
      set_destroy(followers);
      return;
    }
  }
  set_destroy(followers);

  /*Explodes the trap if there is one*/
  if(space_get_trap(dest_space) != NO_ID){
    trap = game_get_object(game, space_get_trap(dest_space));

    if(trap && (object_get_role(trap) != player_get_role(player))){
      cur_health = player_get_health(player);
      new_health = cur_health - object_get_use_value(trap);
      
      /*Damages the player*/
      if(player_set_health(player, new_health) == ERROR) return;
      
      /*Eliminates the trap from the space*/
      if((space_set_trap(dest_space, NO_ID)) == ERROR) return;

      if(game_set_last_message(game, "A trap was activated! Ouch!")) return;
    }
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

  /*Checks whether the inventory of the player is full or not*/
  if (!(player = game_get_player(game))) return;
  if (player_inventory_is_full(player) == TRUE) return;

  obj_id = game_get_obj_id_from_name(game, name);
  if (obj_id == NO_ID) return;
  
  /*Checks whether the object is movable or not*/
  if (object_get_movable(game_get_object(game, obj_id)) == FALSE) return;

  /*Gets their location and error check inside game_get_space*/
  play_location = game_get_player_location(game);
  cur_space = game_get_space(game, play_location);
  if (!cur_space) return;

  obj_location = game_get_object_location(game, obj_id);

  if (play_location == NO_ID || obj_location == NO_ID) return;

  if (play_location != obj_location) return;
  
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


  if (space_objects_is_full(cur_space) == TRUE) return;
  if (space_add_object(cur_space, obj_id) == ERROR) return;
  if (player_delete_object(player,obj_id) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_attack(Game *game) {
  Space *current_space = NULL;
  Character *charr = NULL, *follower = NULL;
  Command *last_cmd = NULL;
  Player *player = NULL;
  Set *followers = NULL;
  Bool friendly = FALSE;
  Id charr_id = NO_ID, damaged_follower = NO_ID, player_loc = NO_ID;
  char *charr_name = NULL, message[MESG_SIZE];
  int dice, charr_health, follower_health, player_health, num_followers = -1, damaged = -1;

  if (!game) return;

  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(charr_name = command_get_desc(last_cmd))) return;

  /*Chacks if the character exists and if its alive*/
  if (!(charr = game_get_character_from_name(game, charr_name))) return;
  if (character_get_health(charr) <= 0) return;
  if((charr_id = character_get_id(charr)) == NO_ID) return;
  if (!(player = game_get_player(game))) return;

  /*Checks if the character and the player are in the same space*/
  if ((player_loc = player_get_location(player)) == NO_ID) return;
  if (!(current_space = game_get_space(game, player_loc))) return;
  if(space_find_character(current_space, charr_id) == FALSE) {
    if (game_set_last_message(game, "This character is out of reach...") == ERROR)return;
    return;
  }

  /*Attack happens only if the character is not friendly and alive*/
  if (game_get_friendly(player_get_role(player), character_get_role(charr), &friendly) == ERROR) return;
  if (friendly == TRUE) {
    if (game_set_last_message(game, "It seems friendly... No need to fight") == ERROR) return;
    return;
  }

  dice = rand() % ATK_RNG;

  /*Checks how many followers the player has*/
  if((num_followers = game_get_num_followers(game, game_get_player(game))) == -1) return;
  
  /*Depending on the number the player or the character looses*/
  if (dice >= ATK_WIN) {
    /*If the character looses, it looses one point of life for each follower that the player has, on top
    of the point lost from the player*/
    if((charr_health = character_get_health(charr)) == -1) return;
    if (character_set_health(charr, charr_health - (num_followers + 1)) == ERROR) return;
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
      if(space_remove_character(current_space, charr_id) == ERROR) return;
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
    /*If the player looses, the player or a character that follows him is damaged randomly*/
    damaged = rand() % (num_followers + 1);

    if(damaged == num_followers) {
      if ((player_health = player_get_health(player)) == -1) return;
      if (player_set_health(player, player_health - 1) == ERROR) return;

      if(player_get_health(player) > 0) {
        switch (rand() % 2){
        case 0:
          if(game_set_last_message(game, "You got attacked by something strange...  Try to get revenge!!")== ERROR) return;
          break;
        case 1:
          if(game_set_last_message(game, "You just took a blow, it seems that you   were too slow")== ERROR) return;
        default:
          break;
        }
      } else {
        if(game_set_last_message(game, "YOU ARE DEAD")== ERROR) return;
      }

    } else {
      /*Else, one of the followers is damaged*/
      if (!(followers = game_get_followers(game, game_get_player(game)))) return;

      if((damaged_follower = set_get_id_at_pos(followers, damaged)) == NO_ID) {
        set_destroy(followers);
        return;
      }
      if (!(follower = game_get_character_from_id(game, damaged_follower))) {
        set_destroy(followers);
        return;
      }

      if ((follower_health = character_get_health(follower)) == -1) {
        set_destroy(followers);
        return;
      }
      if (character_set_health(follower, follower_health - 1) == ERROR) {
        set_destroy(followers);
        return;
      }

      set_destroy(followers);
      
      /*If the character dies, it must stop following the player and a message is shown*/
      if ((follower_health-1) <= 0) {
        if (character_set_following(charr, NO_ID) == ERROR) return;
        if (space_remove_character(current_space, damaged_follower) == ERROR) return;
        sprintf(message, "Sadly your subordinate %s has passed away", character_get_name(follower));
        if (game_set_last_message(game, message) == ERROR) return;
      } else {
        sprintf(message, "Your subordinate %s has been damaged!", character_get_name(follower));
        if (game_set_last_message(game, message) == ERROR) return;
      }
    }    
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_chat(Game *game) {
  Space *current_space = NULL;
  Character *charr = NULL;
  Command *last_cmd = NULL;
  Bool friendly = FALSE;
  Id charr_id = NO_ID, player_loc = NO_ID;
  char *name = NULL;

  if (!game) return;

  /*Error checking inside game_get_space and game_get_player_location*/
  current_space = game_get_space(game, game_get_player_location(game));
  if (!current_space) return;

  /*Gets the name of the character to chat from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(name = command_get_desc(last_cmd))) return;

  /*Checks if the character exists and if its alive*/
  if (!(charr = game_get_character_from_name(game, name))) return;
  if(character_get_health(charr) <= 0) return;
  if((charr_id = character_get_id(charr)) == NO_ID) return;
 
  /*Checks if the character and the player are in the same space*/
  if ((player_loc = game_get_player_location(game)) == NO_ID) return;
  if (!(current_space = game_get_space(game, player_loc))) return;
  if(space_find_character(current_space, charr_id) == FALSE) {
    game_set_last_message(game, "This character is out of reach...");
    return;
  }

  /*Chatting happens only if the character is friendly*/
  if(game_get_friendly(player_get_role(game_get_player(game)), character_get_role(charr), &friendly) == ERROR) return;
  if (friendly == FALSE) {
    game_set_last_message(game, "I dont think its friendly...");
    return;
  }

  if (game_set_last_message(game, character_get_message(charr)) == ERROR) return;
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

void game_actions_recruit(Game *game) {
  Id charr_location = NO_ID, player_id = NO_ID;
  Id play_location = NO_ID, following = NO_ID;
  Command *last_cmd = NULL;
  Bool friendly = FALSE;
  Character *charr = NULL;
  char *charr_name = NULL;

  if (!game) return; 
  
  /*Gets the name of the character to recruit from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(charr_name = command_get_desc(last_cmd))) return;
  if(charr_name[0] == '\0') return;

  if((player_id = player_get_id(game_get_player(game))) == NO_ID) return;
  
  /*Gets the character and checks whether its friendly*/
  if(!(charr = game_get_character_from_name(game, charr_name))) return;
  if(game_get_friendly(player_get_role(game_get_player(game)), character_get_role(charr), &friendly) == ERROR) return;
  if(friendly == FALSE) return;
  if(character_get_following(charr, &following) == ERROR) return;
  if(following != NO_ID) return;

  /*Gets their location and checks if they are at the same space*/
  play_location = game_get_player_location(game);
  charr_location = game_get_character_location(game, character_get_id(charr));
  if (play_location == NO_ID || charr_location == NO_ID) return;
  if (play_location != charr_location) return;


  /*Sets the id of the player the character is going to follow*/
  if(character_set_following(charr, player_id) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_abandon(Game *game) {
  Id player_id = NO_ID;
  Command *last_cmd = NULL;
  Character *charr = NULL;
  Id following = NO_ID;
  char *charr_name = NULL, message[MESG_SIZE];

  if (!game) return; 
  
  /*Gets the name of the character to abandon from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(charr_name = command_get_desc(last_cmd))) return;
  if(charr_name[0] == '\0') return;

  if((player_id = player_get_id(game_get_player(game))) == NO_ID) return;
  
  /*Gets the character and checks whether its alive and if it is following the player*/
  if(!(charr = game_get_character_from_name(game, charr_name))) return;
  if(character_get_health(charr) <= 0) return;
  if(character_get_following(charr, &following) == ERROR) return;
  if(following != player_id) {
    message[0] = '\0';
    sprintf(message, "%s wasn't following you", charr_name);
    game_set_last_message(game, message);
    return;
  }

  /*Sets the Id of the player being followed to NO_ID*/
  if(character_set_following(charr, NO_ID) == ERROR) return;

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
    charr_id = game_get_charr_id_from_name(game, target);
    if(charr_id == NO_ID) return;

    charr = game_get_character_from_id(game, charr_id);
    if(!charr) return;
  }

  switch(obj_tag){
    case NORMAL:
      break;
    case HEALER:
      game_actions_use_healer(game, obj, charr);
      break;
    case WEAPON:
      game_actions_equip_weapon(game, obj, charr);
      break;
    case ARMOR:
      game_actions_equip_armor(game, obj, charr);
      break;
    case TRAP:
      game_actions_set_trap(game, obj);
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
    if(character_set_weapon(trg,obj_id) == ERROR) return;
    if(player_delete_object(player,obj_id) == ERROR) return;
  } else {
    if(player_set_weapon(player,obj_id) == ERROR) return;
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

  /*Sets the trap as one from the player's team*/
  if(object_set_role(obj, player_get_role(player)) == ERROR) return;

  if(player_delete_object(player,obj_id) == ERROR) return;
  
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_save(Game *game) {
  Command *last_cmd = NULL;
  char *cmd_desc = NULL;
  char file_save[WORD_SIZE];
  int len = 0;

  if (!game) return; 
  
  /*Gets the description of the last cmd to name the file*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  if (len >= 4 && strcmp(cmd_desc + len - 4, ".dat") != 0) {
    sprintf(file_save, "%s.dat", cmd_desc);
  }
  else {
    sprintf(file_save, "%s.dat", cmd_desc);
  }

  if (game_save(game, file_save) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_load(Game *game) {
  Command *last_cmd = NULL;
  char *cmd_desc = NULL;
  char file_load[WORD_SIZE];
  int len = 0;

  if (!game) return; 
  
  /*Gets the description of the last cmd to load the file*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  if (len >= 4 && strcmp(cmd_desc + len - 4, ".dat") != 0) {
    sprintf(file_load, "%s.dat", cmd_desc);
  }
  else {
    sprintf(file_load, "%s.dat", cmd_desc);
  }

  if(game_load(game, file_load) == ERROR) return;
  
  if (game_set_last_status(game, OK) == ERROR) return;
}
