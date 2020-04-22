/* ===================================================================
File: object.c
Version: 1.0
Date: 1-10-2018
Autores: Saul Almazan y Alvaro Becerra Jiminez
Description: Contiene todas las funciones que perimiten crear objetos y trabajar con sus campos
Revision historica: 
1-10-2018 versión 1.0 
=================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#define TAM 32 /*Tamaño máximo nombre*/

/*Estructura del objeto que almacena el nombre y su id*/
struct _Object {
    Id id; /*Identificador del objeto*/
    char name[TAM]; /*Nombre del objeto*/
};

/******************************************************************
 *Funcion :object_create
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de crear el objecto
 *Input: nada
 *Output: el objeto o NULL si hay error
 ********************************************************************/

Object *object_create() {
    Object *po = NULL;
    po = (Object*) calloc(1, sizeof (Object));
    po->id = NO_ID;
    return po;
}

/******************************************************************
 *Funcion:object_destroy
 *Autores: Alvaro Becerra Jiminez
 *Date: 1-10-2018
 *Description: Funcion que se encarga de destruir el objecto
 *Input: Object
 *Output: nada
 ********************************************************************/

void object_destroy(Object * po) {
    if (po) {
        free(po);
        po = NULL;
    }
    return;
}

/******************************************************************
 *Funcion :object_get_id
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de obtener el id de un objeto
 *Input: Object
 *Output: el id o NO_ID si el objeto del que se pide el id no existe
 ********************************************************************/

Id object_get_id(Object *po) {
    if (!po) return NO_ID;
    return po->id;
}

/******************************************************************
 *Funcion :object_get_name
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de devolver el nombre del objeto
 *Input: object
 *Output: char * el nombre del objeto o NULL si el objeto del que se pide el nombre no existe
 ********************************************************************/

char *object_get_name(Object *po) {
    if (!po) return NULL;
    return po->name;
}

/******************************************************************
 *Funcion :object_set_id
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de poner un nuevo id al objeto
 *Input: El objeto y el nuevo id
 *Output: Ok si sale bien y ERROR si no existe el objeto
 ********************************************************************/

STATUS object_set_id(Object * po, Id nuevo_id) {
    if (!po) return ERROR;
    po->id = nuevo_id; /*No comprobamos si el nuevo id es distinto a NO_ID porque en el juego, 
						quizás queramos destruir el objeto de esta forma*/
    return OK;
}

/******************************************************************
 *Funcion :object_set_name
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se encarga de poner el nombre a un objeto
 *Input: El objeto y char * del nuevo nombre
 *Output: Ok si sale bien y ERROR si algún parámetro de la entrada no existe
 ********************************************************************/

STATUS object_set_name(Object *po, char *nuevo_nombre) {
    if (!po || !nuevo_nombre) return ERROR;
    strcpy(po->name, nuevo_nombre);
    return OK;
}

/******************************************************************
 *Funcion :object_set_id
 *Date: 1-10-2018
 *Autores: Alvaro Becerra Jiminez
 *Description: Funcion que se enccarga de imprimir el objeto
 *Input: El objeto y el fichero donde se escribirá
 *Output: un int que, si va todo bien, será mayor que 0
 ********************************************************************/

int print_object(FILE *f, Object *po) {
    if (!po || !f) return ERROR;
    return fprintf(f, " %ld %s\n", po->id, po->name);
}
