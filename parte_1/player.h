/** @brief Implementacion del modulo encargado de
*   cargar los espacios
*
* @file Player.h
* @author Saul Almazan y Alvaro Becerra Jimenez
* @version 1.0*/
#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
typedef struct _Player Player;

/*funciones basicas para crear y destruir el jugador*/
Player *player_create();
void player_destroy(Player *);

/*funciones para establecer los valores de player*/
STATUS player_set_name(Player *,char *);
STATUS player_set_id(Player *,int);
STATUS player_set_object_id(Player *, int );
STATUS player_set_space_id(Player *, int );

/*funciones para obtener cualquier campo de player*/
char * player_get_name(Player *);
int player_get_id(Player *);
int player_get_object_id(Player *);
int player_get_space_id(Player *);

/*Imprime todos los datos del player*/
STATUS player_print(FILE *,Player *);

#endif
