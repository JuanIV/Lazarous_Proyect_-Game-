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

/**********************************************************
 * ***************** AREA SIZES DEFINITION ****************
 * ********************************************************/

/**
 * @brief Width of the map area of the screen
 *
 */
#define WIDTH_MAP (3*SQ_SZ+4)

/**
 * @brief Height of the map area of the screen
 *
 */
#define HEIGHT_MAP 34

/**
 * @brief Width of the description area of the screen
 *
 */
#define WIDTH_MSG 120

/**
 * @brief Height of the message area of the screen
 *
 */
#define HEIGHT_MSG (POV_HGHT + HEIGHT_FDB + 1)

/**
 * @brief Width of the player info area
 * 
 */
#define WIDTH_PINF 30

/**
 * @brief Height of the player info area
 * 
 */
#define HEIGHT_PINF (HEIGHT_MAP)

/**
 * @brief Width of the feedback area of the screen
 * 
 */
#define WIDTH_FDB (POV_WDTH)

/**
 * @brief Height of the feedback area of the screen
 *
 */
#define HEIGHT_FDB 3

/**
 * @brief Width of the description area
 * 
 */
#define WIDTH_DESC ((WIDTH_MSG + POV_WDTH + 1)-(WIDTH_MAP + WIDTH_PINF + 2))

/**
 * @brief Height of the description area
 * 
 */
#define HEIGHT_DESC (HEIGHT_MAP)


/** *********************************************************
 * **************** PRINTING INFO MACROS ********************
 * **********************************************************/

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
#define SQ_SZ (4*PLY_GD_SZ+3)

/**
 * @brief Number of lines a square takes vertically
 * 
 */
#define SQ_LINES (SP_GD_HGHT + 3 + 2)

/**
 * @brief Size of a square in the map
 * 
 */
#define SQ_IN_SZ (SQ_SZ)

/**
 * @brief Maximum number of objects in a space that will be printed
 * 
 */
#define NUM_OBJS_PRINT 5

/**
 * @brief Maximum number of characters in a space that will be printed
 * 
 */
#define NUM_CHARR_PRINT 3

/**
 * @brief Characters of the name of the object that will be printed
 * 
 */
#define OBJ_GD_SZ 3

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
 * @brief Type of wall that should be printed
 * 
 */
typedef enum { ERR_WALL = -1, NO_WALL, CLSD_WALL, LOCK_WALL, CONEX_WALL, OPEN_WALL, HUMAN_WALL, MNSTR_WALL} Wall_style;

/**
 * @brief Struct that stores the information of the graphic engine: Id, name and desc
 * @author Profesores PPROG
 * 
 */
struct _Graphic_engine {
  Area *map, *descript, *player_inf, *pov, *message, *feedback;
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
 * @param lines Lines in which the spaces will be printed
 */
void graphic_engine_map_print_row(Game *game, Graphic_engine *ge, Id left, Id center, Id right, char lines[SQ_LINES][WIDTH_MAP + 1]);

/**
 * @brief Prints a map with 9 spaces in order
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param ge Pointer to the graphic engine
 * @param id Array of 9 ids of the spaces which will be printed as the map
 */
void graphic_engine_map_print_map(Game *game, Graphic_engine *ge, Id id[9]);

/**
 * @brief Prints into a group of strings the visuals of one space
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param ge Pointer to the graphic engine
 * @param lines Strings where the visuals will be saved
 * @param id Id of the space that will be printed
 */
void graphic_engine_map_print_square(Game *game, Graphic_engine *ge, char lines[SQ_LINES][WIDTH_MAP + 1], Id id);

/**
 * @brief Gets the 8 spaces that are surrounding one space
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param center Id of the space in the middle
 * @param neighbor Ids where the id of the surroundings will be saved
 */
void graphic_engine_get_surroundings(Game *game, Id center, Id neighbor[8]);

/**
 * @brief Reports the way a link should be printed according to its assets
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param link Pointer to the link
 * @return The type of wall the link represents
 */
Wall_style graphic_engine_get_wall_style(Game *game, Link *link);

/**
 * @brief Prints a vertical wall between two spaces according to their conexion
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param link Pointer to the link
 * @param lines Pointer to the lines where the wall will be printed
 */
void graphic_engine_print_vertical_wall(Game *game, Link *link, char lines[SQ_LINES][WIDTH_MAP + 1]);

/**
 * @brief Prints a horizontal wall between two spaces according to their conexion
 * @author Juan Ibáñez
 * 
 * @param game Pointer to the game
 * @param link Pointer to the link
 * @param line Pointer to the line where the wall will be printed
 */
void graphic_engine_print_horizontal_wall(Game *game, Link *link, char line[WIDTH_MAP + 1]);

/**
 * @brief Prints the minimap
 * @author Alina Datsko
 * 
 * @param game Pointer to the game
 * @param link Pointer to the graphic engine
 */
void graphic_engine_print_minimap(Game *game, Graphic_engine *ge);

/*
 * ************** Implementation of private functions ****************
*/

Wall_style graphic_engine_get_wall_style(Game *game, Link *link) {
  Bool connected = FALSE,  open = FALSE, locked = FALSE;
  Role link_role = NO_ROLE;

  if(!game) return ERR_WALL;

  if(!link) return NO_WALL;

  link_role = link_get_use_role(link);

  if(link_get_connected(link, &connected) == ERROR) return ERR_WALL;
  if(link_get_open(link, &open) == ERROR) return ERR_WALL;
  if(link_get_locked(link, &locked) == ERROR) return ERR_WALL;

  if(open == TRUE){
    if(connected) return CONEX_WALL;
    else{
      if(link_role == TEAM1 || link_role == TEAM2) return HUMAN_WALL;
      else if(link_role == MONSTER) return MONSTER;
      else return OPEN_WALL;
    }
    
  } else if(locked == TRUE) return LOCK_WALL;

  return CLSD_WALL;
}

void graphic_engine_print_vertical_wall(Game *game, Link *link, char lines[SQ_LINES][WIDTH_MAP + 1]) {
  int i = 0;
  Wall_style wall_style = ERR_WALL;

  if(!game || !lines) return;

  wall_style = graphic_engine_get_wall_style(game,link);
  if(wall_style == ERR_WALL) return;

  switch(wall_style){
    case NO_WALL:
    for(i=0;i<SQ_LINES;i++) strcat(lines[i],"H");
    break;

    case CLSD_WALL:
      for(i=0;i<SQ_LINES;i++) strcat(lines[i],"|");
      break;

    case LOCK_WALL:
      for(i=0;i<SQ_LINES;i++) {
        if(i==(SQ_LINES/2)) strcat(lines[i], "&");
        else strcat(lines[i], "|");
      }
      break;

    case CONEX_WALL:
      for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");
      break;
    
    case OPEN_WALL:
      for(i=0;i<SQ_LINES;i++) {
        if(i<3 || i>SQ_LINES-4) strcat(lines[i],"|");
        else strcat(lines[i]," ");
      }
      break;

    case HUMAN_WALL:
    for(i=0;i<SQ_LINES;i++) {
      if(i<3 || i>SQ_LINES-4) strcat(lines[i],"Z");
      else strcat(lines[i],":");
    }
    break;

    case MNSTR_WALL:
      for(i=0;i<SQ_LINES;i++) {
        if(i<3 || i>SQ_LINES-4) strcat(lines[i],"|");
        else strcat(lines[i],"/");
      }
      break;

    default:
      break;
  }
}

void graphic_engine_print_horizontal_wall(Game *game, Link *link, char line[WIDTH_MAP + 1]) {
  int i = 0, wall_style = 0;

  if(!game || !line) return;

  wall_style = graphic_engine_get_wall_style(game, link);

  switch(wall_style){
    case NO_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line,"=");
      break;

    case CLSD_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line,"-");
      break;

    case LOCK_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) {
        if(i==(SQ_IN_SZ/2)) strcat(line,"&");
        else strcat(line,"-");
      }
      break;

    case CONEX_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line," ");
      break;
    
    case OPEN_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) {
        if(i<7 || i>SQ_IN_SZ-8) strcat(line,"-");
        else strcat(line," ");
      }
      break;

    case HUMAN_WALL:
    strcat(line,"+");
    for(i=0;i<SQ_IN_SZ;i++) {
      if(i<7 || i>SQ_IN_SZ-8) strcat(line,"N");
      else strcat(line,".");
    }
    break;

    case MNSTR_WALL:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) {
        if(i<7 || i>SQ_IN_SZ-8) strcat(line,"-");
        else strcat(line,"\\");
      }
      break;

    default:
      break;
  }
}

void graphic_engine_get_surroundings(Game *game, Id center, Id neighbor[8]){
  int i, n_next, n_back;
  Bool changes = TRUE;
  Direction next[8] = {E,E,S,S,W,W,N,N}, back;


  if(!game || center == NO_ID) return;

  /**The ids will be saved in the respective position of the array acording to the next reference: 
   * [0] [1] [2]
   * [7] [-] [3]
   * [6] [5] [4] 
  */

  for (i = 0; i < 8; i++) {
    neighbor[i] = NO_ID;
  }


  /*We first get the id of the spaces directly accesible by the player*/
  neighbor[1] = game_get_connection(game,center,N);
  neighbor[3] = game_get_connection(game,center,E);
  neighbor[5] = game_get_connection(game,center,S);
  neighbor[7] = game_get_connection(game,center,W);

  /*From there, we repeatedly try to get the adyacent ids of any of the 
  spaces we already got so that we discover new spaces if posible each time 
  untill we dont get any new one, which is when we will know we already got all we can get*/
  while(changes == TRUE){
    changes = FALSE;

    for(i=0;i<8;i++){
      n_next = (i + 1)%8;
      n_back = (i - 1 + 8)%8;
      back = next[(i+3)%8];
      if(neighbor[i] != NO_ID){
        if(neighbor[n_next] == NO_ID){
          if((neighbor[n_next] = game_get_connection(game, neighbor[i], next[i])) != NO_ID) changes = TRUE;
        }
        if(neighbor[n_back] == NO_ID){
          if((neighbor[n_back] = game_get_connection(game, neighbor[i], back)) != NO_ID) changes = TRUE;
        }
      }
    }
  }
}

void graphic_engine_map_print_square(Game *game, Graphic_engine *ge, char lines[SQ_LINES][WIDTH_MAP + 1], Id id){
  Space *space = NULL;
  Player *play = NULL;
  Bool discovered;
  Id obj_id = NO_ID, charr_id = NO_ID;
  Object *obj = NULL;
  Character *charr = NULL;
  char p_gdesc[MAX_PLAY][PLY_GD_SZ + 1];
  char line[SQ_SZ+1], space_gdesc[SP_GD_WTH + 1];
  int i = 0, count = 0;

  if(!game || !ge ) return;

  space = game_get_space(game, id);

  if(space){

    if(space_get_discovered(space, &discovered) == ERROR) return;

    if(discovered){
      /*Print the name and Id*/
      sprintf(line,"%-*.*s %*ld", SP_NAME_PRINT,SP_NAME_PRINT,space_get_name(space),SP_ID_PRINT,id);
      strcat(lines[0],line);

      /*Players*/
      for(i=0;i<MAX_PLAY;i++){
        play = game_get_player_at(game, i);
        if(!play){
          sprintf(p_gdesc[i],"%*s",PLY_GD_SZ,"");
          continue;
        } 

        if(player_get_location(play) == id){
          if(player_get_health(play) > 0) sprintf(p_gdesc[i],"%-*.*s",PLY_GD_SZ,PLY_GD_SZ,player_get_gdesc(play));
          else sprintf(p_gdesc[i],"%*.*s",PLY_GD_SZ,PLY_GD_SZ,"--{@");
        } else sprintf(p_gdesc[i],"%*s",PLY_GD_SZ,"");
      }

      sprintf(line, "%s %s %s %s", p_gdesc[0], p_gdesc[1], p_gdesc[2], p_gdesc[3]);
      strcat(lines[1],line);

      sprintf(line, "%s %s %s %s", p_gdesc[4], p_gdesc[5], p_gdesc[6], p_gdesc[7]);
      strcat(lines[2],line);

      /*Print the characters*/
      for(i=0, count = 0; i<space_get_num_characters(space) && i < NUM_CHARR_PRINT; i++){
        charr_id = space_get_character_at_pos(space,i);
        charr = game_get_character_from_id(game, charr_id);
        if(!charr) continue;

        if(character_get_health(charr) > 0){
          count += sprintf(line, "%-*.*s ", CHR_GD_SZ, CHR_GD_SZ, character_get_gdesc(charr));
          strcat(lines[3], line);
        }
      }
      if(space_get_num_characters(space) > NUM_CHARR_PRINT){
        strcat(lines[3], "...");
        count += 3;
      }
      sprintf(line, "%*s",SQ_IN_SZ-count,"");
      strcat(lines[3],line);


      /*Print the gdesc*/
      for(i=0;i<SP_GD_HGHT;i++){

        strcpy(space_gdesc, space_get_gdesc_at(space, i));

        sprintf(line,"%-*.*s",SQ_IN_SZ,SQ_IN_SZ,space_gdesc);
        strcat(lines[i + 4],line);
      }

      /*Print the objects*/
      for(i = 0, count = 0; i<space_get_num_objects(space) && i<NUM_OBJS_PRINT; i++){
        obj_id = space_get_object_at_pos(space,i);
        obj = game_get_object(game,obj_id);
        if(!obj) continue;

        count += sprintf(line, "%-*.*s ", OBJ_GD_SZ, OBJ_GD_SZ, class_get_name(game_get_class_from_id_obj(game, obj_id)));
        strcat(lines[SQ_LINES-1],line);
      }
      if(space_get_num_objects(space) > NUM_OBJS_PRINT){
        strcat(lines[SQ_LINES - 1], "...");
        count += 3;
      }
      sprintf(line, "%*s",SQ_IN_SZ-count,"");
      strcat(lines[SQ_LINES-1],line);

    } else {
      /*Case if space is not discovered*/
      sprintf(line,"%*.*s",SQ_IN_SZ,SQ_IN_SZ,"       ?       ");
      strcat(lines[0],line);
      for(i=1;i<SQ_LINES;i++){
        sprintf(line, "%*s", SQ_SZ,"");
        strcat(lines[i],line);
      }
    }
  } else {
    /*Case if space doesnt exist*/
    for(i=0;i<SQ_LINES;i++){
      sprintf(line, "%*s", SQ_SZ,"");
      strcat(lines[i],line);
    }
  }
}

void graphic_engine_map_print_row(Game *game, Graphic_engine *ge, Id left, Id center, Id right, char lines[SQ_LINES][WIDTH_MAP + 1]) {
  Link *link = NULL;
  Space *sp[3] = {NULL, NULL, NULL};
  int i = 0;

  if(!game || !ge) return;

  for(i=0;i<SQ_LINES;i++){
    lines[i][0] = '\0';
  }

  sp[0] = game_get_space(game, left);
  sp[1] = game_get_space(game, center);
  sp[2] = game_get_space(game, right);

  if(sp[0]){
    link = game_get_link(game,left,W);
    graphic_engine_print_vertical_wall(game, link, lines);
  } else for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");

  graphic_engine_map_print_square(game, ge, lines, left);

  if(sp[0] || sp[1]){
    link = game_get_link(game,center,W);
    graphic_engine_print_vertical_wall(game, link, lines);
  } else for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");

  graphic_engine_map_print_square(game, ge, lines, center);

  if(sp[1] || sp[2]){
    link = game_get_link(game,center,E);
    graphic_engine_print_vertical_wall(game, link, lines);
  } else for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");

  graphic_engine_map_print_square(game, ge, lines, right);

  if(sp[2]){
    link = game_get_link(game,right,E);
    graphic_engine_print_vertical_wall(game, link, lines);
  } else for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");

}

void graphic_engine_map_print_map(Game *game, Graphic_engine *ge, Id id[9]){
  char lines[SQ_LINES][WIDTH_MAP + 1];
  char interm[WIDTH_MAP + 1], aux[WORD_SIZE + 1];
  Link *link = NULL;
  Space *space[9];
  int i = 0;

  if (command_get_code(game_get_last_command(game)) == VIEW) {
    graphic_engine_print_minimap(game, ge);
    return;
  }

  for(i=0;i<SQ_LINES;i++){
    lines[i][0] = '\0';
  }

  for(i=0;i<9;i++){
    space[i] = game_get_space(game, id[i]);
  }
  
  strcpy(interm, "");
  for(i=0;i<3;i++){
    if(space[i]){
      link = game_get_link(game,id[i],N);
      graphic_engine_print_horizontal_wall(game, link, interm);
    } else{
      if(i>0 && (space[i-1])) strcat(interm,"+");
      else strcat(interm, " ");
      sprintf(aux,"%*s",SQ_IN_SZ,"");
      strcat(interm, aux);
    }
  }
  if(space[i]) strcat(interm, "+");
  screen_area_puts(ge->map,interm);

  /*Print upper row*/
  graphic_engine_map_print_row(game, ge, id[0], id[1], id[2], lines);
  for(i=0;i<SQ_LINES;i++) screen_area_puts(ge->map,lines[i]);

  strcpy(interm, "");
  for(i=3;i<6;i++){
    if(space[i] || space[i-3]){
      link = game_get_link(game,id[i],N);
      graphic_engine_print_horizontal_wall(game, link, interm);
    } else{
      if(i>3 && (space[i-1] || space[i-4])) strcat(interm,"+");
      else strcat(interm, " ");
      sprintf(aux,"%*s",SQ_IN_SZ,"");
      strcat(interm, aux);
    }
  }
  if(space[i]) strcat(interm, "+");
  screen_area_puts(ge->map,interm);

  /*Print middle row*/
  graphic_engine_map_print_row(game, ge, id[3], id[4], id[5], lines);
  for(i=0;i<SQ_LINES;i++) screen_area_puts(ge->map,lines[i]);

  strcpy(interm, "");
  for(i=3;i<6;i++){
    if(space[i] || space[i+3]){
      link = game_get_link(game,id[i],S);
      graphic_engine_print_horizontal_wall(game, link, interm);
    } else{
      if(i>3 && (space[i-1] || space[i+2])) strcat(interm,"+");
      else strcat(interm, " ");
      sprintf(aux,"%*s",SQ_IN_SZ,"");
      strcat(interm, aux);
    }
  }
  if(space[i]) strcat(interm, "+");
  screen_area_puts(ge->map,interm);

  /*Print lower row */
  graphic_engine_map_print_row(game, ge, id[6], id[7], id[8], lines);
  for(i=0;i<SQ_LINES;i++) screen_area_puts(ge->map,lines[i]);

  strcpy(interm, "");
  for(i=6;i<9;i++){
    if(space[i]){
      link = game_get_link(game,id[i],S);
      graphic_engine_print_horizontal_wall(game, link, interm);
    } else{
      strcat(interm, " ");
      sprintf(aux,"%*s",SQ_IN_SZ,"");
      strcat(interm, aux);
    }
  }
  /*if(space[i]) strcat(interm, "+");*/
  screen_area_puts(ge->map,interm);
  

}

void graphic_engine_print_minimap(Game *game, Graphic_engine *ge) {
  Space *sp = NULL;
  Id id_act = NO_ID;
  int i = 0, floor = 0;
  char *minimap = NULL;

  if (!game || ! ge) return;

  if ((id_act = game_get_player_location(game)) == NO_ID) return;
  if ((sp = game_get_space(game, id_act)) == NULL) return;

  if ((floor = game_get_floor(game, sp)) == -1) return;

  while ((minimap = game_get_minimap_at(game, i, floor))) {
    screen_area_puts(ge->map, minimap);
    i++;
  }
}

/*
 * ****************** Implementation of public functions **************************
 */

/*Creates a new graphic engine initializing all screen areas according to their area resolution*/
Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) return ge;

  screen_init(HEIGHT_MAP + HEIGHT_MSG + 3, POV_WDTH + WIDTH_MSG + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) return NULL;
  
  ge->player_inf = screen_area_init(1, 1, WIDTH_PINF, HEIGHT_PINF);
  ge->map = screen_area_init(WIDTH_PINF + 2, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_PINF + WIDTH_MAP + 3, 1, WIDTH_DESC, HEIGHT_DESC);

  ge->pov = screen_area_init(1, HEIGHT_PINF + 2, POV_WDTH, POV_HGHT);
  ge->feedback = screen_area_init(1, POV_HGHT + HEIGHT_PINF + 3, WIDTH_FDB, HEIGHT_FDB);
  ge->message = screen_area_init(POV_WDTH + 2, HEIGHT_MAP + 2, WIDTH_MSG, HEIGHT_MSG);
  
  return ge;
}

/*Destroys a graphic engine destroying each dedicated area and freeing allocated memory*/
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->pov);
  screen_area_destroy(ge->player_inf);
  screen_area_destroy(ge->message);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/*Paints each area according to its function with the necessary information*/
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, neighbors[8], map_spaces[9];
  Status last_status = ERROR;
  char str[MESG_SIZE + 1], *aux_name = NULL, *close_up = NULL, *msg = NULL, msg_aux[MESG_SIZE], *partial_msg = NULL;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, aux_health, turn, index_convert[9] = {0,1,2,7,-1,3,6,5,4}, chars = 0, num_followers = 0;
  Object *aux_obj = NULL;
  Character *aux_charr = NULL;
  Space *sp = NULL;
  Type sender_type = NO_TYPE;
  Player *act_player = NULL, *aux_player = NULL;
  Role role = NO_ROLE;
  Id aux_obj_id = NO_ID, aux_charr_id = NO_ID, weapon = NO_ID, armor = NO_ID;
  Inventory *inventory = NULL;
  Set *followers = NULL;

  id_act = game_get_player_location(game);
  if(id_act == NO_ID) return;
  sp = game_get_space(game, id_act);
  act_player = game_get_player(game);
  if(!act_player || !sp) return;
  role = player_get_role(act_player);
  if(role == NO_ROLE) return;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  graphic_engine_get_surroundings(game, id_act,neighbors);
  for(i=0;i<9;i++){
    if(i==4){
      map_spaces[i] = id_act;
      continue;
    }
    map_spaces[i] = neighbors[index_convert[i]];
  }
  graphic_engine_map_print_map(game,ge,map_spaces);

  /* Paint the description area */
  screen_area_clear(ge->descript);

  /*PLAYERS*/
  sprintf(str, " Quest-mates:");
  screen_area_puts(ge->descript, str);

  for(i = 0; i<game_get_n_players(game);i++){
    aux_player = game_get_player_at(game, i);
    if(!aux_player) continue;

    if(role != player_get_role(aux_player)) continue;
    
    aux_health = player_get_health(aux_player);
    if(aux_health < 0) continue;

    sprintf(str, "  %-*.*s %*.*s: %-*d (%d)", DESC_NAMES_SZ,DESC_NAMES_SZ,player_get_name(aux_player), PLY_GD_SZ, PLY_GD_SZ, player_get_gdesc(aux_player), DESC_ID_SZ, (int)player_get_location(aux_player), aux_health);
    screen_area_puts(ge->descript, str);
  }
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  /*OBJECTS*/
  sprintf(str, " Objects:");
  screen_area_puts(ge->descript, str);
  for(i=0; i<space_get_num_objects(sp);i++){
    aux_obj_id = space_get_object_at_pos(sp, i);
    if (aux_obj_id == NO_ID) continue;

    aux_obj = game_get_object(game, aux_obj_id);
    if(!aux_obj) continue;

    sprintf(str, "  %-*.*s", WIDTH_DESC-3,WIDTH_DESC-3, class_get_name(game_get_class_from_id_obj(game, aux_obj_id)));
    screen_area_puts(ge->descript, str);
  }
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  
  /*CHARACTERS*/
  sprintf(str, " Characters:");
  screen_area_puts(ge->descript, str);
  for(i=0; i<space_get_num_characters(sp);i++){
    aux_charr_id = space_get_character_at_pos(sp, i);
    if (aux_charr_id == NO_ID) continue;

    aux_charr = game_get_character_from_id(game, aux_charr_id);
    if(!aux_charr) continue;

    aux_health = character_get_health(aux_charr);
    if (aux_health <= 0) continue;

    sprintf(str, "  %-*.*s (%d)", DESC_NAMES_SZ,DESC_NAMES_SZ, character_get_gdesc(aux_charr), aux_health);
    screen_area_puts(ge->descript, str);
  }

  /* Paint the player info area */
  screen_area_clear(ge->player_inf);
  /*HEALTH*/
  sprintf(str, " Health: %d", player_get_health(act_player));
  screen_area_puts(ge->player_inf, str);
  sprintf(str, " ");
  screen_area_puts(ge->player_inf, str);
  
  /*INVENTORY*/
  sprintf(str, " Inventory:");
  screen_area_puts(ge->player_inf, str);

  player_get_armor(act_player, &armor);
  player_get_weapon(act_player, &weapon);

  inventory = player_get_backpack(act_player);
  if(inventory){
    for (i = 0; i < inventory_get_num_objects(inventory); i++) {

      aux_obj_id = inventory_get_object_at_pos(inventory, i);
      if (aux_obj_id == NO_ID || aux_obj_id ==  armor|| aux_obj_id == weapon) continue;

      aux_obj = game_get_object(game, aux_obj_id);
      if(!aux_obj) continue;
  
      sprintf(str, "  %-*.*s", DESC_NAMES_SZ,DESC_NAMES_SZ, class_get_name(game_get_class_from_id_obj(game, aux_obj_id)));
      screen_area_puts(ge->player_inf, str); 
    }
  }
  sprintf(str, " ");
  screen_area_puts(ge->player_inf, str);

  if(armor == NO_ID){
    sprintf(str, " Armor: (no armor)");
    screen_area_puts(ge->player_inf, str);
    sprintf(str, "  DEF: 0");
    screen_area_puts(ge->player_inf, str);
  } else {
    aux_obj = game_get_object(game, armor);
    if(aux_obj){
      sprintf(str, " Armor: %-*.*s", DESC_NAMES_SZ,DESC_NAMES_SZ, class_get_name(game_get_class_from_id_obj(game, armor)));
      screen_area_puts(ge->player_inf, str);
      sprintf(str, "  DEF: %d", (int)object_get_use_value(aux_obj));
      screen_area_puts(ge->player_inf, str);
    }
  }
  

  if(weapon == NO_ID){
    sprintf(str, " Weapon: Fist");
    screen_area_puts(ge->player_inf, str);
    sprintf(str, "  ATK: %d", PLY_BASE_DMG);
    screen_area_puts(ge->player_inf, str);
  } else {
    aux_obj = game_get_object(game, weapon);
    if(aux_obj){
      sprintf(str, " Weapon: %-*.*s", DESC_NAMES_SZ,DESC_NAMES_SZ, class_get_name(game_get_class_from_id_obj(game, weapon)));
      screen_area_puts(ge->player_inf, str);
      sprintf(str, "  ATK: %d", (int)object_get_use_value(aux_obj) + PLY_BASE_DMG);
      screen_area_puts(ge->player_inf, str);
    } 
    
  }
  

  num_followers = game_get_num_followers(game, act_player);
  if(num_followers == -1) return;

  if(num_followers > 0){
    followers = game_get_followers(game, act_player);
    if(!followers) return;
  
    sprintf(str, " ");
    screen_area_puts(ge->player_inf, str);
  
    sprintf(str, " Following:");
    screen_area_puts(ge->player_inf, str);
  
    for(i=0;i<num_followers;i++){
      aux_charr_id = set_get_id_at_pos(followers, i);
      if (aux_charr_id == NO_ID) continue;
  
      aux_charr = game_get_character_from_id(game, aux_charr_id);
      if(!aux_charr) continue;
  
      aux_health = character_get_health(aux_charr);
      if (aux_health <= 0) continue;
  
      sprintf(str, "  %-*.*s (%d)", DESC_NAMES_SZ,DESC_NAMES_SZ, character_get_gdesc(aux_charr), aux_health);
      screen_area_puts(ge->player_inf, str);
    }

    if (set_destroy(followers) == ERROR) return;
  }

  /* Paint the message area */
  if ((turn = game_get_turn(game)) == -1) return;
  screen_area_clear(ge->message);
  
  for (i = 1; i <= NUM_MSGS; i++) {
    chars = 0;
    str[0] = '\0';
    if(game_get_last_message_visibility_at_pos(game, turn, NUM_MSGS-i) == TRUE) {
      sender_type = game_get_last_message_sender_type_at_pos(game, turn, NUM_MSGS-i);

      switch (sender_type)
      {
      case GAME:
        chars = sprintf(str, " Speakers:");
        break;
      case THOUGHTS:
        chars = sprintf(str, " You:");
        break;
      case NO_TYPE:
        chars = sprintf(str, " The voices:");
        break;
      default:
        aux_name = game_get_last_message_sender_name_at_pos(game, turn, NUM_MSGS-i);
        if(aux_name) chars = sprintf(str, " %s:", aux_name);
        break;
      }

      msg = game_get_last_message_at_pos(game, turn, NUM_MSGS-i);
      if(msg) strcpy(msg_aux, msg);
      
      if(msg) {
        partial_msg = strtok(msg_aux, "@\n\r\0");
        sprintf(str + chars, " %s", partial_msg);
        screen_area_puts(ge->message, str);
        str[chars] = '\0';
        while((partial_msg = strtok(NULL, "@\n\r\0"))){
          sprintf(str, " %s", partial_msg);
          screen_area_puts(ge->message, str);
        }
      }
    }
  }

  /* Paint in the close up area */
  screen_area_clear(ge->pov);
  for(i=0;i<POV_HGHT;i++){
    if(!(close_up = game_get_last_close_up_at(game, i)) || (strcmp(close_up, "") == 0)) {
      if(!(close_up = player_get_closeup_at(act_player, i))){
        sprintf(str, "%-*s", POV_WDTH, "");
      }
      else sprintf(str, "%-*.*s", POV_WDTH,POV_WDTH, close_up);
    }
    else sprintf(str, "%-*.*s", POV_WDTH,POV_WDTH, close_up);
    screen_area_puts(ge->pov, str);
  }

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
