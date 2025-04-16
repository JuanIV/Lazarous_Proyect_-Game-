/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"

/**
 * @brief Width of the map area of the screen
 *
 */
#define WIDTH_MAP (3*SQ_SZ)

/**
 * @brief Width of the description area of the screen
 *
 */
#define WIDTH_DES 42

/**
 * @brief Width of the banner area of the screen
 *
 */
#define WIDTH_BAN 23

/**
 * @brief Height of the map area of the screen
 *
 */
#define HEIGHT_MAP 32

/**
 * @brief Height of the banner area of the screen
 *
 */
#define HEIGHT_BAN 1

/**
 * @brief Height of the help area of the screen
 *
 */
#define HEIGHT_HLP 2

/**
 * @brief Height of the feedback area of the screen
 *
 */
#define HEIGHT_FDB 3

/**
 * @brief Number of spaces in a cross
 *
 */
#define CROSS_NUM 5

/**
 * @brief length of the graphic description of the player
 *
 */
#define PLAY_GDSC_LEN 6

/**
 * @brief Ammount of characters from the space id that will be printed in the map
 * 
 */
#define SP_ID_PRINT 4

/**
 * @brief Ammount of characters from the space name that will be printed in the map
 * 
 */
#define SP_NAME_PRINT (SQ_IN_SZ-1-SP_ID_PRINT)

/**
 * @brief Size of a square in the map
 * 
 */
#define SQ_SZ 19

/**
 * @brief Size of a square in the map
 * 
 */
#define SQ_IN_SZ (SQ_SZ-4)

/**
 * @brief Maximum number of objects in a space that will be printed
 * 
 */
#define NUM_OBJS_PRINT 4

/**
 * @brief Characters of the name of the object that will be printed
 * 
 */
#define OBJ_GD_SZ 2

/**
 * @brief Space in the descriprion area to put the names of players and characters
 * 
 */
#define DESC_NAMES_SZ 14

/**
 * @brief Space in the description area to put the locations info
 * 
 */
#define DESC_ID_SZ 5

/**
 * @brief Struct that stores the information of the graphic engine: Id, name and desc
 * @author Profesores PPROG
 * 
 */
struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

/*
 * ************ Declaration of private functions ***************
 */

/**
 * @brief It prints a row of spaces in the map area
 * @author Juan Ibáñez
 *
 * @param game Pointer to the game
 * @param ge Pointer to the graphic engine
 * @param left Id of the space on the left of the row
 * @param center Id of the space on the center of the row
 * @param right Id of the space on the right of the row
 */
void graphic_engine_map_print_row(Game *game, Graphic_engine *ge, Id left, Id center, Id right);
/**
 * @brief It prints the adjacent spaces to a spaces location
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param ge Pointer to the graphic engine
 * @param center Id of the space in the center of the cross
 */
void graphic_engine_map_print_cross(Game *game, Graphic_engine *ge, Id center);

/*
 * ************** Implementation of private functions ****************
 */

void graphic_engine_map_print_row(Game *game, Graphic_engine *ge, Id left, Id center, Id right) {
  Id ids[3], obj_id = NO_ID;
  Space *space[3] = {NULL};
  Bool discovered[3] = {FALSE, FALSE, FALSE};
  Character *charr = NULL;
  Object *obj = NULL;
  char charr_gdesc[CHR_GD_SZ + 1], space_gdesc[SP_GD_WTH + 1];
  char player_gdesc[PLAY_GDSC_LEN + 1];
  char line[WIDTH_MAP + 1];
  char movement_sign;
  int i = 0, j = 0, count = 0, count2 = 0;

  ids[0] = left;
  ids[1] = center;
  ids[2] = right;

  for(i=0;i<3;i++){
    space[i] = game_get_space(game,ids[i]);
    if(space[i]) discovered[i] = space_get_discovered(space[i]);
  }

  for(i=0, count =0;i<3;i++){
    if(space[i]) count += sprintf(line + count," +---------------+ ");
    else count += sprintf(line + count, "%*s", SQ_SZ,"");
  }
  screen_area_puts(ge->map, line);

  for(i=0, count = 0; i<3;i++){
    if(space[i]) {
      if(discovered[i] == TRUE) {
        count += sprintf(line + count," |%-*.*s %*ld| ", SP_NAME_PRINT,SP_NAME_PRINT,space_get_name(space[i]),SP_ID_PRINT,ids[i]);
      }
      else count += sprintf(line + count," |       ?       | ");
    } else count += sprintf(line + count, "%*s", SQ_SZ,"");
  }
  screen_area_puts(ge->map, line);

  /*Line with the character and player*/
  for(i=0, count = 0; i<3;i++){
    if(space[i]){
      if(discovered[i]){
        charr = game_get_character_from_id(game,space_get_character_at_pos(space[i], 0));
        if (charr && character_get_health(charr) > 0) {
          sprintf(charr_gdesc, "%*.*s", CHR_GD_SZ,CHR_GD_SZ,character_get_gdesc(charr));
        } else sprintf(charr_gdesc, "%*s", CHR_GD_SZ,"");
  
        if(ids[i] == game_get_player_location(game)) 
          sprintf(player_gdesc,"%-*.*s", PLAY_GDSC_LEN, PLAY_GDSC_LEN, player_get_gdesc(game_get_player(game)));
        else sprintf(player_gdesc,"%*s",PLAY_GDSC_LEN,"");
  
        count += sprintf(line + count," | %-*.*s  %*.*s| ",PLAY_GDSC_LEN,PLAY_GDSC_LEN,player_gdesc,CHR_GD_SZ,CHR_GD_SZ, charr_gdesc);
      } else count += sprintf(line + count," |%*s| ", SQ_IN_SZ,"");
      
    } else count += sprintf(line + count, "%*s", SQ_SZ,"");
  }
  screen_area_puts(ge->map, line);

  /*GDESC*/
  for(j=0;j<SP_GD_HGHT;j++){
    for(i=0, count = 0;i<3;i++){
      if(space[i]){

        if((j==2) && (ids[i] == game_get_player_location(game))){
          if(game_get_connection(game, ids[i], W) != NO_ID){
            if(game_connection_is_open(game,ids[i],W) == TRUE) movement_sign = '<';
            else movement_sign = 'X';
          } else movement_sign = ' ';
        } else movement_sign = ' ';
        count += sprintf(line + count,"%c",movement_sign);

        if(discovered[i]) strcpy(space_gdesc, space_get_gdesc_at(space[i],j));
        else strcpy(space_gdesc, " ");

        count += sprintf(line + count,"|%-*.*s%*s|",SP_GD_WTH,SP_GD_WTH,space_gdesc,SQ_IN_SZ - SP_GD_WTH,"");
      
        if((j==2) && (ids[i] == game_get_player_location(game))){
          if(game_get_connection(game, ids[i], E) != NO_ID){
            if(game_connection_is_open(game,ids[i],E) == TRUE) movement_sign = '>';
            else movement_sign = 'X';
          } else movement_sign = ' ';
        } else movement_sign = ' ';
        count += sprintf(line + count,"%c",movement_sign);

      } else count += sprintf(line + count, "%*s", SQ_SZ,"");
    }
    screen_area_puts(ge->map, line);
  }

  /*Print objects*/
  for(i=0,count=0;i<3;i++){
    if(space[i]){
      if(discovered[i]){
        count += sprintf(line + count," |");
        for(j=0, count2 = 0; j<space_get_num_objects(space[i]) && j<NUM_OBJS_PRINT; j++){
          obj_id = space_get_object_at_pos(space[i],j);
          if(obj_id != NO_ID){
            obj = game_get_object(game,obj_id);
            count2 += sprintf(line + count + count2, "%-*.*s ", OBJ_GD_SZ, OBJ_GD_SZ, object_get_name(obj));
          }
        }
        if(space_get_num_objects(space[i]) > NUM_OBJS_PRINT)
        count2 += sprintf(line + count + count2, "...");
  
        count += sprintf(line + count + count2, "%*s| ",SQ_IN_SZ-count2,"");
        count += count2;

      } else count += sprintf(line + count, " |%*s| ", SQ_IN_SZ,"");

    } else count += sprintf(line + count, "%*s", SQ_SZ,"");
  }
  screen_area_puts(ge->map, line);

  for(i=0, count =0;i<3;i++){
    if(space[i]) count += sprintf(line + count," +---------------+ ");
    else count += sprintf(line + count, "%*s", SQ_SZ,"");
  }
  screen_area_puts(ge->map, line);
}

void graphic_engine_map_print_cross(Game *game, Graphic_engine *ge, Id center) {
	Id ids[CROSS_NUM-1];
  char line[WIDTH_MAP + 1];

  if(!game || !ge || center == NO_ID) return;

	/*Get all posible spaces*/
	ids[0] = game_get_connection(game, center, N);
	ids[1] = game_get_connection(game, center, E);
	ids[2] = game_get_connection(game, center, S);
	ids[3] = game_get_connection(game, center, W);

  /*Print the space upwards*/
	graphic_engine_map_print_row(game,ge,NO_ID,ids[0],NO_ID);

  if(ids[0] != NO_ID){
    if(game_get_connection(game,center,N) != NO_ID){
      if(game_connection_is_open(game,center,N) == TRUE){
        sprintf(line,"%*s         ^         %*s",SQ_SZ,"",SQ_SZ,"");
        screen_area_puts(ge->map, line);
      } else {
        sprintf(line,"%*s         X         %*s",SQ_SZ,"",SQ_SZ,"");
        screen_area_puts(ge->map, line);
      }
    } else sprintf(line,"%*s",WIDTH_MAP,"");
  }
  
  /*Print the spaces in the middle*/
  graphic_engine_map_print_row(game,ge,ids[3],center,ids[1]);

  if(ids[2] != NO_ID){
    if(game_get_connection(game,center,S) != NO_ID){
      if(game_connection_is_open(game,center,S) == TRUE){
        sprintf(line,"%*s         v         %*s",SQ_SZ,"",SQ_SZ,"");
        screen_area_puts(ge->map, line);
      } else {
        sprintf(line,"%*s         X         %*s",SQ_SZ,"",SQ_SZ,"");
        screen_area_puts(ge->map, line);
      }
    } else sprintf(line,"%*s",WIDTH_MAP,"");
  }

  /*Print the space underneath*/
	graphic_engine_map_print_row(game,ge,NO_ID,ids[2],NO_ID);  
}

/*
 * ****************** Implementation of public functions
 * **************************
 */

/*Creates a new graphic engine initializing all screen areas according to their area resolution*/
Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) return ge;

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4,
              WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) return NULL;

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

/*Destroys a graphic engine destroying each dedicated area and freeing allocated memory*/
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/*Paints each area according to its function with the necessary information*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID;
  Status last_status = ERROR;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, aux_health, turn;
  Object *aux_obj = NULL;
  Character *aux_charr = NULL;
  Player *aux_player = NULL;
  Id aux_obj_id = NO_ID, aux_charr_id = NO_ID;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    graphic_engine_map_print_cross(game,ge,id_act);
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);

  /*OBJECTS*/
  sprintf(str, " Objects:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_objects(game); i++) {
    aux_obj = game_get_object_at_pos(game, i);
    if (!aux_obj) continue;

    aux_obj_id = object_get_id(aux_obj);
    if (aux_obj_id == NO_ID) continue;

    if (player_has_object(game_get_player(game), aux_obj_id) || game_get_object_location(game,aux_obj_id) == NO_ID) {
      continue;
    }

    sprintf(str, "  %-*.*s: %-*d", DESC_NAMES_SZ,DESC_NAMES_SZ, object_get_name(aux_obj), DESC_ID_SZ,(int)game_get_object_location(game, aux_obj_id));
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  
  /*CHARACTERS*/
  sprintf(str, " Characters:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_characters(game); i++) {
    aux_charr = game_get_character_at_pos(game, i);
    if (!aux_charr) continue;

    aux_charr_id = character_get_id(aux_charr);
    if (aux_charr_id == NO_ID) continue;

    aux_health = character_get_health(aux_charr);
    if (aux_health <= 0) continue;

    sprintf(str, "  %-*.*s: %-*d (%d)", DESC_NAMES_SZ,DESC_NAMES_SZ, character_get_gdesc(aux_charr),DESC_ID_SZ, (int)game_get_character_location(game, aux_charr_id), aux_health);
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /*PLAYERS*/
  sprintf(str, " Players:");
  screen_area_puts(ge->descript, str);
  for(i = 0; i<game_get_n_players(game);i++){
    aux_player = game_get_player_at(game, i);
    if(!aux_player) continue;
    
    aux_health = player_get_health(aux_player);
    if(aux_health < 0) continue;

    sprintf(str, "  %-*.*s: %-*d (%d)", DESC_NAMES_SZ,DESC_NAMES_SZ,player_get_name(aux_player), DESC_ID_SZ, (int)player_get_location(aux_player), aux_health);
    screen_area_puts(ge->descript, str);
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /*INVENTORY*/
  sprintf(str, " Inventory:");
  screen_area_puts(ge->descript, str);
  for (i = 0; i < game_get_n_objects(game); i++) {

    aux_obj = game_get_object_at_pos(game, i);
    if (!aux_obj) continue;

    aux_obj_id = object_get_id(aux_obj);
    if (aux_obj_id == NO_ID) continue;

    if (player_has_object(game_get_player(game), aux_obj_id)){
      sprintf(str, "  %-*.*s", DESC_NAMES_SZ,DESC_NAMES_SZ, object_get_name(aux_obj));
      screen_area_puts(ge->descript, str);
    }

    
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /*MESSAGE*/
  sprintf(str, " Message:");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  %s", game_get_last_message(game));
  screen_area_puts(ge->descript, str);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "    The anthill game ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:  move or m (N,S,E,W), exit or e, take or t, ");
  screen_area_puts(ge->help, str);
  sprintf(str," drop or d, attack or at, chat or c, inspect or i, recruit or r and abandon or ab");
  screen_area_puts(ge->help, str);

  /* Paint in the feedback area */
  for(i = 1; i<=NUM_CMDS; i++) {
    last_cmd = command_get_code(game_get_last_command_at_pos(game, NUM_CMDS-i));
    last_status = command_get_status(game_get_last_command_at_pos(game, NUM_CMDS-i));
    if (last_status == OK) {
      sprintf(str, " %s (%s): OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
    } else {
      sprintf(str, " %s (%s): ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
    }
    screen_area_puts(ge->feedback, str);
  }

  /* Dump to the terminal */
  if((turn = game_get_turn(game)) == -1) return;
  screen_paint(BLUE + turn);
  printf("prompt:> ");
}
