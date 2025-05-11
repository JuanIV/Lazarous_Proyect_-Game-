/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "game_management.h"

/**
 * @brief Minimum number of characters of an objects name you need to write to try 
 * to find that object
 * 
 */
#define MIN_ESPECIF 2

typedef struct {
  char msg[MESG_SIZE + 1];   /*!< A message to be shown on screen*/
  Bool visible;              /*!< Number of turns the message should be shown for*/
  Id sender;                 /*!< The id of the sender*/
  Type sender_type;          /*!< A char that represents if the msg was sent by a player ('p'), character ('c'), object ('o') or game ('g')*/
} Message;

/**
 * @brief Struct that stores the information of the interface data of each player: last message and last 3 commands
 * @author Tiago Oselka
 * 
 */
typedef struct {
  Message *messages[NUM_MSGS];             			/*!< Messages to be shown on screen*/
  char last_closeup[POV_HGHT][POV_WDTH + 1];    /*!< Last close up to be shown*/
  Command *last_cmds[NUM_CMDS];				        	/*!< Last command used*/
} InterfaceData;

/**
 * @brief Struct that stores the information of a game: players, turn, spaces, links, objects, characters and information related to their commands  
 * @author Tiago Oselka
 * 
 */
struct _Game {
  Player *players[MAX_PLAY];	/*!< Players of the game*/
  int n_players;              /*!< Number of players in the game*/
  int turn;                   /*!< Turn of the player that is playing*/
  int round;                  /*!< Round the game is currently in*/
  Space *spaces[MAX_SPACES];	/*!< Array of spaces that form the map*/
  int n_spaces;								/*!< Number of spaces in the game*/
  Link *links[MAX_LINKS];     /*!< Array of links that connect the spaces*/
  int n_links;                /*!< Number of links in the game*/
  Class *class[MAX_CLASS];    /*!< Array of classes of objects in the game*/
  int n_classes;              /*!< Number of classes in the game*/
  Object *object[MAX_OBJ];		/*!< Array of objects in the game*/
  int n_objects;							/*!< Number of objects in the game*/
  Character *characters[MAX_CHARR];	/*!< Array of characters in the game*/
  int n_characters;						/*!< Number of characters in the game*/
  Bool deterministic;						/*!< If the game is deterministic or not*/  
  InterfaceData *data[MAX_PLAY];    /*!< Array of the data of each player*/
  Bool finished;							/*!< Status of the game. TRUE if it has finished. FALSE if not*/
  char minimap[NUM_FLOORS][MAP_HEIGHT][MAP_WIDTH + 1]; /*!< Graphic description of the mini map*/
  char win_screens[TOT_PLAYERS][MAP_HEIGHT][MAP_WIDTH + 1]; /*!< Graphic description of the win screens, one for each player*/
  char loss_screen[MAP_HEIGHT][MAP_WIDTH + 1]; /*!< Graphic description of the screen printed when someone looses */
  char interturn_screen[MAP_HEIGHT]; /*!< Graphic description of the screen printed between each turn*/
};

/************************ Private functions **************************** */

/**
 * @brief Private function used in game_create_from_file to get the id of a
 * space in a certain position of the list
 * @author Profesores PPROG
 *
 * @param game pointer to the game
 * @param position position in the space array
 * @return the id from the space in the given position
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It creates a Message, initializing the spaces and its other members
 * @author Tiago Oselka
 * 
 * @return a new Message pointer
 */
Message *game_message_create();

/**
 * @brief it destroys a Message
 * 
 * @param interfaceData a pointer to the Message
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_message_destroy(Message *message);

/**
 * @brief Prints the content of a message
 * @author Tiago Oselka
 * 
 * @param message Pointer to the Message
 * @return Ok if everything went well, ERROR if there was any mistake 
 */
Status game_message_print(Message *message);

/**
 * @brief It creates a new interface data, initializing the spaces and its other members
 * @author Tiago Oselka
 * 
 * @return a new interfaceData pointer
 */
InterfaceData *game_interface_data_create();

/**
 * @brief it destroys a interfaceData freeing every allocated data
 * 
 * @param interfaceData a pointer to the interfaceData
 * @return Ok if everything went well, ERROR if there was any mistake
 */
Status game_interface_data_destroy(InterfaceData *interfaceData);

/**
 * @brief It prints the information inside interface data
 * 
 * @param interfaceData a pointer to the interface data
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_interface_data_print(InterfaceData *interfaceData);

/**
 * @brief Recursive part of game_set_spaces_discovered. Sets all connected spaces as discovered
 * @author Tiago Oselka
 * 
 * @param game Pointer to the game
 * @param space Pointer to a space
 */
void game_set_spaces_discovered_rec(Game *game, Space *space);
/**************** Implementation of private functions ****************** */

Id game_get_space_id_at(Game *game, int position) {
  if (!game || position < 0) return NO_ID;

  if (position >= game_get_n_spaces(game)) return NO_ID;

  return space_get_id(game->spaces[position]);
}

Message *game_message_create() {
  Message *message = NULL;

  if(!(message = (Message*) calloc(1, sizeof(Message)))) return NULL;

  message->msg[0] = '\0';
  message->visible = FALSE;
  message->sender = NO_ID;
  message->sender_type = NO_TYPE;

  return message;
}

Status game_message_destroy(Message *message) {
  if (!message) return ERROR;

  free(message);

  return OK;
}

Status game_message_print(Message *message) {
  if (!message) return ERROR;

  fprintf(stdout, "--> Message: %s\n", message->msg);
  if(message->visible == TRUE) {
    fprintf(stdout, "--> Message will be shown\n");
  }else {
    fprintf(stdout, "--> Message will not be shown\n");
  }
  fprintf(stdout, "--> Message sender Id: %ld\n", message->sender);
  fprintf(stdout, "--> Message sender type: %d\n", message->sender_type);

  return OK;
}

InterfaceData *game_interface_data_create() {
  InterfaceData *interfaceData = NULL;
  int i;

  if(!(interfaceData = (InterfaceData*) calloc(1, sizeof(InterfaceData)))) return NULL;

  for(i = 0; i < NUM_MSGS; i++) {
    if(!(interfaceData->messages[i] = game_message_create())) {
      game_interface_data_destroy(interfaceData);
      return NULL;
    }
  }

  for(i=0;i<POV_HGHT;i++){
    interfaceData->last_closeup[i][0] = '\0';
  }

  for(i = 0; i < NUM_CMDS; i++) {
    if (!(interfaceData->last_cmds[i] = command_create())) {
      game_interface_data_destroy(interfaceData);
      return NULL;
    }
  }
  
  return interfaceData;
}

Status game_interface_data_destroy(InterfaceData *interfaceData) {
  int i;

  if(!interfaceData) return ERROR;
  
  for(i = 0; i < NUM_MSGS; i++) {
    game_message_destroy(interfaceData->messages[i]);
    interfaceData->messages[i] = NULL;
  }

  for(i = 0; i < NUM_CMDS; i++) {
    if(interfaceData->last_cmds[i]) {
      command_destroy(interfaceData->last_cmds[i]);
      interfaceData->last_cmds[i] = NULL;
    }
  }

  free(interfaceData);  

  return OK;
}

Status game_interface_data_print(InterfaceData *interfaceData) {
  int i;
  if(!interfaceData) {
    fprintf(stdout, "--> InterfaceData is empty");
  }

  for(i = 0; i < NUM_MSGS; i++) {
    fprintf(stdout, "=> Message %d\n", i+1);
    if(interfaceData->messages[i]) game_message_print(interfaceData->messages[i]);
  }

  for(i = 0; i<NUM_CMDS; i++) {
    fprintf(stdout, "=> Command %d\n", i+1);
    if(interfaceData->last_cmds[i]) command_print(interfaceData->last_cmds[i]);
  }

  fprintf(stdout, "=> Close up\n");
  for(i = 0; i<POV_HGHT; i++) {
    fprintf(stdout, "%s\n", interfaceData->last_closeup[i]);
  }
  

  return OK;
}

Status game_interface_data_print_at_pos(Game *game, int pos) {
  if(!game) return ERROR;
  if(pos < 0 || pos >= game->n_players) return ERROR;

  return game_interface_data_print(game->data[pos]);
}
/********************************************************************* */

/**
 * ***************  Data management  ***************
 */

/*It creates a new game, initializing the spaces and its other members*/
Game *game_create() {
  Game *game = NULL;
  int i = 0, j = 0;

  if ((game = (Game *)calloc(1, sizeof(Game))) == NULL) return NULL;

  /*Initialize spaces*/
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  game->n_spaces = 0;

  /*Initialize objects*/
  for (i = 0; i < MAX_OBJ; i++) {
    game->object[i] = NULL;
  }
  game->n_objects = 0;

  /*Initialize characters*/
  for (i = 0; i < MAX_CHARR; i++) {
    game->characters[i] = NULL;
  }
  game->n_characters = 0;

  /*Initialize players*/
  for (i = 0; i < MAX_PLAY; i++) {
    game->players[i] = NULL;

    game->data[i] = NULL;
  }
  game->n_players = 0;

  game->turn = 0;

  game->round = 0;

  game->deterministic = FALSE;

  game->finished = FALSE;

  for (i = 0; i < NUM_FLOORS; i++) {
    for (j = 0; j < MAP_HEIGHT; j++) {
      game->minimap[i][j][0] = '\0'; 
    }
  }

  return game;
}

/*It reads a games data from a file*/
Status game_create_from_file(Game *game, char *filename) {
  if (!game || !filename) {
    printf("Here\n");
    return ERROR;
  }
  printf("Enters\n");
  /*we first load the spaces and then the rest in order to directly add 
  the objects, players and characters to each space*/
  if (game_management_load_spaces(game, filename) == ERROR) return ERROR;
  printf("Spaces loaded...\n");
  if (game_management_load_links(game, filename) == ERROR) return ERROR;
  printf("Links loaded...\n");
  if (game_management_load_classes(game, filename) == ERROR) return ERROR;
  printf("Classes loaded...\n");
  if (game_management_load_objects(game, filename) == ERROR) return ERROR;
  printf("Objects loaded...\n");
  if (game_management_load_characters(game, filename) == ERROR) return ERROR;
  printf("Characters loaded...\n");
  if (game_management_load_players(game, filename) == ERROR) return ERROR;
  printf("Players loaded...\n");
  if (game_management_load_interface_data(game, filename) == ERROR) return ERROR;
  printf("InterfaceData loaded...\n");
  if (game_management_load_turn(game, filename) == ERROR) return ERROR;
  printf("Turn loaded...\n");
  if (game_management_load_minimap(game, filename) == ERROR) return ERROR;
  printf("Minimap loaded...\n");

  return OK;
}

/*It destroys a game freeing every allocated data (destroys space data and the last command)*/
Status game_destroy(Game *game) {
  int i = 0;
  if(!game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_classes; i++) {
    class_destroy(game->class[i]);
  }

  for (i = 0; i < game->n_objects; i++) {
    object_destroy(game->object[i]);
  }

  for (i = 0; i < game->n_characters; i++) {
    character_destroy(game->characters[i]);
  }

  for(i = 0; i < game->n_links; i++) {
    link_destroy(game->links[i]);
  }

  for (i = 0; i < game->n_players; i++) {
    player_destroy(game->players[i]);
    if(game->data[i]) game_interface_data_destroy(game->data[i]);
  }

  free(game);

  return OK;
}

/**
 * ***************  Player management  ***************
 */

/*Gets a pointer to the player who has the turn*/
Player *game_get_player(Game *game) {
  Player *player = NULL;

  if (!game) return NULL;

  if(game->turn < 0 || game->turn >= game->n_players) return NULL;

  if (!(player = game->players[game->turn])) return NULL;

  return player;
}

/*Gets a specific player of the game */
Player *game_get_player_at(Game *game, int pos) {
  if(!game) return NULL;

  if(pos<0||pos>=game->n_players) return NULL;

  return game->players[pos];
}

Player *game_get_player_from_name(Game *game, char *name) {
  int i, name_length;
  char *aux_name = NULL;

  if (!game || !name) return NULL;

  name_length = strlen(name);

  if(name_length > WORD_SIZE || name_length < MIN_ESPECIF) return NULL;

  for (i = 0; i < game->n_players; i++) {
    if (!(aux_name = player_get_name(game->players[i]))) continue;

    if ((strncasecmp(name+1, aux_name+1, name_length-1) == 0) && (toupper(name[0]) == toupper(aux_name[0]))) {
      return game->players[i];
    }
  }

  return NULL;
}

Player *game_get_player_from_id(Game *game, Id id) {
  int i;
  Id id_aux = NO_ID;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_players; i++) {
    if (!(id_aux = player_get_id(game->players[i]))) return NULL;

    if (id_aux == id) {
      return game->players[i];
    }
  }

  return NULL;
}

int game_get_player_pos_from_name(Game *game, char *name) {
  int i, name_length;
  char *aux_name = NULL;

  if (!game || !name) return -1;

  name_length = strlen(name);

  if(name_length > WORD_SIZE || name_length < MIN_ESPECIF) return -1;

  for (i = 0; i < game->n_players; i++) {
    if (!(aux_name = player_get_name(game->players[i]))) continue;

    if ((strncasecmp(name+1, aux_name+1, name_length-1) == 0) && (toupper(name[0]) == toupper(aux_name[0]))) {
      return i;
    }
  }

  return -1;
}

/*Gets the number of players in the game*/
int game_get_n_players(Game *game){
  if(!game) return 0;

  return game->n_players;
}

/*It gets the player position from the game struct*/
Id game_get_player_location(Game *game) {
  if (!game) return NO_ID;

  if(game->turn < 0 || game->turn >= game->n_players) return NO_ID;

  if (!game->players[game->turn]) return NO_ID;

  return player_get_location(game->players[game->turn]);
}

/*Sets the player position to a given id*/
Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID || !game) return ERROR;

  if(game->turn < 0 || game->turn >= game->n_players) return ERROR;

  if (!game->players[game->turn]) return ERROR;

  if (player_set_location(game->players[game->turn], id) == ERROR) return ERROR;

  return OK;
}

/*Add a new player to the game*/
Status game_add_player (Game *game, Player *play) {
  Status st = OK;
  if(game == NULL || play == NULL || game->n_players>=8) return ERROR;

  game->players[game->n_players] = play;

  game->data[game->n_players] = game_interface_data_create();
  if(!game->data[game->n_players]) st = ERROR;

  game->n_players++;
  return st;
}

/*Gets the number of characters that follow a player*/
int game_get_num_followers(Game *game, Player *player) {
  int i, count = 0;
  Id player_id = NO_ID, following = NO_ID;

  if(!game || !player) return -1;

  if((player_id = player_get_id(player)) == NO_ID) return -1;

  for(i = 0; i < game->n_characters; i++) {
    if(!game->characters[i]) return -1;
    if(character_get_following(game->characters[i], &following) == ERROR) return -1;
    if(player_id == following) {
      count++;
    }
  }

  return count;
}

/*Gets a set with the Ids of the followers that a player has*/
Set *game_get_followers(Game *game, Player *player) {
  int i;
  Id player_id = NO_ID, charr_id = NO_ID, following = NO_ID;
  Status st = OK;
  Set *followers = NULL;

  if(!game || !player) return NULL;

  if((player_id = player_get_id(player)) == NO_ID) return NULL;

  followers = set_create();
  if(!followers) return NULL;

  for(i = 0; i < game->n_characters && st == OK; i++) {
    if(!game->characters[i]) st = ERROR;
    if (character_get_following(game->characters[i], &following) == ERROR) st = ERROR;

    if((player_id == following) && (character_get_health(game->characters[i]) > 0) && (st == OK)) {
      if((charr_id = character_get_id(game->characters[i])) == NO_ID) st = ERROR;
      if(set_add(followers, charr_id) == ERROR) st = ERROR;
    }

    if(st == ERROR) {
      set_destroy(followers);
      followers = NULL;
      break;
    }
  }

  return followers;
}

/*Gets an object with a certain name from the players backpack*/
Id game_get_object_from_player(Game *game, char *name){
  Player *player = NULL;
  Inventory *inv = NULL;
  Id obj_id = NO_ID;
  Object *obj = NULL;
  Class *class = NULL;
  char *class_name = NULL;
  int i = 0, name_length = 0;

  if(!game || !name ) return NO_ID;
  player = game_get_player(game);

  inv = player_get_backpack(player);
  if(!inv) return NO_ID;

  name_length = strlen(name);

  if (name_length > WORD_SIZE || name_length < MIN_ESPECIF)
  return NO_ID;

  for(i=0;i<inventory_get_num_objects(inv);i++){
    obj_id = inventory_get_object_at_pos(inv, i);
    obj = game_get_object(game, obj_id);
    if(!obj) continue;
    
    if (!(class = game_get_class_from_id_obj(game, obj_id))) return NO_ID;
    class_name = class_get_name(class);

    /*Strstr allows us to get an object from  a fraction of its name, but we set
     * the minimum as 2 characters */
    if ((strncasecmp(class_name+1,name+1, name_length-1) == 0) && (toupper(class_name[0]) == toupper(name[0]))) return obj_id;
  }

  return NO_ID;
}

/**
 * ***************  Turn and round management  ***************
 */

/*Gets the the turn of the game*/
int game_get_turn(Game *game) {
  if (!game) return -1;

  if(game->turn < 0 || game->turn >= game->n_players) return -1;

  return (game->turn);
}

int game_get_prime_from_id(Game *game, Id id) {
  int primes[TOT_PLAYERS] = {2, 3, 5, 7}, i = 0;

  if (!game || id == NO_ID) return -1;

  for(i = 0; i < game->n_players; i++) {
    if (id == player_get_id(game->players[i])) break;
  }

  if (i == game->n_players || i < 0) return -1;

  return primes[i];
}

int game_get_round(Game *game) {
  if (!game) return -1;

  if(game->round < 0) return -1;

  return (game->round);
}

Status game_set_round(Game *game, int round) {
  if(!game) return ERROR;

  if(round < 0) return ERROR;

  game->round = round;

  return OK;
}

Status game_set_turn(Game *game, int turn) {
  if(!game) return ERROR;

  if(turn < 0 || turn >= game->n_players) return ERROR;

  game->turn = turn;

  return OK;
}

/*Sets the next turn*/
Status game_next_turn(Game *game) {
  Status st = ERROR;
  int dead_players = 0;

  if (!game) return ERROR;

  while((st == ERROR) && (dead_players < game->n_players)) {
    game->turn = (game->turn + 1) % game->n_players;
    
    if(player_get_health(game->players[game->turn]) <= 0) {
      dead_players ++;
    } else st = OK;
  }

  game_erase_all_messages(game);

  if(game->turn == 0) game->round++;

  /*If all players are dead, we finish the game*/
  if(st == ERROR) game->finished = TRUE;

  return OK;
}

Status game_update_round(Game *game) {
  if(!game) return ERROR;

  if (game->turn == 0) game->round++;

  return OK;
}
/**
 * ***************  Spaces management  ***************
 */

/*Given an id, returns a pointer to the space that matches that id*/
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) return game->spaces[i];
  }

  return NULL;
}

/*It gets a space in a position of the array of spaces*/
Space *game_get_space_at_pos(Game *game, int pos) {
  if(!game || pos < 0 || pos >= game->n_spaces) return NULL;

  if(!game->spaces[pos]) return NULL;

  return game->spaces[pos];
}

/*Gets the number of spaces in a game*/
int game_get_n_spaces(Game *game) {
  if (!game) return -1;

  if (game->n_spaces < 0) return -1;

  return game->n_spaces;
}

/*It sets the number of spaces in a game*/
Status game_set_n_spaces(Game *game, int n_spaces) {
  if (!game) return ERROR;

  game->n_spaces = n_spaces;

  return OK;
}

/*Private function used in game_load_spaces to add a space to the last position on the list*/
Status game_add_space(Game *game, Space *space) {
  int n_spaces;

  /*Error check game == NULL in game_get_num_spaces*/
  if (((n_spaces = game_get_n_spaces(game)) == -1) || (space == NULL)) return ERROR;

  if (n_spaces >= MAX_SPACES) return ERROR;

  game->spaces[n_spaces] = space;
  if (game_set_n_spaces(game, n_spaces + 1) == ERROR) return ERROR;

  return OK;
}

void game_set_spaces_discovered_rec(Game *game, Space *space) {
  Bool connected, discovered;
  Link *link = NULL;
  int i;

  if (!game || !space) return;

  if (space_get_discovered(space, &discovered) == ERROR) return;
  if(discovered == TRUE) return;
  if (space_set_discovered(space, TRUE) == ERROR) return;

  /* We are only interested in NSEW */
  for(i = 0; i <= N_DIR - 3; i++) {
    if (!(link = game_get_link(game, space_get_id(space), i))) continue;;
    if(link_get_connected(link, &connected) == ERROR) continue;;
    if(connected == TRUE) game_set_spaces_discovered_rec(game, game_get_space(game, link_get_dest(link)));
  }
}

Status game_set_spaces_discovered (Game *game, Space *space) {
  Bool discovered;
  if (!game || !space) return ERROR;

  if (space_get_discovered(space, &discovered) == ERROR) return ERROR;
  if(discovered == TRUE) return OK;
  printf("pasa\n");
  game_set_spaces_discovered_rec(game, space);
 
  return OK;
}

int game_get_floor(Game *game, Space *space) {
  Id id = NO_ID;
  int floor = 0;

  if (!game || !space) return -1;

  if ((id = space_get_id(space)) == NO_ID) return -1;
  floor = (int)id / 1000;

  return floor;
}

/**
 * ***************  Links management  ***************
 */

/*Adds a link to the game*/
Status game_add_link(Game *game, Link *link) {
  if(!game || !link) return ERROR;

  if(game->n_links >= MAX_LINKS || game->n_links < 0) return ERROR;

  game->links[game->n_links] = link;
  game->n_links++;

  return OK;
}

/*It gets a link in a position of the array of links*/
Link *game_get_link_at_pos(Game *game, int pos) {
  if(!game || pos < 0 || pos >= game->n_links) return NULL;

  if(!game->links[pos]) return NULL;

  return game->links[pos];
}

/*Gets the number of links in a game*/
int game_get_n_links(Game *game) {
  if (!game) return -1;

  if (game->n_links < 0) return -1;

  return game->n_links;
}

/*Given the Id of a space and a direction returns the Id of the space linked in that direction*/
Id game_get_connection(Game *game, Id orig_space, Direction dir) {
  Id dest = NO_ID;
  
  int i = 0;

  if(!game || orig_space == NO_ID || dir == UNK_DIR) return NO_ID;

  for(i = 0; i < game->n_links; i++) {
    /* Error check link == NULL donde in link_get_orig */
    if(orig_space != link_get_orig(game->links[i])) continue;

    /* Debería checkear a ver si hay otro link con dest válida en caso de NO_ID?*/
    if((long)dir == (long)link_get_direction(game->links[i])) {
      dest = link_get_dest(game->links[i]);
      return dest;
    }
  }

  return dest;
}

/*Given the Id of a space and a direction returns the link in that direction*/
Link *game_get_link(Game *game, Id orig_space, Direction dir) {
  int i = 0;

  if(!game || orig_space == NO_ID || dir == UNK_DIR) return NULL;

  for(i = 0; i < game->n_links; i++) {
    /* Error check link == NULL in link_get_orig */
    if(orig_space != link_get_orig(game->links[i])) continue;

    if((long)dir == (long)link_get_direction(game->links[i])) {
      return game->links[i];
    }
  }

  return NULL;
}

/*Checks wether a connection is opened given a space and a desired direction*/
Status game_connection_is_open(Game *game, Id orig_space, Direction dir, Bool *bool) {
  int i = 0;

  if(!game || orig_space == NO_ID || dir == UNK_DIR || !bool) return ERROR;

  for(i = 0; i < game->n_links; i++) {
    /* Error check link == NULL donde in link_get_orig */
    if(orig_space != link_get_orig(game->links[i])) continue;

    if(dir == link_get_direction(game->links[i])) {
      return link_get_open(game->links[i], bool);;
    }
  }

  *bool = FALSE;
  return ERROR;
}

/**
 * ***************  Classes management  ***************
*/

/*Adds a class to the game*/
Status game_add_class(Game *game, Class *class){
  if(!game || !class) return ERROR;

  if(game->n_classes >= MAX_CLASS) return ERROR;

  game->class[game->n_classes] = class;
  game->n_classes++;

  return OK;
}

/*Gets the pointer to a class*/
Class *game_get_class(Game *game, Id id){
  int i=0;

  if(!game || id == NO_ID) return NULL;

  for(i = 0; i < game->n_classes; i++){
    if(id == class_get_id(game->class[i])) return game->class[i];
  }

  return NULL;
}

/*Gets the number of classes of a game*/
int game_get_n_classes(Game *game) {
  if (!game) return -1;

  if (game->n_classes < 0) return -1;

  return game->n_classes;
}

/*It gets the class in a position of the array of classes*/
Class *game_get_class_at_pos(Game *game, int pos) {
  if (!game || pos < 0) return NULL;

  if (pos >= game->n_classes) return NULL;

  return game->class[pos];
}

Class *game_get_class_from_id_obj(Game *game, Id id) {
  Object *obj = NULL;
  Id class_id = NO_ID;

  if (!game || id == NO_ID) return NULL;

  if (!(obj = game_get_object(game, id))) return NULL;

  if ((class_id = object_get_class_id(obj)) == NO_ID) return NULL;

  return game_get_class(game, class_id);
}

/**
 * ***************  Objects management  ***************
 */

/*Adds an object to the array of objects of the game*/
Status game_add_object(Game *game, Object *obj) {
  if (!game || !obj) return ERROR;

  if (game->n_objects >= MAX_OBJ) return ERROR;

  game->object[game->n_objects] = obj;
  game->n_objects++;

  return OK;
}

/*Gets the pointer to an object*/
Object *game_get_object(Game *game, Id id) {
  int i = 0;

  if (!game) return NULL;

  if (id == NO_ID) return NULL;

  for (i = 0; i < game->n_objects; i++) {
    if (id == object_get_id(game->object[i])) return game->object[i];
  }

  return NULL;
}

/*Gets the number of objects in a game*/
int game_get_n_objects(Game *game) {
  if (!game) return -1;

  if (game->n_objects < 0) return -1;

  return game->n_objects;
}

/*It gets an object's name from its id*/
char *game_get_obj_name_from_id(Game *game, Id id) {
  int i;
  Id obj_id;
  char *name = NULL;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_objects; i++) {
    if (!(obj_id = object_get_id(game->object[i]))) return NULL;

    name = class_get_name(game->class[i]);

    if (id == obj_id) return name;
  }

  return NULL;
}

/*It gets an object's id from its name*/
Id game_get_obj_id_from_name(Game *game, char *obj_name) {
  int i, n_obj, name_length;
  Id obj_id = NO_ID;
  Class *class = NULL;
  char *name = NULL;

  if (!game || !obj_name) return NO_ID;
  
  name_length = strlen(obj_name);
  
  if (((n_obj = game->n_objects) <= 0) || name_length > WORD_SIZE || name_length < MIN_ESPECIF)
    return NO_ID;
  
  for (i = 0; i < n_obj; i++) {
    if (!(class = game_get_class_from_id_obj(game, object_get_class_id(game->object[i])))) continue;
    if (!(name = class_get_name(class))) continue;

    /*Strstr allows us to get an object from  a fraction of its name, but we set
     * the minimum as 2 characters */
    if ((strncasecmp(name+1,obj_name+1, name_length-1) == 0) && (toupper(name[0]) == toupper(obj_name[0]))) {
      obj_id = object_get_id(game->object[i]);
      if (obj_id == NO_ID) continue;;

      return obj_id;
    }
  }
  
  return NO_ID;
}

Id game_get_obj_id_from_name_at_space(Game *game, char *obj_name, Id space_id) {
  int i, n_obj, name_length;
  Id obj_id = NO_ID;
  Space *space = NULL;
  Class *class = NULL;
  char *name = NULL;
  
  if (!game || !obj_name || space_id == NO_ID) return NO_ID;
  
  name_length = strlen(obj_name);
  space = game_get_space(game, space_id);
  
  if (((n_obj = space_get_num_objects(space)) <= 0) || name_length > WORD_SIZE || name_length < MIN_ESPECIF || !space) return NO_ID;
  
  for (i = 0; i < n_obj; i++) {
    if ((obj_id = space_get_object_at_pos(space, i)) == NO_ID) continue;
    if (!(class = game_get_class_from_id_obj(game, obj_id))) continue;
    if (!(name = class_get_name(class))) continue;

    /*Strstr allows us to get an object from  a fraction of its name, but we set
     * the minimum as 2 characters */ 
    printf("%s", name);
    
    if ((strncasecmp(name+1,obj_name+1, name_length-1) == 0) && (toupper(name[0]) == toupper(obj_name[0]))) return obj_id;
  }

  return NO_ID;
}

/*Gets the object in a position of the array of objects*/
Id game_get_object_location(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID || !game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) {
    if (space_find_object(game->spaces[i], id) == TRUE) {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

/*Declares the position of an object if posible*/
Status game_set_object_location(Game *game, Id obj, Id space_id) {
  Space *space = NULL;
  if (!game) return ERROR;

  if (!game_get_object(game, obj)) return ERROR;

  if (!(space = game_get_space(game, space_id))) return ERROR;

  if ((space_add_object(game_get_space(game, space_id), obj)) == ERROR)
    return ERROR;

  return OK;
}

/*Gets the object in a position of the array of objects*/
Object *game_get_object_at_pos(Game *game, int pos) {
  if (!game) return NULL;

  if (pos >= game->n_objects) return NULL;

  return game->object[pos];
}

/**
 * ***************  Characters management  ***************
 */

/*Adds a character to the game and sets its location*/
Status game_add_character(Game *game, Character *charr, Id location) {
  Space *charr_space = NULL;
  Id id_charr = NO_ID;

  if (!game || !charr || location == NO_ID) return ERROR;

  /*añade el character al array de characters y le añade a un espacio*/
  game->characters[game->n_characters] = charr;
  game->n_characters++;

  charr_space = game_get_space(game, location);
  if (!charr_space) return ERROR;

  if (space_characters_is_full(charr_space) == TRUE) return ERROR;

  id_charr = character_get_id(charr);
  if (id_charr == NO_ID) return ERROR;

  if (space_add_character(charr_space, id_charr) == ERROR) return ERROR;

  return OK;
}

/*Gets the pointer to a character from its id*/
Character *game_get_character_from_id(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_characters; i++) {
    if (id == character_get_id(game->characters[i])) return game->characters[i];
  }

  return NULL;
}

/*Gets the number of characters in a game*/
int game_get_n_characters(Game *game) {
  if (!game) return -1;

  if (game->n_characters < 0) return -1;

  return game->n_characters;
}

/*Gets the location of a character*/
Id game_get_character_location(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID || !game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) {
    if (space_find_character(game->spaces[i], id) == TRUE) return space_get_id(game->spaces[i]);
  }

  return NO_ID;
}

/*Sets a character to a certain space*/
Status game_set_character_location(Game *game, Id charr, Id loc) {
  Space *space = NULL;
  if (!game || charr == NO_ID || loc == NO_ID) return ERROR;

  if(!(space = game_get_space(game, loc))) return ERROR;

  if(space_characters_is_full(space) == TRUE) return ERROR;
  if (space_add_character(space, charr) == ERROR) return ERROR;

  return OK;
}

/*It gets a character's id from its name*/
Id game_get_charr_id_from_name(Game *game, char *charr_name){
  int i, n_charr, name_length;
  Id charr_id = NO_ID;
  char *aux_name = NULL;

  if (!game || !charr_name) return NO_ID;
  
  name_length = strlen(charr_name);
  
  if (((n_charr = game->n_characters) <= 0) || name_length > WORD_SIZE || name_length < MIN_ESPECIF)
    return NO_ID;
  
  for (i = 0; i < n_charr; i++) {
    if (!(aux_name = character_get_name(game->characters[i]))) continue;

    /*Strstr allows us to get an character from  a fraction of its name, but we set
     * the minimum as 2 characters */
    if (!strncasecmp(aux_name + 1, charr_name + 1, name_length-1) && toupper(aux_name[0]) == toupper(charr_name[0])) {
      charr_id = character_get_id(game->characters[i]);
      
      if (charr_id == NO_ID) return NO_ID;

      return charr_id;
    }
  }
  
  return NO_ID;
}

/*Gets a character's id from its name in a specific space*/
Id game_get_charr_id_from_name_at_space(Game *game, char *charr_name, Id space_id) {
  int i, n_charr, name_length;
  Id charr_id = NO_ID;
  Space *space = NULL;
  Character *aux_char = NULL;
  char *name = NULL;
  
  if (!game || !charr_name || space_id == NO_ID) return NO_ID;
  
  name_length = strlen(charr_name);
  space = game_get_space(game, space_id);
  
  if (((n_charr = space_get_num_characters(space)) <= 0) || name_length > WORD_SIZE || name_length < MIN_ESPECIF || !space) return NO_ID;
  
  for (i = 0; i < n_charr; i++) {
    if ((charr_id = space_get_character_at_pos(space, i)) == NO_ID) continue;
    if(!(aux_char = game_get_character_from_id(game, charr_id))) continue;

    name = character_get_name(aux_char);
    if(!name) continue;

    /*Strstr allows us to get an object from  a fraction of its name, but we set
     * the minimum as 2 characters */     
    if ((strncasecmp(name+1,charr_name+1, name_length-1) == 0) && (toupper(name[0]) == toupper(charr_name[0]))) return charr_id;
  }

  return NO_ID;
}

/*Gets the character in a position of the array of characters*/
Character *game_get_character_at_pos(Game *game, int pos) {
  if (!game) return NULL;

  if (pos < 0 || pos >= game->n_characters) return NULL;

  return game->characters[pos];
}

/**
 ****************** Interactions management*****************
*/

/*Given two roles in the game, returns wether their relationship is friendly or not*/
Status game_get_friendly(Role role1, Role role2, Bool *relationship) {
  if((role1) == NO_ROLE || (role2) == NO_ROLE) {
    *relationship = FALSE;
    return ERROR;
  }

  if((role1) == UNDEFINED || (role2) == UNDEFINED) {
    *relationship = TRUE;
    return OK;
  }

  switch (role1) {
    case PEACEFUL:
      *relationship = TRUE;
      return OK;
      break;
    
    case HOSTILE:
      if(role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case TEAM1:
      if(role2 == TEAM1 || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case TEAM2:
      if(role2 == TEAM2 || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case MONSTER:
      if(role2 == MONSTER || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    default:
      break;
  }

  *relationship = FALSE;
  return ERROR;
}

/*Given two roles in the game, returns wether they are allies or not*/
Status game_get_ally(Role role1, Role role2, Bool *relationship) {
  if((role1) == NO_ROLE || (role2) == NO_ROLE) {
    *relationship = FALSE;
    return ERROR;
  }

  if((role1) == UNDEFINED || (role2) == UNDEFINED) {
    *relationship = FALSE;
    return OK;
  }

  switch (role1) {
    case PEACEFUL:
      *relationship = TRUE;
      return OK;
      break;
    
    case HOSTILE:
      if(role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case TEAM1:
      if(role2 == TEAM1 || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case TEAM2:
      if(role2 == TEAM2 || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    case MONSTER:
      if(role2 == MONSTER || role2 == PEACEFUL) (*relationship = TRUE);
      else (*relationship = FALSE);
      return OK;
      break;

    default:
      break;
  }

  *relationship = FALSE;
  return ERROR;
}

/**
 * ***************  Minimap management  ***************
 */

/*Sets the graphic description of a minimap*/
Status game_set_minimap_at(Game *game, char *gdesc, int pos, int floor) {
  int i = 0;

  if (!game || !gdesc || floor < 0 || floor >= NUM_FLOORS || pos < 0 || pos >= MAP_HEIGHT) return ERROR;

  sprintf(game->minimap[floor][pos], "%s", gdesc);

  /*We prevent from saving a line break in the gdesc*/
  for (i = 0; i < MAP_WIDTH; i++) {
    if ((game->minimap[floor][pos][i] == '\n') || (game->minimap[floor][pos][i] == '\r'))
      game->minimap[floor][pos][i] = ' ';
  }

  return OK;
}

/*Gets the graphic descrpition of a minimap*/
char *game_get_minimap_at(Game *game, int line, int floor) {
  if (!game || line < 0 || line >= MAP_HEIGHT || floor < 0 || floor >= NUM_FLOORS) return NULL;

  return game->minimap[floor][line];
}

/**
 * ***************  Last message management  ***************
 */
  
char *game_get_last_message_at_pos(Game *game, int play_pos, int msg_pos) {
  if (!game) return NULL;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return NULL;
  return game->data[play_pos]->messages[msg_pos]->msg;
}

Status game_set_last_message_msg_at_pos(Game *game, int play_pos, int msg_pos, char *msg) {
  if (!game || !msg) return ERROR;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return ERROR;
  sprintf((game->data[play_pos])->messages[msg_pos]->msg, "%.*s", MESG_SIZE, msg);
  return OK;
}

Bool game_get_last_message_visibility_at_pos(Game *game, int play_pos, int msg_pos) {
  if (!game) return FALSE;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return FALSE;
  return game->data[play_pos]->messages[msg_pos]->visible;
}

Status game_set_last_message_visibility_at_pos(Game *game, int play_pos, int msg_pos, Bool visibility) {
  if (!game) return ERROR;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return ERROR;
  game->data[play_pos]->messages[msg_pos]->visible = visibility;
  return OK;
}

Type game_get_last_message_sender_type_at_pos(Game *game, int play_pos, int msg_pos) {
  if (!game) return NO_TYPE;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return NO_TYPE;
  return game->data[play_pos]->messages[msg_pos]->sender_type;
}

Status game_set_last_message_sender_type_at_pos(Game *game, int play_pos, int msg_pos, Type type) {
  if (!game || type == NO_TYPE) return ERROR;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return ERROR;
  game->data[play_pos]->messages[msg_pos]->sender_type = type;
  return OK;
}

Status game_set_last_message_sender_at_pos(Game *game, int play_pos, int msg_pos, Id sender) {
  if (!game || sender == NO_ID) return ERROR;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return ERROR;
  game->data[play_pos]->messages[msg_pos]->sender = sender;
  return OK;
}

Id game_get_last_message_sender_at_pos(Game *game, int play_pos, int msg_pos) {
  if (!game) return NO_ID;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return NO_ID;
  return game->data[play_pos]->messages[msg_pos]->sender;
}

char *game_get_last_message_sender_name_at_pos(Game *game, int play_pos, int msg_pos) {
  Type type = NO_TYPE;
  char *aux_name = NULL;

  if (!game) return NULL;
  if (play_pos < 0 || play_pos >= game->n_players || msg_pos < 0 || msg_pos >= NUM_MSGS) return NULL;

  type = game->data[play_pos]->messages[msg_pos]->sender_type;

  switch (type)
  {
  case PLAYER:
    aux_name = player_get_name(game_get_player_from_id(game, game->data[play_pos]->messages[msg_pos]->sender));
    break;

  case CHARACTER:
    aux_name = character_get_name(game_get_character_from_id(game, game->data[play_pos]->messages[msg_pos]->sender));
    break;

  case OBJECT:
    aux_name = class_get_name(game_get_class_from_id_obj(game, game->data[play_pos]->messages[msg_pos]->sender));
    break;
  
  default:
    aux_name = NULL;
    break;
  }

  return aux_name;
}

Status game_erase_all_messages(Game *game) {
  int i = 0;

  if (!game) return ERROR;
  if (game->turn < 0 || game->turn >= game->n_players) return ERROR;

  for(i = 0; i < NUM_MSGS; i++) {
    game->data[game->turn]->messages[i]->visible = FALSE;
    game->data[game->turn]->messages[i]->sender = NO_ID;
    game->data[game->turn]->messages[i]->sender_type = NO_TYPE;
    game->data[game->turn]->messages[i]->msg[0] = '\0';
  }

  return OK;

}

/*Sets the last displayed message in reverse order*/
Status game_set_last_message(Game *game, char *message) {
  InterfaceData *interfaceData = NULL;
  int i = 0;

  if (!game || !message) return ERROR;
  if (game->turn < 0 || game->turn >= game->n_players) return ERROR;

  interfaceData = game->data[game->turn];
  if (!interfaceData) return ERROR;

  for (i = 0; i < NUM_MSGS; i++) {
    if (!interfaceData->messages[i]) return ERROR;
    if (interfaceData->messages[i]->visible == FALSE) break;
  }

  if (i == NUM_MSGS) {
    for (i = 0; i < NUM_MSGS - 1; i++) {
      if (!interfaceData->messages[i] || !interfaceData->messages[i + 1]) return ERROR;
      interfaceData->messages[i]->visible = interfaceData->messages[i + 1]->visible;
      sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, interfaceData->messages[i + 1]->msg);
      interfaceData->messages[i]->sender = interfaceData->messages[i + 1]->sender;
      interfaceData->messages[i]->sender_type = interfaceData->messages[i + 1]->sender_type;
    }
    i = NUM_MSGS - 1;
  }

  if (!interfaceData->messages[i]) return ERROR;
  sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, message);
  interfaceData->messages[i]->visible = TRUE;
  interfaceData->messages[i]->sender = NO_ID;
  interfaceData->messages[i]->sender_type = NO_TYPE;

  return OK;
}

/*Sets the last displayed message at a desired position */
Status game_set_last_message_at_pos(Game *game, int play_pos, char *message) {
  InterfaceData *interfaceData = NULL;
  int i = 0;

  if (!game || !message || play_pos < 0 || play_pos >= game->n_players) return ERROR;

  interfaceData = game->data[play_pos];
  if (!interfaceData) return ERROR;

  for (i = 0; i < NUM_MSGS; i++) {
    if (!interfaceData->messages[i]) return ERROR;
    if (interfaceData->messages[i]->visible == FALSE) break;
  }

  if (i == NUM_MSGS) {
    for (i = 0; i < NUM_MSGS - 1; i++) {
      if (!interfaceData->messages[i] || !interfaceData->messages[i + 1]) return ERROR;
      interfaceData->messages[i]->visible = interfaceData->messages[i + 1]->visible;
      sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, interfaceData->messages[i + 1]->msg);
      interfaceData->messages[i]->sender = interfaceData->messages[i + 1]->sender;
      interfaceData->messages[i]->sender_type = interfaceData->messages[i + 1]->sender_type;
    }
    i = NUM_MSGS - 1;
  }

  if (!interfaceData->messages[i]) return ERROR;
  sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, message);
  interfaceData->messages[i]->visible = TRUE;
  interfaceData->messages[i]->sender = NO_ID;
  interfaceData->messages[i]->sender_type = NO_TYPE;

  return OK;
}

Status game_set_last_message_at_pos_with_info(Game *game, int play_pos, char *message, Id send, Type send_type) {
  InterfaceData *interfaceData = NULL;
  int i = 0;

  if (!game || !message ||send_type == NO_TYPE) return ERROR;
  if ((send_type != GAME) && (send == NO_ID)) return ERROR;
  if (play_pos < 0 || play_pos >= game->n_players) return ERROR;

  interfaceData = game->data[play_pos];
  if (!interfaceData) return ERROR;

  for (i = 0; i < NUM_MSGS; i++) {
    if (!interfaceData->messages[i]) return ERROR;
    if (interfaceData->messages[i]->visible == FALSE) break;
  }

  if (i == NUM_MSGS) {
    for (i = 0; i < NUM_MSGS - 1; i++) {
      if (!interfaceData->messages[i] || !interfaceData->messages[i + 1]) return ERROR;
      interfaceData->messages[i]->visible = interfaceData->messages[i + 1]->visible;
      sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, interfaceData->messages[i + 1]->msg);
      interfaceData->messages[i]->sender = interfaceData->messages[i + 1]->sender;
      interfaceData->messages[i]->sender_type = interfaceData->messages[i + 1]->sender_type;
    }
    i = NUM_MSGS - 1;
  }

  if (!interfaceData->messages[i]) return ERROR;
  sprintf(interfaceData->messages[i]->msg, "%.*s", MESG_SIZE, message);
  interfaceData->messages[i]->visible = TRUE;
  interfaceData->messages[i]->sender = send;
  interfaceData->messages[i]->sender_type = send_type;

  return OK;
}

/*It gets the last message of the interface data of a player at a desired position*/
char *game_get_last_message_msg_at_pos(Game *game, int play_pos) {
  if (!game) return NULL;
  if (play_pos < 0 || play_pos >= game->n_players) return NULL;

  return game->data[play_pos]->messages[0]->msg;
}
  

/**
 * ***************  Close up management  ***************
*/

/*Gets a line from the last close up shown*/
char *game_get_last_close_up_at(Game *game, int pos) {
  if(!game) return NULL;

  if(pos < 0 || pos >= POV_HGHT) return NULL;
  
  return (game->data[game->turn])->last_closeup[pos];
}

/*Sets the last close up*/
Status game_set_last_close_up(Game *game, char *closeup, int pos) {
  int i;

  if (!game) return ERROR;

  if (pos < 0 || pos >= POV_HGHT) return ERROR;

  if (!closeup) (game->data[game->turn])->last_closeup[pos][0] = '\0';

  sprintf((game->data[game->turn])->last_closeup[pos], "%-*.*s", POV_WDTH, POV_WDTH, closeup);

  /*We prevent from a saving a line break in the closeup*/
  for (i = 0; i < POV_WDTH; i++) {
    if (((game->data[game->turn])->last_closeup[pos][i] == '\n') || ((game->data[game->turn])->last_closeup[pos][i] == '\r'))
    (game->data[game->turn])->last_closeup[pos][i] = ' ';
  }

  return OK;
}

/*Sets the last close up of a specific player*/
Status game_set_last_close_up_at_pos(Game *game, char *closeup, int pos, int line) {
  int i;

  if (!game) return ERROR;

  if (pos < 0 || pos >= game->n_players) return ERROR;

  if (line < 0 || line >= POV_HGHT) return ERROR;

  if (!closeup) (game->data[pos])->last_closeup[line][0] = '\0';

  sprintf((game->data[pos])->last_closeup[line], "%-*.*s", POV_WDTH, POV_WDTH, closeup);

  /*We prevent from a saving a line break in the closeup*/
  for (i = 0; i < POV_WDTH; i++) {
    if (((game->data[pos])->last_closeup[line][i] == '\n') || ((game->data[pos])->last_closeup[line][i] == '\r'))
    (game->data[pos])->last_closeup[line][i] = ' ';
  }

  return OK;  
}

/**
 * ***************  Command management  ***************
 */

/*It gets the status of the last command*/
Status game_get_last_status(Game *game) {
  if (!game) return ERROR;

  if(game->turn < 0 || game->turn >= game->n_players) return ERROR;

  return command_get_status(game->data[game->turn]->last_cmds[0]);
}

/*It gets a command from a desided position of the interface data of a player at a desired position*/
Command *game_get_command_at_pos(Game *game, int play_pos, int cmd_pos) {
  if(!game) return NULL;

  if(play_pos < 0 || play_pos >= game->n_players || cmd_pos < 0 || cmd_pos >= NUM_CMDS) return NULL;

  return game->data[play_pos]->last_cmds[cmd_pos];
}

/*It gets the status at a position of the interface data struct of commands*/
Status game_get_last_status_at_pos(Game *game, int pos) {
  if(!game || pos < 0 || pos >= NUM_CMDS) return ERROR;

  if(game->turn < 0 || game->turn >= game->n_players) return ERROR;

  return command_get_status((game->data[game->turn])->last_cmds[pos]);
}

/*Given the status of the last command, the function sets it as the last one*/
Status game_set_last_status(Game *game, Status status) {
  InterfaceData *interfaceData = NULL;
  if (!game) return ERROR;

  if(game->turn < 0 || game->turn >= game->n_players) return ERROR;
  
  interfaceData = game->data[game->turn];
  if(!interfaceData) return ERROR;

  return command_set_status(interfaceData->last_cmds[0], status);;
}

/*It gets the last command from the game struct*/
Command *game_get_last_command(Game *game) { 
  if(!game) return NULL;

  if(game->turn < 0 || game->turn >= game->n_players) return NULL;

  return (game->data[game->turn])->last_cmds[0]; 
}

/*It gets the last command at a desired position from the game struct*/
Command *game_get_last_command_at_pos(Game *game, int pos) { 
  if(!game || pos < 0 || pos >= NUM_CMDS) return NULL;

  if(game->turn < 0 || game->turn >= game->n_players) return NULL;

  return (game->data[game->turn])->last_cmds[pos]; 
}

/*Given a command, the function sets it as the last one*/
Status game_set_last_command(Game *game, Command *command) {
  InterfaceData *interfaceData = NULL;

  if (!game || !command) return ERROR;

  if(game->turn < 0 || game->turn >= game->n_players) return ERROR;

  interfaceData = game->data[game->turn];
  if(!interfaceData) return ERROR;

  interfaceData->last_cmds[2] = interfaceData->last_cmds[1];
  interfaceData->last_cmds[1] = interfaceData->last_cmds[0];
  interfaceData->last_cmds[0] = command;

  return OK;
}

/**
 * ***************  Deterministic management  ***************
 */

Status game_set_deterministic(Game *game, Bool deterministic) {
  if (!game) return ERROR;

  game->deterministic = deterministic;

  return OK;
}

Status game_get_deterministic(Game *game, Bool *deterministic) {
  if (!game || !deterministic) return ERROR;
  deterministic = &game->deterministic;

  return OK;
}

/**
 * ***************  Finished management  ***************
 */

/*Checks if the game is finished*/
Bool game_get_finished(Game *game) { return game->finished; }

/*Updates the status of the game (finished or not)*/
Status game_set_finished(Game *game, Bool finished) {
  if (!game) return ERROR;

  game->finished = finished;

  return OK;
}

/**
 * ***************  Saved management  ***************
 */
Status game_save(Game *game, char *filename) {
  FILE *create_file = NULL;

  if (!game || !filename) return ERROR;

  create_file = fopen(filename, "w");
  fclose(create_file);

  if (game_management_save_spaces(game, filename) == ERROR) return ERROR;
  if (game_management_save_links(game, filename) == ERROR) return ERROR;
  if (game_management_save_classes(game, filename) == ERROR) return ERROR;
  if (game_management_save_objects(game, filename) == ERROR) return ERROR;
  if (game_management_save_characters(game, filename) == ERROR) return ERROR;
  if (game_management_save_players(game, filename) == ERROR) return ERROR;
  if (game_management_save_turn(game, filename) == ERROR) return ERROR;
  if (game_management_save_mode(game, filename) == ERROR) return ERROR;
  if (game_management_save_minimap(game, filename) == ERROR) return ERROR;

  return OK;
}

Status game_load(Game **game, char *filename) {
  Status st = OK;
  FILE *file = NULL;
  if (!game || !(*game) || !filename) return ERROR;

  /* We first check if the file exists */
  if(!(file = fopen(filename, "r"))) return ERROR;
  fclose(file);
  
  /* In order to load a new game, we save it in savetoload.dat. This way, in case of error we reload the game from here */
  if (game_save(*game, "savetoload.dat") == ERROR) return ERROR;
  game_destroy(*game);

  if (!((*game) = game_create())) st = ERROR;
  if (game_create_from_file(*game, filename) == ERROR) st = ERROR;

  /* In case of error, we try to reload the game. The second check is in order to avoid loops */
  if ((st = ERROR) && strcmp(filename, "savetoload.dat") != 0) {
    game_load(game, "savetoload.dat");
    return ERROR;
  }

  return st;
}

/**
 * ***************  Debugging functions  ***************
 */

/*Prints information about every space in the game and the object and player's location*/
Status game_print(Game *game) {
  int i = 0, j = 0;
  char *minimap = NULL;

  if (!game) return ERROR;

  fprintf(stdout, "=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    fprintf(stdout, "-> Space %d:\n", i);
    space_print(game->spaces[i]);
  }

  fprintf(stdout, "=> Links \n");
  for(i = 0; i < game->n_links; i++) {
    fprintf(stdout, "-> Link %d:\n", i);
    link_print(game->links[i]);
  }

  fprintf(stdout, "=> Objects: \n");
  for (i = 0; i < game->n_objects; i++) {
    fprintf(stdout, "-> Object %d:\n", i);
    object_print(game->object[i]);
    fprintf(stdout, "--> Object location: %d\n", (int)game_get_object_location(game, object_get_id(game->object[i])));
  }
  
  fprintf(stdout, "=> Players: \n");
  for (i = 0; i < game->n_players; i++) {
    fprintf(stdout, "\n-> Player %d:\n", i);
    player_print(game->players[i]);
    game_interface_data_print(game->data[i]);
  }

  fprintf(stdout, "=> Chracters: \n");
  for (i = 0; i < game->n_characters; i++) {
    fprintf(stdout, "\n-> Character %d:\n", i);
    character_print(game->characters[i]);
    fprintf(stdout, "--> Character location: %d\n", (int)game_get_character_location(game, character_get_id(game->characters[i])));
  }

  fprintf(stdout, "=> Classes: \n");
  for (i = 0; i < game->n_classes; i++) {
    fprintf(stdout, "\n-> Class %d:\n", i);
    class_print(game->class[i]);
  }

  fprintf(stdout, "=> Deterministic: %d\n", (int)game->deterministic);

  fprintf(stdout, "=> Finished: %d\n", (int)game->finished);

  fprintf(stdout, "=> Minimaps: \n");
  for (i = 0; i < NUM_FLOORS; i++) {
    fprintf(stdout, "\n-> Floor %d:\n", i);
    for (j = 0; j < MAP_HEIGHT; j++) {
      minimap = game_get_minimap_at(game, j, i);
      fprintf(stdout, "%s\n", minimap);
    }
  }

  return OK;
}
