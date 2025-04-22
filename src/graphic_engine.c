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
#define WIDTH_MAP (3*SQ_SZ+4)

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
#define NUM_OBJS_PRINT 4

/**
 * @brief Maximum number of characters in a space that will be printed
 * 
 */
#define NUM_CHARR_PRINT 3

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
 * @return 1 if blocked, 2 if open but unusable, 3 if its an open door, 4 if its a wide conexion
 */
int graphic_engine_get_wall_style(Game *game, Link *link);

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

/*
 * ************** Implementation of private functions ****************
*/

int graphic_engine_get_wall_style(Game *game, Link *link) {
  Bool usable = FALSE,  connected = FALSE,  open = FALSE;
  Role play_role = NO_ROLE, link_role = NO_ROLE;

  if(!game) return 0;

  if(!link) return 1;

  play_role = player_get_role(game_get_player(game));
  link_role = link_get_use_role(link);

  if(link_role == UNDEFINED || play_role == link_role) usable = TRUE;
  else usable = FALSE;

  if(link_get_connected(link, &connected) == ERROR) return 0;
  if(link_get_open(link, &open) == ERROR) return 0;

  if(open){
    if(usable){
      if(connected) return 4;
      else return 3;
    } else return 2;
  } else return 1;
}

void graphic_engine_print_vertical_wall(Game *game, Link *link, char lines[SQ_LINES][WIDTH_MAP + 1]) {
  int i = 0, wall_style = 0;

  if(!game || !lines) return;

  wall_style = graphic_engine_get_wall_style(game,link);
  if(wall_style == 0) return;

  switch(wall_style){
    case 1:
      for(i=0;i<SQ_LINES;i++) strcat(lines[i],"|");
      break;
    case 2:
      for(i=0;i<SQ_LINES;i++) strcat(lines[i],"s");
      break;
    case 3:
      for(i=0;i<SQ_LINES;i++) {
        if(i<3 || i>SQ_LINES-4) strcat(lines[i],"|");
        else strcat(lines[i]," ");
      }
      break;
    case 4:
      for(i=0;i<SQ_LINES;i++) strcat(lines[i]," ");
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
    case 1:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line,"-");
      break;
    case 2:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line,".");
      break;
    case 3:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) {
        if(i<7 || i>SQ_IN_SZ-8) strcat(line,"-");
        else strcat(line," ");
      }
      break;
    case 4:
      strcat(line,"+");
      for(i=0;i<SQ_IN_SZ;i++) strcat(line," ");
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

        count += sprintf(line, "%-*.*s", CHR_GD_SZ, CHR_GD_SZ, character_get_gdesc(charr));
        strcat(lines[3], line);
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

        count += sprintf(line, "%-*.*s ", OBJ_GD_SZ, OBJ_GD_SZ, object_get_name(obj));
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
      if(i>6 && (space[i-1] || space[i+2])) strcat(interm,"+");
      else strcat(interm, " ");
      sprintf(aux,"%*s",SQ_IN_SZ,"");
      strcat(interm, aux);
    }
  }
  if(space[i]) strcat(interm, "+");
  screen_area_puts(ge->map,interm);
  

}

/*
 * ****************** Implementation of public functions **************************
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
  Id id_act = NO_ID, neighbors[8], map_spaces[9];
  Status last_status = ERROR;
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i, aux_health, turn, index_convert[9] = {0,1,2,7,-1,3,6,5,4};
  Object *aux_obj = NULL;
  Character *aux_charr = NULL;
  Player *aux_player = NULL;
  Id aux_obj_id = NO_ID, aux_charr_id = NO_ID;

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    graphic_engine_get_surroundings(game, id_act,neighbors);
    for(i=0;i<9;i++){
      if(i==4){
        map_spaces[i] = id_act;
        continue;
      }
      map_spaces[i] = neighbors[index_convert[i]];
    }
    graphic_engine_map_print_map(game,ge,map_spaces);
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
  sprintf(str," drop or d, attack or at, chat or c, inspect or i, recruit or r, abandon or ab and use or u");
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
