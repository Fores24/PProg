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
  int id;
  int object_id;
  int space_id;
};

Player * player_create(){
  Player *p = NULL;
  p =(Player*) malloc (sizeof(Player));
  if (!p){
    return NULL;
  }
  return p;
}

void player_destroy(Player *p){
  if (p){
    free(p);
    p = NULL;
  }
}
STATUS player_set_name(Player *p,char *name){
  if (!p || !name){
    return ERROR;
  }


  strcpy (p->name,name);
  return OK;
}
STATUS player_set_id(Player *p,int id){
  if (!p){
    return ERROR;
  }
    p->id = id;
  return OK;
}
STATUS player_set_object_id(Player *p, int object_id ){
  if (!p){
    return ERROR;
  }
    p->object_id = object_id;
  return OK;
}
STATUS player_set_space_id(Player *p, int space_id){
  if (!p){
    return ERROR;
  }
    p->space_id = space_id;
  return OK;
}

char * player_get_name(Player *p){
    if (!p){
      return NULL;
    }
    return p->name;
}

int player_get_id(Player *p){
  if (!p){
    return -1;
  }
  return p->id;
}

int player_get_object_id(Player *p){
  if (!p){
    return -1;
  }
  return p->object_id;
}
int player_get_space_id(Player *p){
  if (!p){
    return -1;
  }
  return p->space_id;
}

STATUS player_print(FILE *f ,Player *p){
  if (!f || !p){
    return ERROR;
  }
fprintf(f," %s , %d, %d ,%d", p->name , p->id, p->object_id, p->space_id);

return OK;
}
