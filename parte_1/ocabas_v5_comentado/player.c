/** @brief Implementacion del modulo encargado de
 *   cargar los espacios
 *
 * @file Player.c
 * @author Saul Almazan y Alvaro Becerra Jimenez
 * @version 1.0*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

/*Tamaño maximo de los nombres de los jugadores*/
#define TAM 32

struct _Player {
    char name[TAM];
    Id id;
    Id object_id;
    Id space_id;
};
/******************************************************************
*Funcion :player_create
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se encarga de crear el jugador
*Input: nada
*Output: el Player
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
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de destruir el jugador
*Input: El player
*Output: nada
********************************************************************/
void player_destroy(Player *p) {
    if (p) {
        free(p);
        p = NULL;
    }
}

/******************************************************************
*Funcion :player_set_name
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner nombre del jugador
*Input: El jugador y el nombre
*Output: Ok si sale bien y Error si hay algo mal
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
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner el id
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
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner el object id
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
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner el space id
*Input: El jugador y el id de espacio
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
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de devolver el nombre
*Input: El jugador
*Output: char * con el nombre del jugador
********************************************************************/
char * player_get_name(Player *p) {
    if (!p) {
        return NULL;
    }
    return p->name;
}

/******************************************************************
*Funcion :player_get_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de devolver el id del jugador
*Input: El jugador
*Output: Id del jugador
********************************************************************/
Id player_get_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->id;
}


/******************************************************************
*Funcion :player_get_object_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de devolver el id del object
*Input: El jugador
*Output: id del object
********************************************************************/
Id player_get_object_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->object_id;
}



/******************************************************************
*Funcion :player_get_space_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de devolver el id del space
*Input: El jugador
*Output: id del object
********************************************************************/
Id player_get_space_id(Player *p) {
    if (!p) {
        return NO_ID;
    }
    return p->space_id;
}



/******************************************************************
*Funcion :print_player
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de printear el objeto
*Input: El jugador y el fichero
*Output: int si es mayor que 0 ha ido todo bien 
********************************************************************/
int print_player(FILE *f, Player *p) {
    if (!f || !p) {
        return ERROR;
    }
    return fprintf(f, "Nombre: %s, id=%ld, objeto=%ld, casilla=%ld", p->name, p->id, p->object_id, p->space_id);
}
