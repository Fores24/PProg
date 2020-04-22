/* ===================================================================
File: player.h
Version: 1.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Contiene todos los prototipos de las funciones de player.c
Revision historica: 
1-10-2018 versión 1.0 
=================================================================== */
#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
typedef struct _Player Player;

/*funciones basicas para crear y destruir el jugador*/
Player *player_create();
void player_destroy(Player *);

/*funciones para establecer los valores de player*/
STATUS player_set_name(Player *, char *);
STATUS player_set_id(Player *, Id);
STATUS player_set_object_id(Player *, Id);
STATUS player_set_space_id(Player *, Id);

/*funciones para obtener cualquier campo de player*/
char * player_get_name(Player *);
Id player_get_id(Player *);
Id player_get_object_id(Player *);
Id player_get_space_id(Player *);

/*Imprime todos los datos del player*/
int print_player(FILE *, Player *);

#endif
