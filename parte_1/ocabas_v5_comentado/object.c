/** @brief Implementacion del modulo encargado de
 *   cargar los espacios
 *
 * @file Object.c
 * @author Saul Almazan y Alvaro Becerra Jimenez
 * @version 1.0*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

#define TAM 32

struct _Object {
    Id id;
    char name[TAM];
};


/******************************************************************
*Funcion :object_create
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de crear el objecto
*Input: nada
*Output: El objeto
********************************************************************/
Object *object_create() {
    Object *po = NULL;
    po = (Object*) calloc(1, sizeof (Object));
    po->id = NO_ID;
    return po;
}

/******************************************************************
*Funcion :object_destroy
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de destruir el objecto
*Input: Object
*Output:
********************************************************************/
void object_destroy(Object * po) {
    if (po) {
        free(po);
        po = NULL;
    }
}



/******************************************************************
*Funcion :object_get_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de tener el id
*Input: id
*Output: El objeto
********************************************************************/
Id object_get_id(Object *po) {
    if (!po) return NO_ID;
    return po->id;
}


/******************************************************************
*Funcion :object_get_name
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de devolver el objeto
*Input: char * el nombre del objeto
*Output: El objeto
********************************************************************/
char *object_get_name(Object *po) {
    if (!po) return NULL;
    return po->name;
}



/******************************************************************
*Funcion :object_set_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner el id del objeto
*Input: El objeto y el nuevo id
*Output: Ok si sale bien y Error si hay algo mal
********************************************************************/
STATUS object_set_id(Object * po, Id nuevo_id) {
    if (!po) return ERROR;
    po->id = nuevo_id;
    return OK;
}

/******************************************************************
*Funcion :object_set_name
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de poner el nombre
*Input: El objeto y char *el nuevo nombtr
*Output: Ok si sale bien y Error si hay algo mal
********************************************************************/
STATUS object_set_name(Object *po, char *nuevo_nombre) {
    if (!po || !nuevo_nombre) return ERROR;
    strcpy(po->name, nuevo_nombre);
    return OK;
}

/******************************************************************
*Funcion :object_set_id
*Autores: Saul Almazan y Alvaro Becerra Jiminez
*Description: Funcion que se enccarga de printear el objeto
*Input: El objeto y el fichero donde se escribirá
*Output: un int si va todo bien >0
********************************************************************/
int print_object(FILE *f, Object *po) {
    if (!po || !f) return ERROR;
    return fprintf(f, " %ld %s\n", po->id, po->name);
}
