/* ===================================================================
File: player.c
Version: 1.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Contiene todas las funciones que perimiten crear jugadores y trabajar con sus campos
Revision historica: 
1-10-2018 versión 1.0 
=================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

/*Tamaño maximo de los nombres de los jugadores*/
#define TAM 32

/*Estructura de Player que guarda información sobre su nombre, su id o dónde está y qué objetos lleva*/
struct _Player {
    char name[TAM]; /*Nombre del jugador*/
    Id id; /*Su número identificador*/
    Id object_id; /*El número identificador del objeto que lleva*/
    Id space_id; /*El número identificador del espacio en el que se encuentra el jugador*/
};

/******************************************************************
 *Funcion :player_create
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de crear el jugador
 *Input: nada
 *Output: el Player o NULL si no se ha podido crear
 ********************************************************************/

Player * player_create() {
    Player *p = NULL;
    p = (Player*) malloc(sizeof (Player));
    if (!p) {
        return NULL;
    }
    p->id = NO_ID;
    p->object_id = NO_ID;
    p->space_id = NO_ID;
    return p;
}

/******************************************************************
 *Funcion :player_destroy
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de destruir el jugador
 *Input: El player
 *Output: nada
 ********************************************************************/

void player_destroy(Player *p) {
    if (p) {
        free(p);
        p = NULL;
    }
    return;
}

/******************************************************************
 *Funcion :player_set_name
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de establecer nombre del jugador
 *Input: El jugador y el nombre
 *Output: Ok si sale bien y ERROR si hay los parámetro de entrada no existen
 ********************************************************************/

STATUS player_set_name(Player *p, char *name) {
    if (!p || !name) {
        return ERROR;
    }
    strcpy(p->name, name);
    return OK;
}

/******************************************************************
 *Funcion :player_set_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de establecer el id del jugador
 *Input: El jugador y el id
 *Output: Ok si sale bien y Error si hay algo mal
 ********************************************************************/

STATUS player_set_id(Player *p, Id id) {
    if (!p) {
        return ERROR;
    }
    p->id = id;
    return OK;
}

/******************************************************************
 *Funcion :player_set_object_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de establecer el object id
 *Input: El jugador y el id del object
 *Output: Ok si sale bien y Error si hay algo mal
 ********************************************************************/

STATUS player_set_object_id(Player *p, Id object_id) {
    if (!p) {
        return ERROR;
    }
    p->object_id = object_id;
    return OK;
}

/******************************************************************
 *Funcion :player_set_space_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de establecer el space_id
 *Input: El jugador y el id del espacio
 *Output: Ok si sale bien y Error si hay algo mal
 ********************************************************************/

STATUS player_set_space_id(Player *p, Id space_id) {
    if (!p) {
        return ERROR;
    }
    p->space_id = space_id;
    return OK;
}

/******************************************************************
 *Funcion :player_get_name
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de devolver el nombre del jugador
 *Input: El jugador
 *Output: char * con el nombre del jugador o NULL si no existe el jugador
 ********************************************************************/

char * player_get_name(Player *p) {
    if (!p) {
        return NULL;
    }
    return p->name;
}

/******************************************************************
 *Funcion :player_get_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de devolver el id del jugador
 *Input: El jugador
 *Output: Id del jugador o NO_ID si no existe el jugador
 ********************************************************************/

Id player_get_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->id;
}

/******************************************************************
 *Funcion :player_get_object_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se enccarga de devolver el id del object
 *Input: El jugador
 *Output: id del object o NO_ID si no existe el jugador
 ********************************************************************/

Id player_get_object_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->object_id;
}

/******************************************************************
 *Funcion :player_get_space_id
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se encarga de devolver el id del space
 *Input: El jugador
 *Output: id del espacio o NO_ID si no existe el jugador
 ********************************************************************/

Id player_get_space_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->space_id;
}

/******************************************************************
 *Funcion :print_player
 *Date: 1-10-2018
 *Autores: Saul Almazan
 *Description: Funcion que se enccarga de imprimir los datos del objeto
 *Input: El jugador y el fichero donde se han de escribir los datos
 *Output: int que si es mayor que 0, significa ha ido todo bien 
 ********************************************************************/
int print_player(FILE *f, Player *p) {
    if (!f || !p) {
        return ERROR;
    }
    return fprintf(f, "Nombre: %s, id=%ld, objeto=%ld, casilla=%ld", p->name, p->id, p->object_id, p->space_id);
}
