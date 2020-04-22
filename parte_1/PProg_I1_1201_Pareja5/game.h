
/* ===================================================================
File: game.h
Version: 2.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Contiene todos los prototipos de las funciones de game públicas, así como la estructura de game 
Revision historica: 
13-01-2015 versión 1.0 (código inicial)
1-10-2018 versión 2.0 
      Añadidas funciones para coger y soltar objetos y avanzar y retroceder de oca a oca. Además, se ha
      modificado la estructura para incluir punteros a objeto y a jugador.

=================================================================== */

#ifndef GAME_H
#define GAME_H

#include "space.h"
#include "command.h"
#include "object.h"
#include "player.h"
#define MAX_OBJECT 2

/** La estructura game almacena datos del juego como los espacios, el jugador, los objetos y el último comando**/
typedef struct _Game {
    Player *player; /*Puntero a estructura jugador*/
    Object *object[MAX_OBJECT]; /*Punteros a estructura objeto*/
    Space* spaces[MAX_SPACES + 1]; /*Punteros a estructura espacio*/
    T_Command last_cmd; /*Último comando*/
} Game;

/*Funciones para crear, actualizar y destruir un juego*/
STATUS game_create(Game* game, char * name_player);
STATUS game_create_from_file(Game* game, char* filename, char* name_player);
STATUS game_update(Game* game, T_Command cmd);
STATUS game_destroy(Game* game);
BOOL game_is_over(Game* game);

/*Función para añadir un espacio a un juego*/
STATUS game_add_space(Game* game, Space* space);

/*Funciones para imprimir pantalla y los datos de un juego*/
void game_print_screen(Game* game);
void game_print_data(Game* game);

/*Funciones para obtener datos de un juego*/
Space* game_get_space(Game* game, Id id);
Id game_get_player_location(Game* game);
Id game_get_object_location(Game* game, Id id);
char *game_get_object_name(Game *game, Id id);
T_Command game_get_last_command(Game* game);
#endif
