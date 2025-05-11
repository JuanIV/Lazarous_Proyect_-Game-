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
 * @brief Defines the range of results you can get when attacking an enemy
 *
 */
#define ATK_RNG 100

/**
 * @brief Defines the minimum number you have to get to land an attack
 *
 */
#define ATK_WIN 20

/**
 * @brief Defines the range of results for an accident to happen
 *
 */
#define ATK_ACC_RNG 1000

/**
 * @brief Defines the minimum number you have to get for an accident to happen
 * while attacking
 *
 */
#define ATK_ACCIDENT 950

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
 * @brief Action of reading a note
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object that is the note
 */
void game_actions_read_note(Game *game, Object *obj);

/**
 * @brief Action of using a switch
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param obj Pointer to the object
 */
void game_actions_use_switch(Game *game, Object *obj);

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
 * @param game Double pointer to the game
 */
void game_actions_load(Game **game);

/**
 * @brief Tries to open a link with or whithout an object
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 */
void game_actions_open_link(Game *game);

/**
 * @brief Closes a link
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 */
void game_actions_close_link(Game *game);

/**
 * @brief Accepts a request. Works paired with game_rules
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_accept(Game *game);

/**
 * @brief Denies a request. Works paired with game_rules
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_deny(Game *game);

/**
 * @brief Command to cooperate with another player
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_cooperate(Game *game);

/**
 * @brief Command to betray your team
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 */
void game_actions_betray(Game *game);

/**
 * @brief It defines the action of using an object
 * @author Alina Datsko
 * 
 * @param game Pointer to the game
 */
void game_actions_view(Game *game);

/**
     Game actions implementation
*/

/*Sets a given command as last command and executes its corresponding action*/
Status game_actions_update(Game **game, Command *command, CommandCode *cmd_code, Bool update) {
  CommandCode cmd;
  Player *player = NULL;
  char *closeup = NULL;
  int i;

  if(!game || !(*game) || !command || !cmd_code) return ERROR;

  player = game_get_player(*game);

  /*The default close up will be the players face*/
  for (i = 0; i < POV_HGHT; i++) {
    if (!(closeup = player_get_closeup_at(player, i))) return ERROR;
    if (game_set_last_close_up(*game, closeup, i) == ERROR) return ERROR;
  }

  if (game_set_last_status(*game, ERROR) == ERROR) return ERROR;

  cmd = command_get_code(command);
  *cmd_code = cmd;

  if(update == FALSE) return OK;

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(*game);
      break;

    case EXIT:
      game_actions_exit(*game);
      break;

    case MOVE:
      game_actions_move(*game);
      break;

    case TAKE:
      game_actions_take(*game);
      break;

    case DROP:
      game_actions_drop(*game);
      break;

    case ATTACK:
      game_actions_attack(*game);
      break;

    case CHAT:
      game_actions_chat(*game);
      break;
    
    case INSPECT:
      game_actions_inspect(*game);
      break;

    case RECRUIT:
      game_actions_recruit(*game);
      break;

    case ABANDON:
      game_actions_abandon(*game);
      break;

    case USE:
      game_actions_use(*game);
      break;

    case SAVE:
      game_actions_save(*game);
      break;

    case LOAD:
      game_actions_load(game);
      break;
      
    case OPEN:
      game_actions_open_link(*game);
      break;

    case CLOSE:
      game_actions_close_link(*game);
      break;

    case SKIP:
      game_set_last_status(*game, OK);
      break;

    case ACCEPT:
      game_actions_accept(*game);
      break;

    case DENY:
      game_actions_deny(*game);
      break;

    case COOPERATE:
      game_actions_cooperate(*game);
      break;

    case BETRAY:
      game_actions_betray(*game);

    case VIEW:
      game_actions_view(*game);
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
  Role link_role = NO_ROLE, player_role = NO_ROLE;
  Id cur_id = NO_ID, dest_id = NO_ID, player_id = NO_ID, charr_id = NO_ID, trap_id = NO_ID;
  Space *cur_space = NULL, *dest_space = NULL;
  Link *link = NULL;
  Bool open = FALSE, allowed = FALSE;
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

  /* checks if the connection exists and then whether it's opened or can be used */
  link = game_get_link(game, cur_id, direction);
  if(!link) {
    game_set_last_message(game, "That's a wall...");
    return;
  }

  if((link_role = link_get_use_role(link)) == NO_ROLE) return;
  if((player_role = player_get_role(game_get_player(game))) == NO_ROLE) return;
  if(game_get_friendly(player_role, link_role, &allowed) == ERROR) return;
  if(allowed == FALSE){
    game_set_last_message(game, "I cant go trough this path...");
    return;
  }

  if(link_get_open(link, &open) == ERROR) return;
  if(open == FALSE){
    game_set_last_message(game, "The path is blocked...");
    return;
  }
  dest_id = link_get_dest(link);

  if(!(dest_space = game_get_space(game, dest_id))) return;
  if(game_set_spaces_discovered(game, dest_space) == ERROR) return;

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
  if(space_get_trap(dest_space, &trap_id) == ERROR) return;
  if(trap_id != NO_ID){
    trap = game_get_object(game, trap_id);

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
  Id obj_id = NO_ID, class_id= NO_ID;
  Id play_location = NO_ID;
  Object *obj = NULL;
  Player *player = NULL;
  Space *cur_space = NULL;
  Command *last_cmd = NULL;
  Bool movable = FALSE;
  Class *class = NULL;
  Tag tag = UNDEFINED;
  char *name = NULL, *closeup = NULL;
  int i;

  if (!game) return; 
  
  /*Gets the name of the object to take from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(name = command_get_desc(last_cmd))) return;

  /*Checks whether the inventory of the player is full or not*/
  if (!(player = game_get_player(game))) return;
  if (player_inventory_is_full(player) == TRUE) return;

  /* Checks if the object exists in the location of the player */
  play_location = game_get_player_location(game);
  obj_id = game_get_obj_id_from_name_at_space(game, name, play_location);
  if (obj_id == NO_ID) return;

  obj = game_get_object(game, obj_id);
  if(!obj) return;

  class_id = object_get_class_id(obj);
  class = game_get_class(game, class_id);
  if(!class) return;

  tag = class_get_tag(class);

  /*If you try to pick up a note or a switch, the game should advice you how to use it*/
  if(tag == NOTE){
    game_set_last_message(game, "That's a note. To read it i must type \"use\" followed by its name...");
    return;
  } else if(tag == SWITCH){
    game_set_last_message(game, "That's a switch. To press it i must type \"use\" followed by its name...");
    return;
  }
  
  /*Checks whether the object is movable or not*/
  if (class_get_movable(game_get_class_from_id_obj(game, obj_id), &movable) == ERROR) return;
  if (movable == FALSE) return;

  cur_space = game_get_space(game, play_location);
  if (!cur_space) return;
  
  if (player_add_object(player, obj_id) == ERROR) return;

  if (space_remove_object(cur_space, obj_id) == ERROR) return;

  for (i = 0; i < POV_HGHT; i++) {
    if (!(closeup = class_get_closeup_at_pos(game_get_class_from_id_obj(game, obj_id), i))) return;
    if (game_set_last_close_up(game, closeup, i) == ERROR) return;
  }

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
  Character *charr = NULL, *follower = NULL, *follower2 = NULL;
  Command *last_cmd = NULL;
  Player *player = NULL, *victim = NULL;
  Set *followers = NULL;
  Bool friendly = FALSE, deterministic = FALSE;
  Object *weapon = NULL, *armor = NULL;
  Class *weapon_class = NULL, *armor_class = NULL;
  Id charr_id = NO_ID, damaged_follower = NO_ID, player_loc = NO_ID, victim_loc = NO_ID, weapon_id = NO_ID, armor_id = NO_ID;
  char *name = NULL, message[MESG_SIZE], notifier[MESG_SIZE];
  int i, dice, charr_health, victim_health = -1, charr_dmg, follower_health, player_health, weapon_dmg = 0;
  int armor_def,damage = 0, damaged, num_followers = -1, num_followers2 = -1, total_luck = 0, count = 0, pos;

  if (!game) return;
  
  if (!(player = game_get_player(game))) return;
  if ((player_health = player_get_health(player)) == -1) return;
  if ((player_loc = player_get_location(player)) == NO_ID) return;
  if (!(current_space = game_get_space(game, player_loc))) return;


  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(name = command_get_desc(last_cmd))) return;

  /*Case of attacking a character*/
  if ((charr_id = game_get_charr_id_from_name_at_space(game, name, player_loc)) != NO_ID){

    charr = game_get_character_from_id(game, charr_id);
    if(!charr) return;

    if (character_get_health(charr) <= 0) return;

    /*Attack happens only if the character is not friendly and alive*/
    if (game_get_friendly(player_get_role(player), character_get_role(charr), &friendly) == ERROR) return;
    if (friendly == TRUE) {
      if (game_set_last_message(game, "It seems friendly... No need to fight") == ERROR) return;
      return;
    }

    /*  PLAYER ATTACKS  */

    player_get_weapon(player, &weapon_id);
    weapon = game_get_object(game, weapon_id);
    weapon_class = game_get_class(game, object_get_id(weapon));
    if(weapon_class && weapon){
      total_luck += class_get_luck(weapon_class);
      weapon_dmg = object_get_use_value(weapon);
    }

    player_get_armor(player, &armor_id);
    armor = game_get_object(game, armor_id);
    armor_class = game_get_class(game, object_get_class_id(armor));
    if(armor_class && armor){
      total_luck += class_get_luck(armor_class);
      armor_def = object_get_use_value(armor);
    }
    
    if(game_get_deterministic(game, &deterministic)==ERROR) return;
  
    if (deterministic == FALSE) dice = (rand() % ATK_RNG) + total_luck;
    else dice = ATK_WIN + 1;

    /*Depending on the number the player lands the attack or not*/
    if (dice >= ATK_WIN) {
      /*If the attack landed, the character gets damaged*/
      if((charr_health = character_get_health(charr)) == -1) return;
      
      damage = PLY_BASE_DMG + weapon_dmg;

      charr_health -= damage;

      if (character_set_health(charr, charr_health) == ERROR) return;

      if(character_get_health(charr) > 0) {
        if(weapon) count += sprintf(message, " @You hit %s with %s dealing %d dmg pts. @", character_get_name(charr), class_get_name(weapon_class), damage);
        else count += sprintf(message, " @You punched %s dealing %d dmg pts. @", character_get_name(charr), damage);
      }else {
        if(weapon) count += sprintf(message, " @You hit %s with %s killing him.@", character_get_name(charr), class_get_name(weapon_class));
        else count += sprintf(message, " @You punched %s so hard you actually killed him.@", character_get_name(charr));
        sprintf(message + count, "@ Enemie defeated! You gain 20 hp. ");
        if(player_set_health(player, player_health + 15) == ERROR) return;
        if(game_set_last_message(game, message)== ERROR) return;
        if (game_set_last_status(game, OK) == ERROR) return;
        return;
      }

    } else {
      /*If the player misses an attack with a weapon he might get hurt insthead of the character by accident*/
      dice = (rand()%ATK_ACC_RNG) - total_luck;

      if((dice >= ATK_ACCIDENT) && weapon) {
        if (player_set_health(player, player_health - PLY_BASE_DMG) == ERROR) return;
        if(player_get_health(player) > 0){
          count += sprintf(message + count, "You missed the attack and hurted yourself by accident. Ouch! @");
        } else {
          sprintf(message + count, "You missed the attack and accidentally killed yourself. Oops... @");
          if(game_set_last_message(game, message)== ERROR) return;
          if (game_set_last_status(game, OK) == ERROR) return;
          return;
        }
      } else {
        if(!(dice%5)) count += sprintf(message + count, " @You critically missed the attack. Check your aim! @");
        else if((dice%5) == 1) count += sprintf(message + count, " @You absurdly missed the attack. %s laughs at you loudly. @", character_get_name(charr));
        else count += sprintf(message + count, " @You missed the attack. @");
      }
    }


    /*   FOLLOWERS ATTACK    */

    if((num_followers = game_get_num_followers(game, player)) == -1) return;

    if(num_followers > 0){
      if (!(followers = game_get_followers(game, player))) return;

      for(i=0, damage = 0; i<num_followers;i++){

        if (deterministic == FALSE) dice = (rand() % ATK_RNG) + total_luck;
        else dice = ATK_WIN + 1;

        follower = game_get_character_from_id(game, set_get_id_at_pos(followers, i));

        if(dice >= ATK_WIN){
          if(!follower) continue;
          damage += character_get_damage(follower);
        }
      }

      set_destroy(followers);

      charr_health -= damage;

      if (character_set_health(charr, charr_health) == ERROR) return;

      if(character_get_health(charr) > 0) {
        if(num_followers > 1) count += sprintf(message + count, "Your followers attacked %s dealing %d dmg pts. @", character_get_name(charr), damage);
        else if(num_followers == 1) count += sprintf(message + count, "%s attacked %s dealing %d dmg pts. @", character_get_name(follower) ,character_get_name(charr), damage);
      }else {
        if(num_followers > 1) count += sprintf(message + count, "Your followers attacked %s and killed him @", character_get_name(charr));
        else if(num_followers == 1) count += sprintf(message + count, "%s attacked %s and killed him @", character_get_name(follower),character_get_name(charr));
        sprintf(message + count, "@ Enemie defeated! You gain 20 hp. ");
        if ((player_health = player_get_health(player)) == -1) return;
        if(player_set_health(player, player_health + 15) == ERROR) return;
        game_set_last_message(game, message);
        if (game_set_last_status(game, OK) == ERROR) return;
        return;
      }
    }

    /*   CHARACTER ATTACKS BACK   */

    if (deterministic == FALSE) dice = (rand() % ATK_RNG) - total_luck;
    else dice = ATK_WIN - 1;

    if(dice >= ATK_WIN){

      if ((charr_dmg = character_get_damage(charr) )== -1) return;

      if(character_get_weapon(charr, &weapon_id) == ERROR) return;
      weapon = game_get_object(game, weapon_id);
      if(weapon) charr_dmg += object_get_use_value(weapon);

      damaged = rand()%(num_followers + 1);

      if(damaged == num_followers) {

        player_get_armor(player, &armor_id);
        armor = game_get_object(game, armor_id);
        if(armor) armor_def = object_get_use_value(armor);
        else armor_def = 0;

        damage = (charr_dmg * (100-armor_def))/100;

        player_health -= damage;

        if (player_set_health(player, player_health) == ERROR) return;
  
        if(player_get_health(player) > 0) {
          count += sprintf(message + count, "%s attacked you! You lose %d hp. @", character_get_name(charr), damage);
        } else {
          sprintf(message + count, "%s attacked and killed you. @", character_get_name(charr));
          if(game_set_last_message(game, message)== ERROR) return;
          if (game_set_last_status(game, OK) == ERROR) return;
          return;
        }
  
      } else {
        /*Else, one of the followers is damaged*/
        character_get_armor(follower, &armor_id);
        armor = game_get_object(game, armor_id);
        if(armor) armor_def = object_get_use_value(armor);
        else armor_def = 0;

        damage = (charr_dmg * (100-armor_def))/100;
        
        if (!(followers = game_get_followers(game, game_get_player(game)))) return;
  
        if((damaged_follower = set_get_id_at_pos(followers, damaged)) == NO_ID) {
          set_destroy(followers);
          return;
        }
        set_destroy(followers);

        if (!(follower = game_get_character_from_id(game, damaged_follower))) return;
  
        if ((follower_health = character_get_health(follower)) == -1) return;

        if (character_set_health(follower, follower_health - damage) == ERROR) return;
  
        /*If the character dies, it must stop following the player and a message is shown*/
        if ((character_get_health(follower)) <= 0) {
          if (character_set_following(charr, NO_ID) == ERROR) return;
          if (space_remove_character(current_space, damaged_follower) == ERROR) return;
          sprintf(message + count, "%s was killed by %s. @", character_get_name(follower), character_get_name(charr));
          character_set_following(follower, NO_ID);
        } else {
          sprintf(message + count, "%s was attacked and lost %d hp. @", character_get_name(follower), damage);
          
        }   
      }
    } else {
      sprintf(message + count, "%s missed his attack. @", character_get_name(charr));
    }
  } else{
    /*Case of attacking a player*/
    victim = game_get_player_from_name(game, name);
    if(!victim) return;

    victim_loc = player_get_location(victim);

    if(player_loc != victim_loc){
      game_set_last_message(game, "That player is out of reach.");
      return;
    }

    /*  PLAYER ATTACKS  */
    if(game_get_deterministic(game, &deterministic)==ERROR) return;
  
    if (deterministic == FALSE) dice = (rand() % ATK_RNG) + total_luck;
    else dice = ATK_WIN + 1;

    /*Depending on the number the player lands the attack or not*/
    if (dice >= ATK_WIN) {
      /*If the attack landed, the victim gets damaged*/
      if((victim_health = player_get_health(victim)) == -1) return;
      
      damage = PLY_BASE_DMG + weapon_dmg;

      if (player_set_health(victim, victim_health - damage) == ERROR) return;

      if(player_get_health(victim) > 0) {
        if(weapon) count += sprintf(message, " @You hit %s with %s dealing %d dmg pts. @", player_get_name(victim), class_get_name(weapon_class), damage);
        else count += sprintf(message, " @You punched %s dealing %d dmg pts. @", player_get_name(victim), damage);
        if ((pos = game_get_player_pos_from_name(game, name)) < 0) return;
        sprintf(notifier, "%s attacked you! You lost %d hp.", player_get_name(player), damage);
        if (game_set_last_message_at_pos_with_info(game, pos, notifier, player_get_id(player), PLAYER) == ERROR) return;
      }else {
        if(weapon)count+= sprintf(message, " @You hit %s with %s killing him.@", player_get_name(victim), class_get_name(weapon_class));
        else count+= sprintf(message, " @You punched %s so hard you actually killed him.@", player_get_name(victim));
        sprintf(message + count, "@ Enemie defeated! You gain 20 hp. ");
        if(player_set_health(player, player_health + 15) == ERROR) return;
        if(game_set_last_message(game, message)== ERROR) return;
        if (game_set_last_status(game, OK) == ERROR) return;
        return;
      }

    } else {
      /*If the player misses an attack with a weapon he might get hurt insthead of the character by accident*/
      dice = (rand()%ATK_ACC_RNG) - total_luck;

      if((dice >= ATK_ACCIDENT) && weapon) {
        if (player_set_health(player, player_health - PLY_BASE_DMG) == ERROR) return;
        if(player_get_health(player) > 0){
          count += sprintf(message + count, "You missed the attack and hurted yourself by accident. Ouch! @");
        } else {
          sprintf(message + count, "You missed the attack and accidentally killed yourself. Oops... @");
          if(game_set_last_message(game, message)== ERROR) return;
          if (game_set_last_status(game, OK) == ERROR) return;
          return;
        }
      } else {
        if(!(dice%5)) count += sprintf(message + count, " @You critically missed the attack. Check your aim! @");
        else if((dice%5) == 1) count += sprintf(message + count, " @You absurdly missed the attack. %s laughs at you loudly. @", player_get_name(victim));
        else count += sprintf(message + count, " @You missed the attack. @");
      }
    }


    /*   FOLLOWERS ATTACK    */

    if((num_followers = game_get_num_followers(game, player)) == -1) return;

    if(num_followers > 0){
      if (!(followers = game_get_followers(game, player))) return;

      for(i=0, damage = 0; i<num_followers;i++){

        if (deterministic == FALSE) dice = (rand() % ATK_RNG) + total_luck;
        else dice = ATK_WIN + 1;

        follower = game_get_character_from_id(game, set_get_id_at_pos(followers, i));
        if(!follower) continue;

        if(dice >= ATK_WIN) damage += character_get_damage(follower);
      }

      set_destroy(followers);

      if((num_followers2 = game_get_num_followers(game, victim)) == -1) return;
      if(num_followers2 > 0){
        damaged = (rand()%num_followers2);

        if (!(followers = game_get_followers(game, victim))) return;

        follower2 = game_get_character_from_id(game, set_get_id_at_pos(followers, damaged));
        if(follower2){
          if((follower_health = character_get_health(follower2)) == -1) return;
          if (character_set_health(follower2, follower_health - damage) == ERROR) return;

          if(character_get_health(follower2) > 0){
            if(num_followers > 1) count += sprintf(message + count, "Your followers attacked %s dealing %d dmg pts. @", character_get_name(follower2), damage);
            else if(num_followers == 1) count += sprintf(message + count, "%s attacked %s dealing %d dmg pts. @", character_get_name(follower) ,character_get_name(follower2), damage);
          } else {
            if(num_followers > 1)count += sprintf(message + count, "Your followers beat the crap out of %s and killed him @", character_get_name(follower2));
            else if(num_followers == 1)count += sprintf(message + count, "%s attacked %s and killed him @", character_get_name(follower),character_get_name(follower2));
            character_set_following(follower2, NO_ID);
          }
        }
      } else {
        if((victim_health = player_get_health(victim)) == -1) return;
        if (player_set_health(victim, victim_health - damage) == ERROR) return;

        if(player_get_health(victim) > 0){
          if(num_followers > 1) count += sprintf(message + count, "Your followers attacked %s dealing %d dmg pts. @", player_get_name(victim), damage);
          else if(num_followers == 1) count += sprintf(message + count, "%s attacked %s dealing %d dmg pts. @", character_get_name(follower) ,player_get_name(victim), damage);
        } else {
          if(num_followers > 1)count+= sprintf(message + count, "Your followers beat the crap out of %s and killed him @", player_get_name(victim));
          else if(num_followers == 1)count+= sprintf(message + count, "%s attacked %s and killed him @", character_get_name(follower),player_get_name(victim));
        }
      }

    }

  }

  if (game_set_last_message(game, message) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_chat(Game *game) {
  Command *last_cmd = NULL;
  Space *current_space = NULL;
  Character *charr = NULL;
  Class *class1 = NULL, *class2 = NULL;
  Inventory *backpack1 = NULL, *backpack2 = NULL;
  Object *talkie1 = NULL, *talkie2 = NULL;
  Player *play_reciever = NULL, *play_sender = NULL;
  Role role1 = NO_ROLE, role2 = NO_ROLE;
  Bool friendly = FALSE, found = FALSE;
  Id player_loc = NO_ID, reciever_loc = NO_ID, sender_id = NO_ID, charr_id = NO_ID, obj1 = NO_ID, obj2 = NO_ID;
  char *name = NULL, *closeup = NULL, *desc = NULL, *mesg = NULL, message[MESG_SIZE];
  int i, j, pos, n_objs = -1, n_objs2 = -1, use_value = -1;

  if (!game) return;

  if (!(play_sender = game_get_player(game))) return;

  if ((player_loc = game_get_player_location(game)) == NO_ID) return;
  current_space = game_get_space(game, player_loc);
  if (!current_space) return;

  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(desc = command_get_desc(last_cmd))) return;
  if (!(name = strtok(desc, " "))) return;
  if (!(mesg = strtok(NULL, "\r\n"))) return;

  charr_id = game_get_charr_id_from_name(game, name);
  play_reciever = game_get_player_from_name(game, name);

  if ((charr_id == NO_ID) && !play_reciever) return;

  if (play_reciever) {
    if (player_get_health(play_reciever) <= 0) return;
    if ((pos = game_get_player_pos_from_name(game, name)) < 0) return;

    if ((reciever_loc = player_get_location(play_reciever)) == NO_ID) return;

    if (reciever_loc == player_loc) {
      sender_id = player_get_id(play_sender);
      if(sender_id == NO_ID) return;

      if (game_set_last_message_at_pos_with_info(game, pos, mesg, sender_id, PLAYER) == ERROR) return;
      sprintf(message, "You to %s: %s", player_get_name(game_get_player_at(game, pos)), mesg);
      if (game_set_last_message(game, message) == ERROR) return;

      for (i = 0; i < POV_HGHT; i++) {
        if (!(closeup = player_get_closeup_at(play_reciever, i))) return;
        if (game_set_last_close_up(game, closeup, i) == ERROR) return;
      }

      for (i = 0; i < POV_HGHT; i++) {
        if (!(closeup = player_get_closeup_at(play_sender, i))) return;
        if (game_set_last_close_up_at_pos(game, closeup, pos, i) == ERROR) return;
      }
      /* In case that you are not in the same space */
    } else {
      if (!(backpack1 = player_get_backpack(play_sender))) return;
      if ((n_objs = inventory_get_num_objects(backpack1)) == -1) return;

      for(i = 0; (i < n_objs) && (found == FALSE); i++) {
        obj1 = inventory_get_object_at_pos(backpack1, i);
        if (!(class1 = game_get_class_from_id_obj(game, obj1))) continue;
        if (class_get_tag(class1) != WALKIE_TALKIE) continue;

        if (!(talkie1 = game_get_object(game, obj1))) continue;
        if ((role1 = object_get_role(talkie1)) == NO_ROLE) continue;

        if (!(backpack2 = player_get_backpack(play_sender))) return;
        if ((n_objs2 = inventory_get_num_objects(backpack2)) == -1) return;

        for(j = 0; j < n_objs2; j++) {
          obj2 = inventory_get_object_at_pos(backpack2, i);
          if (!(class2 = game_get_class_from_id_obj(game, obj2))) continue;
          if (class_get_tag(class2) != WALKIE_TALKIE) continue;

          if (!(talkie2 = game_get_object(game, obj1))) continue;
          if ((role2 = object_get_role(talkie1)) == NO_ROLE) continue;

          if(role1 == role2) {
            found = TRUE;
            break;
          }
        }
      }

      if (found == FALSE) {
        game_set_last_message(game, "This player is out of reach...");
        return;
      }
      printf("encuentra");
      if ((use_value = object_get_use_value(talkie1)) <= 0) {
        if (game_set_last_message_at_pos_with_info(game, game_get_turn(game), "Damn, my WalkieTalkie broke down...", sender_id, THOUGHTS) == ERROR) return;
      
        for (i = 0; i < POV_HGHT; i++) {
          if (!(closeup = class_get_closeup_at_pos(class1, i))) return;
          if (game_set_last_close_up_at_pos(game, closeup, pos, i) == ERROR) return;
        }

        return;
      } 

      if (object_set_use_value(talkie1, use_value - 1) == ERROR) return;

      /* Sets the message to you */
      if (!(name = player_get_name(play_reciever))) return;
      sprintf(message, "You to %s: %s", name, mesg);
      if (game_set_last_message(game, message) == ERROR) return;

      for (i = 0; i < POV_HGHT; i++) {
        if (!(closeup = class_get_closeup_at_pos(class1, i))) return;
        if (game_set_last_close_up(game, closeup, i) == ERROR) return;
      }

      /* Sets the message to the player you are chatting with */
      if (!(name = player_get_name(play_sender))) return;
      sprintf(message, "(%s) %s", name, mesg);
      if (game_set_last_message_at_pos_with_info(game, pos, message, obj2, OBJECT) == ERROR) return;

      for (i = 0; i < POV_HGHT; i++) {
        if (!(closeup = class_get_closeup_at_pos(class2, i))) return;
        if (game_set_last_close_up_at_pos(game, closeup, pos, i) == ERROR) return;
      }
    }

  } else if ((charr_id != NO_ID) && !play_reciever) {
    charr = game_get_character_from_id(game, charr_id);
    if(!charr) return;

    if (character_get_health(charr) <= 0) return;
    if ((sender_id = character_get_id(charr)) == NO_ID) return;

    if(space_find_character(current_space, sender_id) == FALSE) {
      game_set_last_message(game, "This character is out of reach...");
      return;
    }

    if(game_get_friendly(player_get_role(play_sender), character_get_role(charr), &friendly) == ERROR) return;
    if (friendly == FALSE) {
      game_set_last_message(game, "I dont think its friendly...");
      return;
    }

    pos = game_get_turn(game);
    if (game_set_last_message_at_pos_with_info(game, pos, character_get_message(charr), sender_id, CHARACTER) == ERROR) return;

    for (i = 0; i < POV_HGHT; i++) {
      if (!(closeup = character_get_closeup_at_pos(charr, i))) return;
      if (game_set_last_close_up(game, closeup, i) == ERROR) return;
    }
  }
  else if (play_reciever && charr) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_inspect(Game *game){
  Command *last_cmd = NULL;
  char *name = NULL;
  Id obj_id = NO_ID, play_id = NO_ID;
  Object *obj = NULL;
  Class *class = NULL;
  char *desc = NULL, *closeup = NULL;
  int i, prime = -1, use_value = -1;

  if (!game) return; 
  
  /*Gets the name of the object to inspect from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(name = command_get_desc(last_cmd))) return;

  /*Get the object from the given name and checks if it is in the location of the player */
  obj_id = game_get_obj_id_from_name_at_space(game, name, player_get_location(game_get_player(game)));
  if (obj_id == NO_ID){
    /*If its not at the player's location, then check if the player has it on him*/
    obj_id = game_get_object_from_player(game, name);
    if(obj_id == NO_ID) return;
  }

  if (!(obj = game_get_object(game, obj_id))) return;  

  if (!(class = game_get_class_from_id_obj(game, obj_id))) return;
  if (!(desc = class_get_desc(class))) return;

  if(game_set_last_message_at_pos_with_info(game, game_get_turn(game), desc, obj_id, OBJECT) == ERROR) return;

  /* Multiplies by the prime associated if the obj is a note*/
  if (class_get_tag(class) == NOTE) {
    if ((use_value = object_get_use_value(obj)) == -1) return;
    if ((play_id = player_get_id(game_get_player(game))) == NO_ID) return;
    if ((prime = game_get_prime_from_id(game, play_id)) == -1) return;
    
    if ((use_value % prime) != 0) {
      if (object_set_use_value(obj, use_value * prime) == ERROR) return;
    }
  }

  for (i = 0; i < POV_HGHT; i++) {
    if (!(closeup = class_get_closeup_at_pos(game_get_class_from_id_obj(game, obj_id), i))) return;
    if (game_set_last_close_up(game, closeup, i) == ERROR) return;
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_recruit(Game *game) {
  Id charr_location = NO_ID, charr_id = NO_ID, player_id = NO_ID;
  Id play_location = NO_ID, following = NO_ID;
  Command *last_cmd = NULL;
  Bool friendly = FALSE;
  Character *charr = NULL;
  char *charr_name = NULL, message[MESG_SIZE];

  if (!game) return; 
  
  /*Gets the name of the character to recruit from the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(charr_name = command_get_desc(last_cmd))) return;
  if(charr_name[0] == '\0') return;

  if((player_id = player_get_id(game_get_player(game))) == NO_ID) return;
  
  /*Gets the character and checks whether its friendly*/
  if((charr_id = game_get_charr_id_from_name(game, charr_name)) == NO_ID) return;
  if(!(charr = game_get_character_from_id(game, charr_id)));
  if(game_get_friendly(player_get_role(game_get_player(game)), character_get_role(charr), &friendly) == ERROR) return;
  if(friendly == FALSE) return;
  if(character_get_following(charr, &following) == ERROR) return;
  if(following == player_id) {
    message[0] = '\0';
    sprintf(message, "%s is already following you.", charr_name);
    game_set_last_message(game, message);
    return;
  }
  if(following != NO_ID) return;

  /*Gets their location and checks if they are at the same space*/
  play_location = game_get_player_location(game);
  charr_location = game_get_character_location(game, character_get_id(charr));
  if (play_location == NO_ID || charr_location == NO_ID) return;
  if (play_location != charr_location) return;


  /*Sets the id of the player the character is going to follow*/
  if(character_set_following(charr, player_id) == ERROR) return;
  if(character_get_message(charr)){
    if(game_set_last_message_at_pos_with_info(game, game_get_turn(game), character_get_message(charr), character_get_id(charr), CHARACTER) == ERROR) return;
  }
    
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_abandon(Game *game) {
  Id player_id = NO_ID, charr_id = NO_ID;
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
  if((charr_id = game_get_charr_id_from_name(game, charr_name)) == NO_ID) return;
  if(!(charr = game_get_character_from_id(game, charr_id)));
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
  Bool friendly = FALSE, possesed = FALSE;
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

  toks = strtok(NULL," \r\n");
  if(toks){
    if(!strcmp(toks,"over")){
      toks = strtok(NULL," \r\n");
      if(!toks) return;
      target = toks;
    }
  }

  /*Get the object from the given name*/
  obj_id = game_get_object_from_player(game, name);
  if (obj_id == NO_ID){
    obj_id = game_get_obj_id_from_name_at_space(game, name, game_get_player_location(game));
    if(obj_id == NO_ID) return;
    else possesed = FALSE;
  } else possesed = TRUE;

  obj = game_get_object(game, obj_id);
  if(!obj) return;

  obj_tag = class_get_tag(game_get_class_from_id_obj(game, obj_id));

  /*Get the character if a name is given*/
  if(target){
    charr_id = game_get_charr_id_from_name(game, target);
    if(charr_id == NO_ID) return;

    charr = game_get_character_from_id(game, charr_id);
    if(!charr) return;

    /*If the character is unreachable or not friendly, nothing happens*/
    if(game_get_character_location(game,charr_id) != game_get_player_location(game)){
      game_set_last_message(game, "Im too far to do that...");
      return;
    }
    if(game_get_friendly(character_get_role(charr),player_get_role(game_get_player(game)),&friendly) == ERROR) return;
    if(friendly == FALSE){
      game_set_last_message(game, "I cant use this on an enemy...");
      return;
    }
  }

  switch(obj_tag){
    case NORMAL:
      if(possesed == FALSE) return;
      game_set_last_message(game, "That doesnt do anything...");
      break;
    case HEALER:
      if(possesed == FALSE) return;
      game_actions_use_healer(game, obj, charr);
      break;
    case WEAPON:
      if(possesed == FALSE) return;
      game_actions_equip_weapon(game, obj, charr);
      break;
    case ARMOR:
      if(possesed == FALSE) return;
      game_actions_equip_armor(game, obj, charr);
      break;
    case TRAP:
      if(possesed == FALSE) return;
      game_actions_set_trap(game, obj);
      break;
    case NOTE:
      game_actions_read_note(game, obj);
      break;
    case SWITCH:
      game_actions_use_switch(game, obj);
      break;
    default:
      break;
  }
}

void game_actions_use_healer(Game *game, Object *obj, Character *trg){
  int current_health = 0, new_health = 0;
  Player *player = NULL;

  if(!game || !obj) return;

  player = game_get_player(game);
  if(!player) return;

  if(trg){
    current_health = character_get_health(trg);

    if(current_health <= 0) return;

    new_health = current_health + object_get_use_value(obj);
    if(new_health <= 0) character_set_health(trg, 0);
    else character_set_health(trg, new_health);
  } else {
    current_health = player_get_health(player);

    if(current_health <= 0) return;

    new_health = current_health + object_get_use_value(obj);
    if(new_health <= 0) player_set_health(player, 0);
    else player_set_health(player, new_health);
  }

  if(player_delete_object(player, object_get_id(obj)) == ERROR) return;
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_equip_armor(Game *game, Object *obj, Character *trg){
  Id obj_id = NO_ID, armor = NO_ID;
  Player *player = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  if(!player || obj_id == NO_ID) return;

  if(trg){
    if(player_delete_object(player,obj_id) == ERROR) return;

    if(character_get_armor(trg,&armor) == ERROR) return;
    if(armor != NO_ID) player_add_object(player, armor);
    if(character_set_armor(trg,obj_id)==ERROR) return;
    
  } else {
    if(player_delete_object(player,obj_id) == ERROR) return;

    if(player_get_armor(player, &armor) == ERROR) return;
    if(armor != NO_ID) player_add_object(player,armor);
    if(player_set_armor(player,obj_id)==ERROR) return;
    
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_equip_weapon(Game *game, Object *obj, Character *trg){
  Id obj_id = NO_ID, weapon = NO_ID;
  Player *player = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  if(!player || obj_id == NO_ID) return;

  if(trg){
    if(player_delete_object(player,obj_id) == ERROR) return;

    if(character_get_weapon(trg,&weapon) == ERROR) return;
    if(weapon != NO_ID) player_add_object(player,weapon);
    if(character_set_weapon(trg,obj_id) == ERROR) return;
    
  } else {
    if(player_delete_object(player,obj_id) == ERROR) return;

    if(player_get_weapon(player,&weapon) == ERROR) return;
    if(weapon != NO_ID) player_add_object(player,weapon);
    if(player_set_weapon(player,obj_id) == ERROR) return;
    
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_set_trap(Game *game, Object *obj){
  Id obj_id = NO_ID, trap_id = NO_ID;
  Player *player = NULL;
  Space *curr_sp = NULL;

  if(!game || !obj) return;

  obj_id = object_get_id(obj);
  player = game_get_player(game);
  curr_sp = game_get_space(game, game_get_player_location(game));
  if(!player || obj_id == NO_ID || !curr_sp) return;

  /*If there is already a trap, we cant set another one*/
  if(space_get_trap(curr_sp, &trap_id) == ERROR) return;
  if(trap_id != NO_ID) return;
  if(space_set_trap(curr_sp,obj_id) == ERROR) return;

  /*Sets the trap as one from the player's team*/
  if(object_set_role(obj, player_get_role(player)) == ERROR) return;

  if(player_delete_object(player,obj_id) == ERROR) return;
  
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_read_note(Game *game, Object *obj){
  char *desc = NULL, *closeup = NULL;
  Class *class = NULL;
  int i;

  if (!(class = game_get_class(game, object_get_class_id(obj)))) return;

  desc = class_get_desc(class);
  if(!desc) return;

  for (i = 0; i < POV_HGHT; i++) {
    if (!(closeup = class_get_closeup_at_pos(class, i))) return;
    if (game_set_last_close_up(game, closeup, i) == ERROR) return;
  }

  game_set_last_message(game, desc);

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_use_switch(Game *game, Object *obj){
  int state;

  if (!game || !obj) return;

  state = object_get_use_value(obj);
  if(state == -1) return;

  /*Alternates the state between 0 and 1*/
  state = (state + 1) % 2;
  if (object_set_use_value(obj, state) == ERROR) return;

  if(game_set_last_message_at_pos_with_info(game, game_get_turn(game),"*pip!*",object_get_id(obj),OBJECT) == ERROR) return;

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
  if ((len = strlen(cmd_desc)) <= 0) return;

  printf("Entra a ga_save: %d\n", len);
  if (len >= 4 && strcmp(cmd_desc + len - 4, ".dat") != 0) {
    sprintf(file_save /*+ strlen(file_save)*/, "%s.dat", cmd_desc);
  }
  else {
    sprintf(file_save, "%s", cmd_desc);
  }

  if (game_save(game, file_save) == ERROR) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_load(Game **game) {
  Command *last_cmd = NULL;
  char *cmd_desc = NULL;
  char file_load[WORD_SIZE];
  int len = 0;

  if (!game) return; 
  
  /*Gets the description of the last cmd to load the file*/
  if (!(last_cmd = game_get_last_command(*game))) return;
  if (!(cmd_desc = command_get_desc(last_cmd))) return;
  len = strlen(cmd_desc);

  if (strcmp(cmd_desc + len - 4, ".dat") != 0) {
    sprintf(file_load, "%s.dat", cmd_desc);
  }
  else {
    sprintf(file_load, "%s", cmd_desc);
  }

  if(game_load(game, file_load) == ERROR) return;
  
  if (game_set_last_status(*game, OK) == ERROR) return;
}

void game_actions_open_link(Game *game){
  Command *last_cmd = NULL;
  char *cmd_desc = NULL, *toks = NULL;
  char *key = NULL;
  extern char *dir_to_str[N_DIR][N_DIRT];
  Direction typed_dir = UNK_DIR, reverse_dir = UNK_DIR;
  Link *link = NULL, *reverse_link = NULL;
  Id obj_id = NO_ID, cur_id = NO_ID, obj_open = NO_ID, destin = NO_ID;
  Object *obj = NULL;
  Role play_role = NO_ROLE, link_role = NO_ROLE;
  Bool open = TRUE, locked = TRUE, ally = FALSE, connected = FALSE;
  int i = 0;

  if (!game) return; 
  
  /*Gets the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  toks = strtok(cmd_desc," \r\n");
  if(!toks) return;

  /* compares the command description to any known directions */
  while(typed_dir == UNK_DIR && i < N_DIR) {
    if(!strcasecmp(toks, dir_to_str[i][DIRS]) || !strcasecmp(toks, dir_to_str[i][DIRL])) {
      typed_dir = i + UNK_DIR;
    }else {
      i++;
    }
  }
  /* if no valid direction is found, the function ends */
  if(typed_dir == UNK_DIR) return;

  /*Gets the current space of the player and the link wanted to open*/
  cur_id = game_get_player_location(game);

  link = game_get_link(game, cur_id, typed_dir);
  if(!link) return;

  destin = link_get_dest(link);
  if(destin == NO_ID) return;

  if(((int)typed_dir)%2) reverse_dir = typed_dir - 1;
  else reverse_dir = typed_dir + 1;

  reverse_link = game_get_link(game, destin, reverse_dir);

  /* Checks if the link is connected or already opened */
  if(link_get_connected(link, &connected) == ERROR) return;
  if(connected == TRUE){
    game_set_last_message(game, "There is no door to open");
    return;
  }

  if(link_get_open(link, &open) == ERROR) return;
  if(open == TRUE) {
    game_set_last_message(game, "The door is already open");
    return;
  }
  /*If the player is not allowed to open this link, the function ends*/
  play_role = player_get_role(game_get_player(game));
  link_role = link_get_open_role(link);

  if(game_get_friendly(play_role, link_role, &ally) == ERROR) return;
  if(ally == FALSE){
    game_set_last_message(game, "I cant open this type of lock...");
    return;
  }

  toks = strtok(NULL," \r\n");
  if(toks){
    if(!strcmp(toks,"with")){
      toks = strtok(NULL," \r\n");
      if(!toks) return;
      key = toks;
    }
  }

  if(link_get_locked(link, &locked) == ERROR) return;
  if (locked == TRUE){
    /*Get the object from the given name*/
    if(!key){
      game_set_last_message(game, "This door is locked. I need a key.");
      return;
    }

    obj_id = game_get_object_from_player(game, key);
    obj = game_get_object(game, obj_id);
    if(!obj) return;

    if(class_get_open(game_get_class_from_id_obj(game, obj_id), &obj_open) == ERROR) return;

    if(obj_open == NO_ID) return;
    if(obj_open == link_get_id(link)){
      if(link_set_locked(link, FALSE) == ERROR) return;
      if(link_set_open(link, TRUE) == ERROR) return;
      if(link_set_locked(reverse_link, FALSE) == ERROR) return;
      if(link_set_open(reverse_link, TRUE) == ERROR) return;

      object_set_use_value(obj, 1);
    } else {
      game_set_last_message(game, "I cant open the door with that...");
      return;
    }
  } else {
    if(link_set_open(link, TRUE) == ERROR) return;
    if(link_set_open(reverse_link, TRUE) == ERROR) return;
  }
  
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_close_link(Game *game){
  Command *last_cmd = NULL;
  char *cmd_desc = NULL;
  Direction typed_dir = UNK_DIR, reverse_dir = UNK_DIR;
  Link *link = NULL, *reverse_link = NULL;
  Role play_role = NO_ROLE, link_role = NO_ROLE;
  Bool open = TRUE, ally = FALSE, connected = FALSE;
  extern char *dir_to_str[N_DIR][N_DIRT];
  Id cur_id = NO_ID, destin = NO_ID;
  int i = 0;

  if (!game) return; 
  
  /*Gets the description of the last cmd*/
  if (!(last_cmd = game_get_last_command(game))) return;

  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  /* compares the command description to any known directions */
  while(typed_dir == UNK_DIR && i < N_DIR) {
    if(!strcasecmp(cmd_desc, dir_to_str[i][DIRS]) || !strcasecmp(cmd_desc, dir_to_str[i][DIRL])) {
      typed_dir = i + UNK_DIR;
    }else {
      i++;
    }
  }
  /* if no valid direction is found, the function ends */
  if(typed_dir == UNK_DIR) return;

  /*Gets the current space of the player and the link wanted to close*/
  cur_id = game_get_player_location(game);

  link = game_get_link(game, cur_id, typed_dir);
  if(!link) return;

  
  destin = link_get_dest(link);
  if(destin == NO_ID) return;

  if(((int)typed_dir)%2) reverse_dir = typed_dir - 1;
  else reverse_dir = typed_dir + 1;

  reverse_link = game_get_link(game, destin, reverse_dir);


  /* Checks if the link is connected or already closed */
  if(link_get_connected(link, &connected) == ERROR) return;
  if(connected == TRUE){
    game_set_last_message(game, "There is no door to close");
    return;
  }

  if(link_get_open(link, &open) == ERROR) return;
  if(open == FALSE) {
    game_set_last_message(game, "The door is already closed");
    return;
  }

  /*If the player is not allowed to close this link, the function ends*/
  play_role = player_get_role(game_get_player(game));
  link_role = link_get_open_role(link);
  if(game_get_friendly(play_role, link_role, &ally) == ERROR) return;
  if(ally == FALSE){
    game_set_last_message(game, "I cant close this type of lock...");
    return;
  }

  if(link_set_open(link, FALSE) == ERROR) return;
  if(link_set_open(reverse_link, FALSE) == ERROR) return;
  
  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_accept(Game *game) {
  if(!game) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_deny(Game *game) {
  if(!game) return;

  if(game_get_round(game) != 0) return;

  if(player_set_role(game_get_player(game), UNDEFINED) == ERROR) return;

  if (game_set_last_status(game, ERROR) == ERROR) return;
}

void game_actions_cooperate(Game *game) {
  Command *last_cmd = NULL;
  char *cmd_desc = NULL;
  Player *play = NULL, *play_dest = NULL;
  Id loc = NO_ID;
  int turn;

  if(!game) return;
  
  if((turn = game_get_turn(game)) == -1) return;
  if(game_get_round(game) != 0) return;

  if (!(last_cmd = game_get_last_command(game))) return;
  if (!(cmd_desc = command_get_desc(last_cmd))) return;

  if(!(play = game_get_player(game))) return;
  if(player_get_role(play) != UNDEFINED) return;
  
  if (!(play_dest = game_get_player_from_name(game, cmd_desc))) return;
  if (player_get_role(play_dest) != UNDEFINED) return;
  
  if(((loc = player_get_location(play)) != player_get_location(play_dest) || loc == NO_ID) ) return;

  /* Assigns a team to the first pair and another to the other pair*/
  if(turn == 0) {
    if(player_set_role(play, TEAM1) == ERROR) return;
  } else {
    if(player_set_role(play, TEAM2) == ERROR) return;
  }

  if (game_set_last_status(game, OK) == ERROR) return;
}

void game_actions_betray(Game *game) {
  if(!game) return;

  if (game_set_last_status(game, ERROR) == ERROR) return;
}

void game_actions_view(Game *game) {
if(!game) return;

  if (game_set_last_status(game, OK) == ERROR) return;
}
